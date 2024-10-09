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
#include "ParseHelper.h"

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
        logI << ("GQT: End of initial stream data received for symbol: " + std::string(symbol));
        return;
      }

      // Move to after msgType/operation column ':'
      const char* currentPos = secondColon + 1;

      if(msgType != 'E')
        operation = msgType;

      switch (msgType)
      {
        case 'A': // Add trade
        {
          if(!ParseHelper::copyUntilDelimiter(time, currentPos, MAX_STRING_SIZE)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          if (!ParseHelper::toDouble(price, currentPos)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          if (!ParseHelper::toInt(buyerBroker, currentPos)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          if (!ParseHelper::toInt(sellerBroker, currentPos)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          if (!ParseHelper::toInt(quantity, currentPos)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          if (!ParseHelper::copyUntilDelimiter(tradeID, currentPos, MAX_STRING_SIZE)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          if(_isSnapshot)
          {
            if (!ParseHelper::copyUntilDelimiter(requestID, currentPos, MAX_STRING_SIZE)) break;
            if (!ParseHelper::moveOn(currentPos)) break;
          }

          if (!ParseHelper::toInt(direct, currentPos)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          aggressor = *currentPos;
          break;
        }
        case 'D': // Remove trade
        {
          ParseHelper::copyUntilDelimiter(tradeID, currentPos, MAX_STRING_SIZE);
          break;
        }
        case 'R': // Remove all trades
        {
          break;
        }
        case 'E': // End of messages with requested id (needs to be snapshot)
        {
          if(_isSnapshot)
            ParseHelper::copyUntilDelimiter(requestID, currentPos, MAX_STRING_SIZE);
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
