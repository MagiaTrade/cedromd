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
#include "ParseHelper.h"

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
        logI << ("End of initial data received for symbol: " + std::string(symbol));
        return;
      }

      // Move to after msgType column ':'
      const char* currentPos = firstColon + 3;

      switch (msgType)
      {
        case 'A': // Add order
        {
          if(!ParseHelper::toInt(position, currentPos))
          {
            logE << ("BQT: Msg(A) - Position parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          direction = *currentPos++;

          if(!ParseHelper::moveOn(currentPos))
            break;

          if (!ParseHelper::toDouble(price, currentPos))
          {
            logE << ("BQT: Msg(A) - Price parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          if (!ParseHelper::toInt(quantity, currentPos))
          {
            logE << ("BQT: Msg(A) - Quantity parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          if (!ParseHelper::toInt(broker, currentPos))
          {
            logE << ("BQT: Msg(A) - Broker parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          if (!ParseHelper::copyUntilDelimiter(datetime, currentPos, MAX_STRING_SIZE))
          {
            logE << ("BQT: Msg(A) - Datetime parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          // Parse orderID
          if (!ParseHelper::copyUntilDelimiter(orderID, currentPos, MAX_STRING_SIZE))
          {
            logE << ("BQT: Msg(A) - orderID parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          offerType = *currentPos;

          break;
        }
        case 'U': // Modify order
        {
          if(!ParseHelper::toInt(position, currentPos))
          {
            logE << ("BQT: Msg(U) - Position parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          if(!ParseHelper::toInt(oldPosition, currentPos))
          {
            logE << ("BQT: Msg(U) - OldPosition parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          direction = *currentPos++;

          if(!ParseHelper::moveOn(currentPos))
            break;

          if (!ParseHelper::toDouble(price, currentPos))
          {
            logE << ("BQT: Msg(U) - Price parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          if (!ParseHelper::toInt(quantity, currentPos))
          {
            logE << ("BQT: Msg(U) - Quantity parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          if (!ParseHelper::toInt(broker, currentPos))
          {
            logE << ("BQT: Msg(U) - Broker parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          // Parse datetime
          if (!ParseHelper::copyUntilDelimiter(datetime, currentPos, MAX_STRING_SIZE))
          {
            logE << ("BQT: Msg(U) - datetime parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          // Parse orderID
          if (!ParseHelper::copyUntilDelimiter(orderID, currentPos, MAX_STRING_SIZE))
          {
            logE << ("BQT: Msg(U) - orderID parse error.");
            break;
          }

          if(!ParseHelper::moveOn(currentPos))
            break;

          offerType = *currentPos;

          break;
        }
        case 'D': // Delete order
        {
          if (!ParseHelper::toInt(cancelType, currentPos))
          {
            logE << ("BQT: Msg(D) - CancelType parse error.");
            break;
          }

          if(cancelType == 3)
            break;

          if(!ParseHelper::moveOn(currentPos))
            break;

          direction = *currentPos++;

          if(!ParseHelper::moveOn(currentPos))
            break;

          if (!ParseHelper::toInt(position, currentPos))
          {
            logE << ("BQT: Msg(D) - Position parse error.");
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
