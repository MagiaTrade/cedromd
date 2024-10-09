//
// Created by Arthur Motelevicz on 09/08/24.
//

#ifndef CEDRO_MD_VAPMODEL_H
#define CEDRO_MD_VAPMODEL_H

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
  class VAPModel
  {
  public:
    char symbol[MAX_STRING_SIZE] = "";
    /**
     * N - Normal
     * M - Minutes
     * P - Period
     * E - EndOfMessages
     */
    char msgType{'\0'};

    double tradedPrice{dNaN};
    double buyerTrades{dNaN};
    double buyerVolume{dNaN};
    double sellerTrades{dNaN};
    double sellerVolume{dNaN};
    double directTrades{dNaN};
    double directVolume{dNaN};
    double undefinedTrades{dNaN};
    double undefinedVolume{dNaN};
    double rlpTrades{dNaN};
    double rlpVolume{dNaN};
    int32_t period{INVALID_INT32};
    char dateRange[MAX_STRING_SIZE] = "";

    void parseVAPMessage(const char* message, size_t length, VAPRequestInfo::Type requestedType)
    {
      // Skip "VAP:"
      const char* content = message + 4;
      size_t contentLength = length - 4;

      const char* firstColon = std::strchr(content, ':');
      if (firstColon == nullptr || firstColon - content >= contentLength)
          return;

      size_t symbolLength = firstColon - content;
      std::strncpy(symbol, content, symbolLength);
      symbol[symbolLength] = '\0';

      msgType = *(firstColon + 1);

      if (length <= 40 && msgType == 'E')
      {
        logI << ("VAP: End of snapshot data received for symbol: " + std::string(symbol));
        return;
      }

      const char* currentPos = firstColon + 1;

      ParseHelper::toDouble(tradedPrice, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      ParseHelper::toDouble(buyerTrades, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      ParseHelper::toDouble(buyerVolume, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      ParseHelper::toDouble(sellerTrades, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      ParseHelper::toDouble(sellerVolume, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      ParseHelper::toDouble(directTrades, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      ParseHelper::toDouble(directVolume, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      ParseHelper::toDouble(undefinedTrades, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      ParseHelper::toDouble(undefinedVolume, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      if(requestedType == VAPRequestInfo::NORMAL ||
          requestedType == VAPRequestInfo::MINUTE)
      {
        msgType = requestedType == VAPRequestInfo::NORMAL ?  'N' : 'M';
        ParseHelper::toInt(period, currentPos);
        if (!ParseHelper::moveOn(currentPos)) return;
      }
      else if(requestedType == VAPRequestInfo::HISTORY)
      {
        msgType = 'H';
        std::strncpy(dateRange, currentPos, MAX_STRING_SIZE);
        if (!ParseHelper::moveOn(currentPos)) return;
      }

      ParseHelper::toDouble(rlpTrades, currentPos);
      if (!ParseHelper::moveOn(currentPos)) return;

      ParseHelper::toDouble(rlpVolume, currentPos);
    }
  };
}

#endif //CEDRO_MD_VAPMODEL_H
