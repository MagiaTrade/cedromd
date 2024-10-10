//
// Created by Arthur Motelevicz on 09/10/24.
//

#ifndef MMDPERSISTOR_PARSEHELPER_H
#define MMDPERSISTOR_PARSEHELPER_H

#include <string>
#include <mgutils/Utils.h>
#include <mgutils/Logger.h>

namespace cedro::md
{

  class ParseHelper
  {
  public:

    inline static std::string trim(const std::string &str)
    {
      size_t first = str.find_first_not_of(" \r\n");
      if (first == std::string::npos)
        return "";
      size_t last = str.find_last_not_of(" \r\n");
      return str.substr(first, last - first + 1);
    }

    inline static bool copyUntilDelimiter(char *dest, const char *source, size_t maxSize, char delimiter = ':')
    {
      const char *end = std::strchr(source, delimiter);
      if (end == nullptr)
        return false; // Não encontrou o delimitador

      size_t length = std::min(static_cast<size_t>(end - source),
                               maxSize - 1); // Garante que não ultrapasse o tamanho do buffer
      std::strncpy(dest, source, length);
      dest[length] = '\0'; // Garante que a string seja terminada corretamente

      return true;
    };

    inline static bool toInt(int32_t &out, const char *inStart)
    {
      char *outEnd;
      long value = std::strtol(inStart, &outEnd, 10);

      if (value == INVALID_INT32 || outEnd == inStart)
      {
        out = INVALID_INT32;
        return false;
      }

      out = static_cast<int32_t>(value);
      return true;
    };

    inline static bool toDouble(double &out, const char *inStart)
    {
      char *outEnd;
      double value = std::strtod(inStart, &outEnd);

      if (std::isnan(value) || outEnd == inStart)
      {
        out = dNaN;
        return false;
      }

      out = value;
      return true;
    };

    inline static bool moveOn(const char *&currentPos, char delimiter = ':', bool shouldLogError = true)
    {
      currentPos = std::strchr(currentPos, delimiter);
      if (currentPos == nullptr)
      {
        if(shouldLogError)
          logE << ("Unexpected end of data.");
        return false;
      }

      currentPos++; // Skips the delimiter
      return true;
    }
  };
}
#endif //MMDPERSISTOR_PARSEHELPER_H
