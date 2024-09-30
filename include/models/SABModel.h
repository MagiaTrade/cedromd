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
          logE << ("SAB: Unexpected end of data.");
          return false;
        }

        currentPos++; // Skips the ':'
        return true;
      };

      switch (msgType)
      {
        case 'A': // Add order
        case 'U': // Update order
        {
          if (!toInt(position, currentPos)) break;
          if (!moveOn(currentPos)) break;

          direction = *currentPos++;

          if (!moveOn(currentPos)) break;

          if (!toDouble(price, currentPos)) break;
          if (!moveOn(currentPos)) break;

          if (!toInt(quantity, currentPos)) break;
          if (!moveOn(currentPos)) break;

          if (!toInt(numOfOffers, currentPos)) break;
          if (!moveOn(currentPos)) break;

          std::strncpy(dateTime, currentPos, MAX_STRING_SIZE);
          break;
        }
        case 'D': // Cancel order
        {
          if (!toInt(cancelType, currentPos)) break;

          if (cancelType == 3) break;

          if (!moveOn(currentPos)) break;

          direction = *currentPos++;

          if (!moveOn(currentPos)) break;

          if (!toInt(position, currentPos)) break;

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
