//
// Created by Arthur Motelevicz on 09/08/24.
//

#ifndef CEDRO_MD_SABMODEL_H
#define CEDRO_MD_SABMODEL_H


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
  class SABModel
  {
  public:
    char symbol[MAX_STRING_SIZE]="";
    char msgType{'\0'};

    int32_t position{INVALID_INT32};
    char direction{'\0'};
    double price{dNaN};
    int32_t quantity{INVALID_INT32};
    int32_t numOfOffers{INVALID_INT32};
    char dateTime[MAX_STRING_SIZE]="";
    int32_t cancelType{INVALID_INT32};

    void parseSABMessage(const char* message, size_t length)
    {
      // Remove the prefix "Z:"
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
        logI << ("SAB: End of initial data received for symbol: " + std::string(symbol));
        return;
      }

      // Move to after msgType column ':'
      const char* currentPos = firstColon + 3;

      switch (msgType)
      {
        case 'A': // Add order
        case 'U': // Update order
        {
          if (!ParseHelper::toInt(position, currentPos)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          direction = *currentPos++;

          if (!ParseHelper::moveOn(currentPos)) break;

          if (!ParseHelper::toDouble(price, currentPos)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          if (!ParseHelper::toInt(quantity, currentPos)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          if (!ParseHelper::toInt(numOfOffers, currentPos)) break;
          if (!ParseHelper::moveOn(currentPos)) break;

          ParseHelper::copyUntilDelimiter(dateTime, currentPos, MAX_STRING_SIZE);
          break;
        }
        case 'D': // Cancel order
        {
          if (!ParseHelper::toInt(cancelType, currentPos)) break;

          if (cancelType == 3) break;

          if (!ParseHelper::moveOn(currentPos)) break;

          direction = *currentPos++;

          if (!ParseHelper::moveOn(currentPos)) break;

          if (!ParseHelper::toInt(position, currentPos)) break;

          break;
        }
        default:
          logE << ("SAB: Unknown message type received.");
          break;
      }
    }
  };
}


#endif //CEDRO_MD_SABMODEL_H
