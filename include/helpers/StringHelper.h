////
//// Created by Arthur Motelevicz on 30/07/24.
////
//
//#ifndef CEDRO_MD_STRINGHELPER_H
//#define CEDRO_MD_STRINGHELPER_H
//
//#include <string>
//#include <stdexcept>
//#include <chrono>
//#include <iomanip>
//#include <sstream>
//#include <string>
//#include <functional>
//#include <cmath>
//#include <limits>
//#include <algorithm>
//#include <cctype>
//
//namespace cedro::md
//{
//  inline static int64_t convertToMillis(const std::string& timeStr)
//  {
//    if (timeStr.length() != 6 && timeStr.length() != 9)
//    {
//      throw std::invalid_argument("Invalid time string length");
//    }
//
//    int hours = std::stoi(timeStr.substr(0, 2));
//    int minutes = std::stoi(timeStr.substr(2, 2));
//    int seconds = std::stoi(timeStr.substr(4, 2));
//    int millis = (timeStr.length() == 9) ? std::stoi(timeStr.substr(6, 3)) : 0;
//
//    if (hours < 0 || hours >= 24 ||
//        minutes < 0 || minutes >= 60 ||
//        seconds < 0 || seconds >= 60 ||
//        millis < 0 || millis >= 1000) {
//      throw std::invalid_argument("Invalid time values");
//    }
//
//    long long totalMillis = hours * 3600LL * 1000LL
//                            + minutes * 60LL * 1000LL
//                            + seconds * 1000LL
//                            + millis;
//    return totalMillis;
//  }
//}
//#endif //CEDRO_MD_STRINGHELPER_H
