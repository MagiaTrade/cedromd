//
// Created by Arthur Motelevicz on 30/07/24.
//

#ifndef CEDRO_MD_TESTSHELPER_H
#define CEDRO_MD_TESTSHELPER_H

#include <beastboys>
#include "catch2/catch.hpp"

class TestHelper{
public:
  inline static void waitForSuccess(std::future<bool>& future, std::shared_ptr<bb::network::rs::Stream>& streamPtr, size_t seconds = 10)
  {
    if (future.wait_for(std::chrono::seconds(seconds)) == std::future_status::ready)
    {
      bool success = future.get();
      REQUIRE(success);
      REQUIRE(streamPtr != nullptr);
      REQUIRE(streamPtr->isOpen());
    } else
    {
      logE << ("Timeout waiting for connection callback.");
      REQUIRE(false); // Force test failure on timeout
    }

  }

  inline static void waitForFail(std::future<bool>& future, std::shared_ptr<bb::network::rs::Stream>& streamPtr, size_t seconds = 10)
  {
    if (future.wait_for(std::chrono::seconds(seconds)) == std::future_status::ready)
    {
      bool success = future.get();
      REQUIRE_FALSE(success);
      REQUIRE(streamPtr == nullptr);
    } else
    {
      logE << ("Timeout waiting for connection callback.");
      REQUIRE(false); // Force test failure on timeout
    }
  }


};


#endif //CEDRO_MD_TESTSHELPER_H
