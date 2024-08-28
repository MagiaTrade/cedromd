//
// Created by Arthur Motelevicz on 30/07/24.
//
#include "TestsHelper.h"
#include <cedromd>

#define SYMBOL_TO_TEST "wdou24"

TEST_CASE("COMMANDS")
{
  cedro::md::CMDBaseManager manager(CEDRO_USERNAME, CEDRO_PASSWORD, CEDRO_SOFTKEY);

  std::promise<bool> sendPromise;
  std::future<bool> sendFuture = sendPromise.get_future();

  std::shared_ptr<bb::network::rs::Stream> streamPtr;

  manager.connect([&](bool success, const std::shared_ptr<bb::network::rs::Stream>& stream)
  {
    streamPtr = stream;
    sendPromise.set_value(success);
  });

  TestHelper::waitForSuccess(sendFuture, streamPtr, 3);

  manager.setErrorCallback([&](const cedro::md::Error& error, const std::string& msg)
  {
    LOG_WARNING("Error: " + error.toString() + " Msg: " + msg);
  });

  SECTION("SQT snapshot")
  {
    std::promise<bool> sendSQTPromise;
    std::future<bool> sendSQTFuture = sendSQTPromise.get_future();
    bool isSnapshot = true;
    bool promiseSet = false;

    manager.subscribeQuote(SYMBOL_TO_TEST,
    [&](bool success, const char* data, size_t size)
    {
      if(promiseSet)
        return;

      auto *startMsg = std::strstr(data, "T:");
      auto *endMsg = std::strchr(data, '!');
      REQUIRE(startMsg != nullptr);
      REQUIRE(endMsg != nullptr);
      REQUIRE(success);
      REQUIRE(size > 250);
      LOG_INFO(data);
      sendSQTPromise.set_value(success);
      promiseSet = true;

    }, isSnapshot);

    TestHelper::waitForSuccess(sendSQTFuture, streamPtr, 5);
  }
//
//  SECTION("SQT stream")
//  {
//    std::promise<bool> sendSQTPromise;
//    std::future<bool> sendSQTFuture = sendSQTPromise.get_future();
//    int countMsgs = 0;
//    bool isSnapshot = false;
//    bool promiseSet = false;
//
//    manager.subscribeQuote(SYMBOL_TO_TEST,
//    [&](bool success, const char* data, size_t size)
//    {
//      countMsgs++;
//      if(countMsgs < 5)
//        return;
//
//      if(promiseSet)
//        return;
//
//      auto *startMsg = std::strstr(data, "T:");
//      auto *endMsg = std::strchr(data, '!');
//      REQUIRE(startMsg != nullptr);
//      REQUIRE(endMsg != nullptr);
//      REQUIRE(success);
//      REQUIRE(size < 100);
//
//      LOG_INFO(data);
//
//      sendSQTPromise.set_value(success);
//      promiseSet = true;
//    }, isSnapshot);
//
//    TestHelper::waitForSuccess(sendSQTFuture, streamPtr, 5);
//
//    SECTION("SQT stream unsubscribe")
//    {
//      std::promise<bool> sendUnsubPromise;
//      std::future<bool> sendUnsubFuture = sendUnsubPromise.get_future();
//      manager.unsubscribeQuote(SYMBOL_TO_TEST,
//     [&](bool success)
//     {
//       REQUIRE(success);
//       sendUnsubPromise.set_value(success);
//     });
//
//      TestHelper::waitForSuccess(sendUnsubFuture, streamPtr, 5);
//    }
//  }
//
//  SECTION("BQT stream")
//  {
//    std::promise<bool> sendBQTPromise;
//    std::future<bool> sendBQTFuture = sendBQTPromise.get_future();
//    int countMsgs = 0;
//    bool promiseSet = false;
//
//    manager.subscribeBookQuote(SYMBOL_TO_TEST,
//    [&](bool success, const char* data, size_t size)
//    {
//      countMsgs++;
//      if(countMsgs < 5)
//        return;
//
//      if(promiseSet)
//        return;
//
//      auto *startMsg = std::strstr(data, "B:");
//      REQUIRE(startMsg != nullptr);
//      REQUIRE(success);
//      REQUIRE(size < 100);
//      LOG_INFO(data);
//      sendBQTPromise.set_value(success);
//      promiseSet = true;
//    });
//
//    TestHelper::waitForSuccess(sendBQTFuture, streamPtr, 5);
//
//    SECTION("BQT stream unsubscribe")
//    {
//      std::promise<bool> sendUnsubPromise;
//      std::future<bool> sendUnsubFuture = sendUnsubPromise.get_future();
//      manager.unsubscribeBookQuote(SYMBOL_TO_TEST,
//      [&](bool success)
//      {
//       REQUIRE(success);
//       sendUnsubPromise.set_value(success);
//      });
//
//      TestHelper::waitForSuccess(sendUnsubFuture, streamPtr, 5);
//    }
//  }
//
//  SECTION("SAB stream")
//  {
//    std::promise<bool> sendSABPromise;
//    std::future<bool> sendSABFuture = sendSABPromise.get_future();
//    int countMsgs = 0;
//    bool promiseSet = false;
//
//    manager.subscribeAggBook(SYMBOL_TO_TEST,
//    [&](bool success, const char* data, size_t size)
//    {
//      countMsgs++;
//      if(countMsgs < 5)
//       return;
//
//      if(promiseSet)
//       return;
//
//      auto *startMsg = std::strstr(data, "Z:");
//      REQUIRE(startMsg != nullptr);
//      REQUIRE(success);
//      REQUIRE(size < 100);
//      LOG_INFO(data);
//      sendSABPromise.set_value(success);
//      promiseSet = true;
//    });
//
//    TestHelper::waitForSuccess(sendSABFuture, streamPtr, 5);
//
//    SECTION("SAB stream unsubscribe")
//    {
//      std::promise<bool> sendUnsubPromise;
//      std::future<bool> sendUnsubFuture = sendUnsubPromise.get_future();
//      manager.unsubscribeAggBook(SYMBOL_TO_TEST,
//     [&](bool success)
//     {
//       REQUIRE(success);
//       sendUnsubPromise.set_value(success);
//     });
//
//      TestHelper::waitForSuccess(sendUnsubFuture, streamPtr, 5);
//    }
//  }
//
//  SECTION("GQT stream")
//  {
//    std::promise<bool> sendGQTPromise;
//    std::future<bool> sendGQTFuture = sendGQTPromise.get_future();
//    int countMsgs = 0;
//    bool promiseSet = false;
//    manager.subscribeQuoteTrades(SYMBOL_TO_TEST,
//    [&](bool success, const char* data, size_t size)
//    {
//      countMsgs++;
//      if(countMsgs < 5)
//        return;
//
//      if(promiseSet)
//        return;
//
//      auto *startMsg = std::strstr(data, "V:");
//      REQUIRE(startMsg != nullptr);
//      REQUIRE(success);
//      REQUIRE(size < 100);
//      LOG_INFO(data);
//
//      sendGQTPromise.set_value(true);
//      promiseSet = true;
//    });
//
//    TestHelper::waitForSuccess(sendGQTFuture, streamPtr, 10);
//
//    SECTION("GQT stream unsubscribe")
//    {
//      std::promise<bool> sendUnsubPromise;
//      std::future<bool> sendUnsubFuture = sendUnsubPromise.get_future();
//      manager.unsubscribeQuoteTrades(SYMBOL_TO_TEST,
//      [&](bool success)
//      {
//       REQUIRE(success);
//       sendUnsubPromise.set_value(success);
//      });
//
//      TestHelper::waitForSuccess(sendUnsubFuture, streamPtr, 5);
//    }
//  }
//
//  /**
//   * This is the most problematic section so far
//   * the reason is that sometimes requesting quotes in sequence the callback comes
//   * with the end of message flag to true as the first message and no messages are delivered at all.
//   * TODO:: talk to Rodrigo of Cedro about it.
//   */
//  SECTION("GQT snapshot")
//  {
//    for(int i = 1; i <= 1; i++)
//    {
//      std::promise<bool> promiseGQTSnap;
//      std::future<bool> futureGQTSnap = promiseGQTSnap.get_future();
//      size_t numberOfTrades = 10 * i;
//      size_t countMessages = 0;
//      manager.snapshotQuoteTrades(SYMBOL_TO_TEST, numberOfTrades,
//      [&](bool success, const char *data, size_t size, bool isEndOfMessage)
//      {
//        auto *startMsg = std::strstr(data, "V:");
//        REQUIRE(startMsg != nullptr);
//
//        if (isEndOfMessage)
//          promiseGQTSnap.set_value(true);
//        else
//          countMessages++;
//      });
//
//      TestHelper::waitForSuccess(futureGQTSnap, streamPtr, 5);
//
//      REQUIRE((countMessages == numberOfTrades || countMessages == 0));
//    }
//  }
//
//  SECTION("VAP Normal snapshot")
//  {
//    std::promise<bool> promiseVAP;
//    std::future<bool> futureVAP = promiseVAP.get_future();
//
//    manager.snapshotVolumeAtPrice(SYMBOL_TO_TEST,
//    [&](bool success, const char *data, size_t size, bool isEndOfMessage, cedro::md::VAPRequestInfo::Type requestedType)
//    {
//      auto *startMsg = std::strstr(data, "VAP:");
//      REQUIRE(startMsg != nullptr);
//
//      if (isEndOfMessage)
//        promiseVAP.set_value(true);
//    });
//
//    TestHelper::waitForSuccess(futureVAP, streamPtr, 5);
//  }
//
//  SECTION("VAP Minute snapshot")
//  {
//    std::promise<bool> promiseVAP;
//    std::future<bool> futureVAP = promiseVAP.get_future();
//    int32_t minutes = 60;
//    manager.snapshotVolumeAtPriceLastMinutes(
//      SYMBOL_TO_TEST,
//      [&](bool success, const char *data, size_t size, bool isEndOfMessage, cedro::md::VAPRequestInfo::Type requestedType)
//      {
//        auto *startMsg = std::strstr(data, "VAP:");
//        REQUIRE(startMsg != nullptr);
//        LOG_INFO(data);
//        if (isEndOfMessage)
//          promiseVAP.set_value(true);
//      }, minutes);
//
//    TestHelper::waitForSuccess(futureVAP, streamPtr, 10);
//  }
//
//  SECTION("VAP snapshot history")
//  {
//    std::promise<bool> promiseVAP;
//    std::future<bool> futureVAP = promiseVAP.get_future();
//    std::string startDate = "20240801";
//    std::string endDate = "20240807";
//    bool acc = false;
//
//    manager.snapshotVolumeAtPriceHistory(
//      SYMBOL_TO_TEST,
//      [&](bool success, const char *data, size_t size, bool isEndOfMessage, cedro::md::VAPRequestInfo::Type requestedType)
//      {
//        auto *startMsg = std::strstr(data, "VAP:");
//        REQUIRE(startMsg != nullptr);
//        LOG_INFO(data);
//        if (isEndOfMessage)
//          promiseVAP.set_value(true);
//      },
//      startDate,
//      endDate,
//      acc);
//
//    TestHelper::waitForSuccess(futureVAP, streamPtr, 5);
//  }
//
//  SECTION("VAP snapshot history accumulated")
//  {
//    std::promise<bool> promiseVAP;
//    std::future<bool> futureVAP = promiseVAP.get_future();
//    std::string startDate = "20240801";
//    std::string endDate = "20240807";
//    bool acc = true;
//
//    manager.snapshotVolumeAtPriceHistory(
//      SYMBOL_TO_TEST,
//      [&](bool success, const char *data, size_t size, bool isEndOfMessage, cedro::md::VAPRequestInfo::Type requestedType)
//      {
//        auto *startMsg = std::strstr(data, "VAP:");
//        REQUIRE(startMsg != nullptr);
//        LOG_INFO(data);
//        if (isEndOfMessage)
//          promiseVAP.set_value(true);
//      },
//      startDate,
//      endDate,
//      acc);
//
//    TestHelper::waitForSuccess(futureVAP, streamPtr, 5);
//  }

  SECTION("GPN: get players")
  {
    std::promise<bool> promiseGPN;
    std::future<bool> futureGPN = promiseGPN.get_future();
    bool sortedByName = true;

    bool passou = false;
    bool fechou = false;
    manager.getPlayerNames("bmf", sortedByName,
    [&](bool success, const char *data, size_t size, bool isEndOfMessages)
    {
      auto *startMsg = std::strstr(data, "G:");
      REQUIRE(startMsg != nullptr);
      REQUIRE(success);
      if(isEndOfMessages)
        promiseGPN.set_value(true);
    });

    TestHelper::waitForSuccess(futureGPN, streamPtr, 10);
  }

}
