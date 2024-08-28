//
// Created by Arthur Motelevicz on 08/08/24.
//

#ifndef CEDRO_MD_BQTMODEL_H
#define CEDRO_MD_BQTMODEL_H

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "CMDTypes.h"

namespace cedro::md::models
{


  class BQTModel
  {
  public:
    char symbol[MAX_STRING_SIZE]="";
    char msgType{'\0'};

    int32_t position{INVALID_INT32};
    int32_t oldPosition{INVALID_INT32};
    char direction{'\0'};
    double price{dNaN};
    int32_t quantity{INVALID_INT32};
    int32_t broker{INVALID_INT32};
    char datetime[MAX_STRING_SIZE]="";
    char orderID[MAX_STRING_SIZE]="";
    int32_t cancelType{INVALID_INT32};
    char offerType{'\0'};


    void parseBQTMessage(const char* message, size_t length)
    {
      // Remove the prefix "B:"
      const char* content = message + 2;
      size_t contentLength = length - 2;

      const char* firstColon = std::strchr(content, ':');
      if (firstColon == nullptr || firstColon - content >= contentLength)
        return;

      size_t symbolLength = firstColon - content;
      std::strncpy(symbol, content, symbolLength);
      symbol[symbolLength] = '\0';

      msgType = *(firstColon + 1);

      if (msgType == 'E')
      {
        LOG_INFO("End of initial data received for symbol: " + std::string(symbol));
        return;
      }

      // Move to after msgType column ':'
      const char* currentPos = firstColon + 3;

      auto toInt = [](int32_t &out, const char* inStart) -> bool
      {
        char* outEnd;
        long value = std::strtol(inStart, &outEnd, 10);

        if (value == INVALID_INT32 || outEnd == inStart)
        {
          out = INVALID_INT32;
          return false;
        }

        out = static_cast<int32_t>(value);
        return true;
      };

      auto toDouble = [](double &out, const char* inStart) -> bool
      {
        char* outEnd;
        double value = std::strtod(inStart, &outEnd);

        if (std::isnan(value) || outEnd == inStart)
        {
          out = dNaN;
          return false;
        }

        out = value;
        return true;
      };

      auto moveOn = [](const char*& currentPos) -> bool
      {
        currentPos = std::strchr(currentPos, ':');
        if (currentPos == nullptr)
        {
          LOG_ERROR("BQT: Unexpected end of data.");
          return false;
        }

        currentPos++; // Skips the ':'
        return true;
      };

      switch (msgType)
      {
        case 'A': // Add order
        {
          if(!toInt(position, currentPos))
          {
            LOG_ERROR("BQT: Msg(A) - Position parse error.");
            break;
          }

          if(!moveOn(currentPos))
            break;

          direction = *currentPos++;

          if(!moveOn(currentPos))
            break;

          if (!toDouble(price, currentPos))
          {
            LOG_ERROR("BQT: Msg(A) - Price parse error.");
            break;
          }

          if(!moveOn(currentPos))
            break;

          if (!toInt(quantity, currentPos))
          {
            LOG_ERROR("BQT: Msg(A) - Quantity parse error.");
            break;
          }

          if(!moveOn(currentPos))
            break;

          if (!toInt(broker, currentPos))
          {
            LOG_ERROR("BQT: Msg(A) - Broker parse error.");
            break;
          }

          if(!moveOn(currentPos))
            break;

          // Parse datetime
          std::strncpy(datetime, currentPos, MAX_STRING_SIZE);

          if(!moveOn(currentPos))
            break;

          // Parse orderID
          std::strncpy(orderID, currentPos, MAX_STRING_SIZE);

          if(!moveOn(currentPos))
            break;

          offerType = *currentPos;

          break;
        }
        case 'U': // Modify order
        {
          if(!toInt(position, currentPos))
          {
            LOG_ERROR("BQT: Msg(U) - Position parse error.");
            break;
          }

          if(!moveOn(currentPos))
            break;

          if(!toInt(oldPosition, currentPos))
          {
            LOG_ERROR("BQT: Msg(U) - OldPosition parse error.");
            break;
          }

          if(!moveOn(currentPos))
            break;

          direction = *currentPos++;

          if(!moveOn(currentPos))
            break;

          if (!toDouble(price, currentPos))
          {
            LOG_ERROR("BQT: Msg(U) - Price parse error.");
            break;
          }

          if(!moveOn(currentPos))
            break;

          if (!toInt(quantity, currentPos))
          {
            LOG_ERROR("BQT: Msg(U) - Quantity parse error.");
            break;
          }

          if(!moveOn(currentPos))
            break;

          if (!toInt(broker, currentPos))
          {
            LOG_ERROR("BQT: Msg(U) - Broker parse error.");
            break;
          }

          if(!moveOn(currentPos))
            break;

          // Parse datetime
          std::strncpy(datetime, currentPos, MAX_STRING_SIZE);

          if(!moveOn(currentPos))
            break;

          // Parse orderID
          std::strncpy(orderID, currentPos, MAX_STRING_SIZE);

          if(!moveOn(currentPos))
            break;

          offerType = *currentPos;

          break;
        }
        case 'D': // Delete order
        {
          if (!toInt(cancelType, currentPos))
          {
            LOG_ERROR("BQT: Msg(D) - CancelType parse error.");
            break;
          }

          if(cancelType == 3)
            break;

          if(!moveOn(currentPos))
            break;

          direction = *currentPos++;

          if(!moveOn(currentPos))
            break;

          if (!toInt(position, currentPos))
          {
            LOG_ERROR("BQT: Msg(D) - Position parse error.");
            break;
          }

          break;
        }
        default:
          std::cerr << "Unknown message type: " << msgType << std::endl;
          break;
      }
    }
  };
}


#endif //CEDRO_MD_BQTMODEL_H
