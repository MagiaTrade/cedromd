//
// Created by Arthur Motelevicz on 10/08/24.
//

#ifndef CEDRO_MD_GPNMODEL_H
#define CEDRO_MD_GPNMODEL_H

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
  class GPNModel
  {
  public:
    char market[MAX_STRING_SIZE] = "";

    /**
      * M - Message
      * E - EndOfMessages
    */
    char msgType{'\0'};

    int32_t brokerCode{INVALID_INT32};
    char brokerName[MAX_STRING_SIZE] = "";
    int32_t brokerCodeAtBank{INVALID_INT32};
    int32_t marketCode{INVALID_INT32};

    void parseGPNMessage(const char* message, size_t length)
    {
      // Skip "G:"
      const char* content = message + 2;
      size_t contentLength = length - 2;

      const char* firstColon = std::strchr(content, ':');
      if(firstColon != nullptr && firstColon - content >= contentLength)
        return;

      size_t marketNameLength = firstColon - content;
      std::strncpy(market, content, marketNameLength);
      market[marketNameLength] = '\0';

      msgType = *(firstColon + 1);

      if (length <= 10 && msgType == 'E')
      {
        logI << ("GPN: End of data received for market: " + std::string(market));
        return;
      }

      msgType = 'M';

      const char* currentPos = firstColon + 1;

      char delimiter = ':';
      const char* errMsg = "VAP: Unexpected end of data.";

      toInt(brokerCode, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      std::strncpy(brokerName, currentPos, MAX_STRING_SIZE);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toInt(brokerCodeAtBank, currentPos);
      if (!moveOn(currentPos, delimiter, errMsg)) return;

      toInt(marketCode, currentPos);
    }
  };
}
#endif //CEDRO_MD_GPNMODEL_H
