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
#include "StringHelper.h"

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

      char delimiter = ':';
      const char* errMsg = "VAP: Unexpected end of data.";

      toDouble(tradedPrice, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toDouble(buyerTrades, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toDouble(buyerVolume, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toDouble(sellerTrades, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toDouble(sellerVolume, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toDouble(directTrades, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toDouble(directVolume, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toDouble(undefinedTrades, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toDouble(undefinedVolume, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      if(requestedType == VAPRequestInfo::NORMAL ||
          requestedType == VAPRequestInfo::MINUTE)
      {
        msgType = requestedType == VAPRequestInfo::NORMAL ?  'N' : 'M';
        toInt(period, currentPos);
        if (!moveOn(currentPos, delimiter, errMsg)) return;
      }
      else if(requestedType == VAPRequestInfo::HISTORY)
      {
        msgType = 'H';
        std::strncpy(dateRange, currentPos, MAX_STRING_SIZE);
        if (!moveOn(currentPos, delimiter, errMsg)) return;
      }

      toDouble(rlpTrades, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toDouble(rlpVolume, currentPos);
    }
  };
}

#endif //CEDRO_MD_VAPMODEL_H
