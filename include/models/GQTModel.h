//
// Created by Arthur Motelevicz on 09/08/24.
//

#ifndef CEDRO_MD_GQTMODEL_H
#define CEDRO_MD_GQTMODEL_H

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "CMDTypes.h"

namespace cedro::md::models
{
  class GQTModel
  {
  public:
    char symbol[MAX_STRING_SIZE]="";
    char msgType{'\0'};

    char operation{'\0'};
    char time[MAX_STRING_SIZE]="";
    double price{dNaN};
    int32_t buyerBroker{INVALID_INT32};
    int32_t sellerBroker{INVALID_INT32};
    int32_t quantity{INVALID_INT32};
    char tradeID[MAX_STRING_SIZE]="";
    int32_t direct{INVALID_INT32};
    char aggressor{'\0'};
    char requestID[MAX_STRING_SIZE]="";

    void setIsSnapshot(bool snap)
    {
      _isSnapshot = snap;
    }

    bool isSnapshot() const
    {
      return _isSnapshot;
    }

    void parseGQTMessage(const char* message, size_t length)
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

      const char* secondColon = std::strchr(firstColon + 1, ':');
      if (msgType == 'E' && secondColon == nullptr)
      {
        LOG_INFO("GQT: End of initial stream data received for symbol: " + std::string(symbol));
        return;
      }

      // Move to after msgType/operation column ':'
      const char* currentPos = secondColon + 1;

      if(msgType != 'E')
        operation = msgType;

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
          LOG_ERROR("GQT: Unexpected end of data.");
          return false;
        }
        currentPos++; // Skips the ':'
        return true;
      };

      switch (msgType)
      {
        case 'A': // Add trade
        {
          std::strncpy(time, currentPos, MAX_STRING_SIZE);
          if (!moveOn(currentPos)) break;

          if (!toDouble(price, currentPos)) break;
          if (!moveOn(currentPos)) break;

          if (!toInt(buyerBroker, currentPos)) break;
          if (!moveOn(currentPos)) break;

          if (!toInt(sellerBroker, currentPos)) break;
          if (!moveOn(currentPos)) break;

          if (!toInt(quantity, currentPos)) break;
          if (!moveOn(currentPos)) break;

          std::strncpy(tradeID, currentPos, MAX_STRING_SIZE);
          if (!moveOn(currentPos)) break;

          if(_isSnapshot)
          {
            std::strncpy(requestID, currentPos, MAX_STRING_SIZE);
            if (!moveOn(currentPos)) break;
          }

          if (!toInt(direct, currentPos)) break;
          if (!moveOn(currentPos)) break;

          aggressor = *currentPos;
          break;
        }
        case 'D': // Remove trade
        {
          std::strncpy(tradeID, currentPos, MAX_STRING_SIZE);
          break;
        }
        case 'R': // Remove all trades
        {
          break;
        }
        case 'E': // End of messages with requested id (needs to be snapshot)
        {
          if(_isSnapshot)
            std::strncpy(requestID, currentPos, MAX_STRING_SIZE);
          break;
        }
        default:
          std::cerr << "Unknown operation type: " << operation << std::endl;
          break;
      }
    }
  private:
    bool _isSnapshot = false;
  };
}

#endif //CEDRO_MD_GQTMODEL_H
