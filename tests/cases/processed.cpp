//
// Created by Arthur Motelevicz on 08/08/24.
//
#include "TestsHelper.h"
#include <cedromd>

#define SYMBOL_TO_TEST "WDOV24"

TEST_CASE("Processed Subscribe Quote - SQT")
{
  cedro::md::CMDProcessedManager manager(CEDRO_USERNAME, CEDRO_PASSWORD, CEDRO_SOFTKEY);

  std::promise<bool> sendPromise;
  std::future<bool> sendFuture = sendPromise.get_future();

  std::shared_ptr<bb::network::rs::Stream> streamPtr;

  manager.connect([&](bool success, const std::shared_ptr<bb::network::rs::Stream> &stream)
  {
    streamPtr = stream;
    sendPromise.set_value(success);
  });

  TestHelper::waitForSuccess(sendFuture, streamPtr, 3);


//
//  auto checkSQTModel = [](const cedro::md::models::SQTModel& model)
//  {
//    REQUIRE(strcmp(model.symbol, "") != 0);
//
//    // Verificações de todas as variáveis da estrutura SQTModel
//
//    // Header
//    REQUIRE(strcmp(model.symbol, "") != 0);
//    REQUIRE(strcmp(model.time, "") != 0);
//
//    // Campos principais
////        REQUIRE(strcmp(model.lastModTime, "") != 0);             //not coming
//    REQUIRE(strcmp(model.lastModDate, "") != 0);
//    REQUIRE(!std::isnan(model.lastTradePrice));
//    REQUIRE(!std::isnan(model.bestBidPrice));
//    REQUIRE(!std::isnan(model.bestAskPrice));
//    REQUIRE(strcmp(model.lastTradeTime, "") != 0);
//    REQUIRE(model.currentTradeSize != INVALID_INT32);
//    REQUIRE(model.lastTradeSize != INVALID_INT32);
//    REQUIRE(model.totalTrades != INVALID_INT32);
//    REQUIRE(model.totalVolume != INVALID_INT32);
//    REQUIRE(!std::isnan(model.totalFinancialVolume));
//    REQUIRE(!std::isnan(model.highestPriceOfDay));
//    REQUIRE(!std::isnan(model.lowestPriceOfDay));
//    REQUIRE(!std::isnan(model.previousDayClosePrice));
//    REQUIRE(!std::isnan(model.openingPrice));
//    REQUIRE(strcmp(model.bestBidTime, "") != 0);
//    REQUIRE(strcmp(model.bestAskTime, "") != 0);
//    REQUIRE(!std::isnan(model.bestBidVolume));
//    REQUIRE(!std::isnan(model.bestAskVolume));
//    REQUIRE(model.bestBidSize != INVALID_INT32);
//    REQUIRE(model.bestAskSize != INVALID_INT32);
//    REQUIRE(!std::isnan(model.variation));
//    REQUIRE(!std::isnan(model.lastWeekClosePrice));
//    REQUIRE(!std::isnan(model.lastMonthClosePrice));
//    REQUIRE(!std::isnan(model.lastYearClosePrice));
//    REQUIRE(!std::isnan(model.previousDayOpeningPrice));
//    REQUIRE(!std::isnan(model.previousDayHighestPrice));
//    REQUIRE(!std::isnan(model.previousDayLowestPrice));
//    REQUIRE(!std::isnan(model.averagePrice));
//    REQUIRE(!std::isnan(model.vhDaily));
//    REQUIRE(model.marketCode != INVALID_INT32);
//    REQUIRE(model.assetType != INVALID_INT32);
//    REQUIRE(model.standardLot != INVALID_INT32);
//    REQUIRE(strcmp(model.assetDescription, "") != 0);
//    REQUIRE(strcmp(model.classificationName, "") != 0);
//    REQUIRE(model.quoteForm != INVALID_INT32);
//    REQUIRE(strcmp(model.intradayDate, "") != 0);
//    REQUIRE(strcmp(model.lastTradeDate, "") != 0);
//    REQUIRE(strcmp(model.shortAssetDescription, "") != 0);
//    REQUIRE(strcmp(model.canceledTradeId, "") != 0);
//    REQUIRE(strcmp(model.lastTradeDateSimple, "") != 0);
//    REQUIRE(model.openingUnfulfilledSide != 'x');
//    REQUIRE(model.openingUnfulfilledSize != INVALID_INT32);
//    REQUIRE(strcmp(model.scheduledOpeningTime, "") != 0);
//    REQUIRE(strcmp(model.rescheduledOpeningTime, "") != 0);
//    REQUIRE(model.bestBidBroker != INVALID_INT32);
//    REQUIRE(model.bestAskBroker != INVALID_INT32);
//    REQUIRE(model.lastBuyBroker != INVALID_INT32);
//    REQUIRE(model.lastSellBroker != INVALID_INT32);
//    REQUIRE(strcmp(model.optionExpirationDate, "") != 0);
//    REQUIRE(model.expired != INVALID_INT8);
//    REQUIRE(strcmp(model.totalPapers, "") != 0);
//    REQUIRE(model.instrumentStatus != INVALID_INT32);
//    REQUIRE(model.optionType != '\0');
//    REQUIRE(model.optionDirection != '\0');
//    REQUIRE(strcmp(model.parentSymbol, "") != 0);
//    REQUIRE(!std::isnan(model.theoreticalOpeningPrice));
//    REQUIRE(model.theoreticalSize != INVALID_INT32);
//    REQUIRE(model.assetStatus != INVALID_INT32);
//    REQUIRE(!std::isnan(model.strikePrice));
//    REQUIRE(!std::isnan(model.diffPrice));
//    REQUIRE(strcmp(model.previousDay, "") != 0);
//    REQUIRE(strcmp(model.assetGroupPhase, "") != 0);
//    //      REQUIRE(!std::isnan(model.previousDayAveragePrice));    //not coming
//    //      REQUIRE(!std::isnan(model.marginRange));                //not coming
//    REQUIRE(!std::isnan(model.averageVolume20Days));
//    REQUIRE(!std::isnan(model.marketCapitalization));
//    REQUIRE(strcmp(model.marketType, "") != 0);
//    REQUIRE(!std::isnan(model.weekCloseVariation));
//    REQUIRE(!std::isnan(model.monthCloseVariation));
//    REQUIRE(!std::isnan(model.yearCloseVariation));
//    REQUIRE(model.openContracts != INVALID_INT32);
//    REQUIRE(model.businessDaysToExpiry != INVALID_INT32);
//    REQUIRE(model.daysToExpiry != INVALID_INT32);
//    REQUIRE(!std::isnan(model.adjustmentPrice));
//    REQUIRE(!std::isnan(model.previousDayAdjustmentPrice));
//    REQUIRE(strcmp(model.securityId, "") != 0);
//    REQUIRE(strcmp(model.tickDirection, "") != 0);
//    REQUIRE(!std::isnan(model.tunnelUpperLimit));
//    REQUIRE(!std::isnan(model.tunnelLowerLimit));
//    REQUIRE(strcmp(model.tradingPhase, "") != 0);
//    REQUIRE(model.tickSize != INVALID_INT32);
//    REQUIRE(model.minTradeVolume != INVALID_INT32);
//    REQUIRE(!std::isnan(model.minPriceIncrement));
//    REQUIRE(model.minOfferSize != INVALID_INT32);
//    REQUIRE(model.maxOfferSize != INVALID_INT32);
//    REQUIRE(model.uniqueInstrumentId != INVALID_INT32);
//    REQUIRE(strcmp(model.currency, "") != 0);
//    REQUIRE(strcmp(model.securityType, "") != 0);
//    REQUIRE(strcmp(model.securitySubType, "") != 0);
//    REQUIRE(model.associatedProduct != INVALID_INT32);
//    REQUIRE(strcmp(model.expiryMonthYear, "") != 0);
//    REQUIRE(!std::isnan(model.optionStrikePrice));
//    REQUIRE(strcmp(model.optionCurrency, "") != 0);
//    REQUIRE(!std::isnan(model.contractMultiplier));
//    REQUIRE(model.priceType != INVALID_INT32);
//    REQUIRE(strcmp(model.endOfTradeTime, "") != 0);
//    REQUIRE(strcmp(model.assetGroup, "") != 0);
//    REQUIRE(!std::isnan(model.currentAdjustmentRate));
//    REQUIRE(!std::isnan(model.previousAdjustmentRate));
//    REQUIRE(strcmp(model.currentAdjustmentDate, "") != 0);
//    REQUIRE(model.withdrawalsToExpiry != INVALID_INT32);
//    REQUIRE(!std::isnan(model.hourlyVolumeVariation));
//    REQUIRE(!std::isnan(model.cumulativeVolumeVariation));
//    REQUIRE(model.sectorCode != INVALID_INT32);
//    REQUIRE(model.subsectorCode != INVALID_INT32);
//    REQUIRE(model.segmentCode != INVALID_INT32);
//    REQUIRE(strcmp(model.adjustmentType, "") != 0);
//    REQUIRE(!std::isnan(model.referencePrice));
//    REQUIRE(strcmp(model.referenceDate, "") != 0);
//    REQUIRE(strcmp(model.lastModTimeMillis, "") != 0);
//    REQUIRE(strcmp(model.lastTradeTimeMillis, "") != 0);
//    REQUIRE(strcmp(model.bestBidTimeMillis, "") != 0);
//    REQUIRE(strcmp(model.bestAskTimeMillis, "") != 0);
//    REQUIRE(!std::isnan(model.adjustedPriceVariation));
//    REQUIRE(!std::isnan(model.diffAdjustedPrice));
//    REQUIRE(!std::isnan(model.tunnelUpperAuctionLimit));
//    REQUIRE(!std::isnan(model.tunnelLowerAuctionLimit));
//    REQUIRE(!std::isnan(model.tunnelUpperRejectionLimit));
//    REQUIRE(!std::isnan(model.tunnelLowerRejectionLimit));
//    REQUIRE(!std::isnan(model.tunnelUpperStaticLimit));
//    REQUIRE(!std::isnan(model.tunnelLowerStaticLimit));
//
//    /**
//     *  Fields exclusive for treasure.
//     *  Uncomment if you are testing it */
////        REQUIRE(std::isnan(model.unitPrice));
////        REQUIRE(std::isnan(model.rateValue));
////        REQUIRE(std::isnan(model.minApplicationValue));
////        REQUIRE(model.treasuryMarket == INVALID_INT32);
////        REQUIRE(strcmp(model.titleCode, "") == 0);
////        REQUIRE(model.typeCode == INVALID_INT32);
////        REQUIRE(strcmp(model.typeName, "") == 0);
////        REQUIRE(strcmp(model.selicCode, "") == 0);
////        REQUIRE(strcmp(model.issueDate, "") == 0);
////        REQUIRE(model.transactionId == INVALID_INT32);
////        REQUIRE(std::isnan(model.baseValue));
////        REQUIRE(std::isnan(model.buyRate));
////        REQUIRE(std::isnan(model.sellRate));
////        REQUIRE(model.indexerCode == INVALID_INT32);
////        REQUIRE(strcmp(model.indexerName, "") == 0);
////        REQUIRE(strcmp(model.titleName, "") == 0);
//
//  };
//
//  SECTION("SQT snapshot")
//  {
//    std::promise<bool> sendSQTPromise;
//    std::future<bool> sendSQTFuture = sendSQTPromise.get_future();
//    bool isSnapshot = true;
//    bool promiseSet = false;
//
//    manager.subscribeQuote(SYMBOL_TO_TEST,
//      [&](bool success, const cedro::md::models::SQTModel& model)
//      {
//        if (promiseSet)
//          return;
//
//        REQUIRE(success);
//        checkSQTModel(model);
//
//        promiseSet = true;
//        sendSQTPromise.set_value(success);
//      }, isSnapshot);
//
//    TestHelper::waitForSuccess(sendSQTFuture, streamPtr, 5);
//
//    SECTION("SQT unsubscribe")
//    {
//      std::promise<bool> sendUnsubPromise;
//      std::future<bool> sendUnsubFuture = sendUnsubPromise.get_future();
//      manager.unsubscribeQuote(SYMBOL_TO_TEST,
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
//  SECTION("SQT stream")
//  {
//    std::promise<bool> sendSQTPromise;
//    std::future<bool> sendSQTFuture = sendSQTPromise.get_future();
//    bool isSnapshot = false;
//    bool promiseSet = false;
//
//    int countMessages = 0;
//    manager.subscribeQuote(SYMBOL_TO_TEST, [&](bool success, const cedro::md::models::SQTModel& model)
//    {
//      if (promiseSet)
//        return;
//
//      REQUIRE(success);
//      checkSQTModel(model);
//
//      if(countMessages < 10)
//      {
//        countMessages++;
//        return;
//      }
//
//      promiseSet = true;
//      sendSQTPromise.set_value(success);
//
//    }, isSnapshot);
//
//    TestHelper::waitForSuccess(sendSQTFuture, streamPtr, 5);
//
//    SECTION("SQT stream unsubscribe")
//    {
//      std::promise<bool> sendUnsubPromise;
//      std::future<bool> sendUnsubFuture = sendUnsubPromise.get_future();
//      manager.unsubscribeQuote(SYMBOL_TO_TEST,
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
//  SECTION("BQT stream")
//  {
//    std::promise<bool> sendSQTPromise;
//    std::future<bool> sendSQTFuture = sendSQTPromise.get_future();
//    bool promiseSet = false;
//
//    int countMessages = 0;
//    manager.subscribeBookQuote(SYMBOL_TO_TEST, [&](bool success, const cedro::md::models::BQTModel& model)
//    {
//      if (promiseSet)
//        return;
//
//      REQUIRE(success);
//      REQUIRE(strcmp(model.symbol, "") != 0);
//      REQUIRE((model.msgType == 'A' || model.msgType == 'U' || model.msgType == 'D' || model.msgType == 'E'));
//
//      // Verificações específicas para cada tipo de mensagem
//      switch (model.msgType)
//      {
//        case 'A': // Add order
//          REQUIRE(model.position != INVALID_INT32);
//          REQUIRE(model.direction != '\0');
//          REQUIRE(!std::isnan(model.price));
//          REQUIRE(model.quantity != INVALID_INT32);
//          REQUIRE(model.broker != INVALID_INT32);
//          REQUIRE(strcmp(model.datetime, "") != 0);
//          REQUIRE(strcmp(model.orderID, "") != 0);
//          REQUIRE(model.offerType != '\0');
//          break;
//
//        case 'U': // Update order
//          REQUIRE(model.position != INVALID_INT32);
//          REQUIRE(model.oldPosition != INVALID_INT32);
//          REQUIRE(model.direction != '\0');
//          REQUIRE(!std::isnan(model.price));
//          REQUIRE(model.quantity != INVALID_INT32);
//          REQUIRE(model.broker != INVALID_INT32);
//          REQUIRE(strcmp(model.datetime, "") != 0);
//          REQUIRE(strcmp(model.orderID, "") != 0);
//          REQUIRE(model.offerType != '\0');
//          break;
//
//        case 'D': // Delete order
//          REQUIRE(model.cancelType != INVALID_INT32);
//          if (model.cancelType != 3) // If not a mass delete, validate position and direction
//          {
//            REQUIRE(model.position != INVALID_INT32);
//            REQUIRE(model.direction != '\0');
//          }
//          break;
//        case 'E': // End of initial data
//          break;
//        default:
//          FAIL("Unknown message type received");
//          break;
//      }
//
//      // set to a big number to get all book and test end of messages type properly
//      if (countMessages < 100)
//      {
//        countMessages++;
//        return;
//      }
//
//      promiseSet = true;
//      sendSQTPromise.set_value(success);
//    });
//
//    TestHelper::waitForSuccess(sendSQTFuture, streamPtr, 60);
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
//  SECTION("GQT stream")
//  {
//    std::promise<bool> sendGQTPromise;
//    std::future<bool> sendGQTFuture = sendGQTPromise.get_future();
//    bool promiseSet = false;
//
//    int countMessages = 0;
//    manager.subscribeQuoteTrades(SYMBOL_TO_TEST, [&](bool success, const cedro::md::models::GQTModel& model)
//    {
//      if (promiseSet)
//        return;
//
//      REQUIRE(success);
//      REQUIRE(strcmp(model.symbol, "") != 0);
//      REQUIRE((model.msgType == 'A' || model.msgType == 'D' || model.msgType == 'R' || model.msgType == 'E'));
//
//  if(model.msgType ==  'E')
//    REQUIRE(model.operation == '\0');
//  else
//    REQUIRE((model.operation == 'A' || model.operation == 'D' || model.operation == 'R'));
//
//      switch (model.msgType)
//      {
//        case 'A': // Add trade
//          REQUIRE(strcmp(model.time, "") != 0);
//          REQUIRE(!std::isnan(model.price));
//          REQUIRE(model.buyerBroker != INVALID_INT32);
//          REQUIRE(model.sellerBroker != INVALID_INT32);
//          REQUIRE(model.quantity != INVALID_INT32);
//          REQUIRE(strcmp(model.tradeID, "") != 0);
//          REQUIRE(model.direct != INVALID_INT32);
//          REQUIRE(model.aggressor != '\0');
//          break;
//
//        case 'D': // Remove trade
//          REQUIRE(strcmp(model.tradeID, "") != 0);
//          break;
//
//        case 'R': // Remove all trades
//          break;
//
//        case 'E': // End of initial data
//          if (model.isSnapshot())
//            REQUIRE(strcmp(model.requestID, "") != 0);
//          break;
//
//        default:
//          FAIL("Unknown message type received");
//          break;
//      }
//
//      if (countMessages < 10)
//      {
//        countMessages++;
//        return;
//      }
//
//      sendGQTPromise.set_value(success);
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
//        REQUIRE(success);
//        sendUnsubPromise.set_value(success);
//      });
//
//      TestHelper::waitForSuccess(sendUnsubFuture, streamPtr, 5);
//    }
//  }
//
///**
//   * This is the most problematic section so far
//   * the reason is that sometimes requesting quotes in sequence the callback comes
//   * with the end of message flag to true as the first message and no messages are delivered at all.
//   * TODO:: talk to Rodrigo of Cedro about it.
//   */
//  SECTION("GQT snapshot")
//  {
//    std::promise<bool> sendGQTPromise;
//    std::future<bool> sendGQTFuture = sendGQTPromise.get_future();
//    bool promiseSet = false;
//
//    int countMessages = 0;
//    int numberOfQuotes = 200;
//    manager.snapshotQuoteTrades(SYMBOL_TO_TEST, numberOfQuotes,
//    [&](bool success, const cedro::md::models::GQTModel& model, bool isEndOfMessages)
//    {
//      if (promiseSet)
//        return;
//
//      REQUIRE(success);
//      REQUIRE(strcmp(model.symbol, "") != 0);
//      REQUIRE((model.msgType == 'A' || model.msgType == 'D' || model.msgType == 'R' || model.msgType == 'E'));
//
//      if(model.msgType ==  'E')
//        REQUIRE(model.operation == '\0');
//      else
//      {
//        REQUIRE((model.operation == 'A' || model.operation == 'D' || model.operation == 'R'));
//        countMessages++;
//      }
//
//      switch (model.msgType)
//      {
//        case 'A': // Add trade
//          REQUIRE(strcmp(model.time, "") != 0);
//          REQUIRE(!std::isnan(model.price));
//          REQUIRE(model.buyerBroker != INVALID_INT32);
//          REQUIRE(model.sellerBroker != INVALID_INT32);
//          REQUIRE(model.quantity != INVALID_INT32);
//          REQUIRE(strcmp(model.tradeID, "") != 0);
//          REQUIRE(model.direct != INVALID_INT32);
//          REQUIRE(model.aggressor != '\0');
//          break;
//
//        case 'D': // Remove trade
//          REQUIRE(strcmp(model.tradeID, "") != 0);
//          break;
//
//        case 'R': // Remove all trades
//          break;
//
//        case 'E': // End of initial data
//          if (model.isSnapshot())
//            REQUIRE(strcmp(model.requestID, "") != 0);
//          break;
//
//        default:
//          FAIL("Unknown message type received");
//          break;
//      }
//
//      if(isEndOfMessages)
//      {
//        sendGQTPromise.set_value(success);
//        promiseSet = true;
//      }
//    });
//
//    TestHelper::waitForSuccess(sendGQTFuture, streamPtr, 10);
//
//    REQUIRE((numberOfQuotes == countMessages || countMessages == 0));
//  }
//
//  SECTION("SAB snapshot")
//  {
//    std::promise<bool> sendSABPromise;
//    std::future<bool> sendSABFuture = sendSABPromise.get_future();
//    bool promiseSet = false;
//    bool isSnapshot = true;
//
//    manager.subscribeAggBook(SYMBOL_TO_TEST, [&](bool success, const cedro::md::models::SABModel& model)
//    {
//      if (promiseSet)
//        return;
//
//      REQUIRE(success);
//      REQUIRE(strcmp(model.symbol, "") != 0);
//      REQUIRE((model.msgType == 'A' || model.msgType == 'U' || model.msgType == 'D' || model.msgType == 'E'));
//
//      switch (model.msgType)
//      {
//        case 'A': // Add order
//        case 'U': // Update order
//          REQUIRE(model.position != INVALID_INT32);
//          REQUIRE(model.direction != '\0');
//          REQUIRE(!std::isnan(model.price));
//          REQUIRE(model.quantity != INVALID_INT32);
//          REQUIRE(model.numOfOffers != INVALID_INT32);
//          REQUIRE(strcmp(model.dateTime, "") != 0);
//          break;
//
//        case 'D': // Delete order
//          REQUIRE(model.cancelType != INVALID_INT32);
//          if (model.cancelType == 3) break;
//          // If not a mass cancel, validate position and direction
//          REQUIRE(model.position != INVALID_INT32);
//          REQUIRE(model.direction != '\0');
//          break;
//        case 'E': // End of initial data
//          {
//            promiseSet = true;
//            sendSABPromise.set_value(success);
//          }
//          break;
//        default:
//          REQUIRE(false);
//          break;
//      }
//
//    }, isSnapshot);
//
//    TestHelper::waitForSuccess(sendSABFuture, streamPtr, 20);
//
//    SECTION("SAB snapshot unsubscribe")
//    {
//      std::promise<bool> sendUnsubPromise;
//      std::future<bool> sendUnsubFuture = sendUnsubPromise.get_future();
//      manager.unsubscribeAggBook(SYMBOL_TO_TEST,
//      [&](bool success)
//      {
//        REQUIRE(success);
//        sendUnsubPromise.set_value(success);
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
//    bool promiseSet = false;
//    bool isSnapshot = false;
//
//    int countMessages = 0;
//    manager.subscribeAggBook(SYMBOL_TO_TEST, [&](bool success, const cedro::md::models::SABModel& model)
//    {
//      if (promiseSet)
//        return;
//
//      REQUIRE(success);
//      REQUIRE(strcmp(model.symbol, "") != 0);
//      REQUIRE((model.msgType == 'A' || model.msgType == 'U' || model.msgType == 'D' || model.msgType == 'E'));
//
//      switch (model.msgType)
//      {
//        case 'A': // Add order
//        case 'U': // Update order
//          REQUIRE(model.position != INVALID_INT32);
//          REQUIRE(model.direction != '\0');
//          REQUIRE(!std::isnan(model.price));
//          REQUIRE(model.quantity != INVALID_INT32);
//          REQUIRE(model.numOfOffers != INVALID_INT32);
//          REQUIRE(strcmp(model.dateTime, "") != 0);
//          break;
//
//        case 'D': // Delete order
//          REQUIRE(model.cancelType != INVALID_INT32);
//          if (model.cancelType == 3) break;
//          // If not a mass cancel, validate position and direction
//          REQUIRE(model.position != INVALID_INT32);
//          REQUIRE(model.direction != '\0');
//          break;
//        case 'E': // End of initial data
//          break;
//        default:
//          REQUIRE(false);
//          break;
//      }
//
//      if (countMessages < 100)
//      {
//        countMessages++;
//        return;
//      }
//
//      promiseSet = true;
//      sendSABPromise.set_value(success);
//    }, isSnapshot);
//
//    TestHelper::waitForSuccess(sendSABFuture, streamPtr, 20);
//
//    SECTION("SAB stream unsubscribe")
//    {
//      std::promise<bool> sendUnsubPromise;
//      std::future<bool> sendUnsubFuture = sendUnsubPromise.get_future();
//      manager.unsubscribeAggBook(SYMBOL_TO_TEST,
//      [&](bool success)
//      {
//        REQUIRE(success);
//        sendUnsubPromise.set_value(success);
//      });
//
//      TestHelper::waitForSuccess(sendUnsubFuture, streamPtr, 5);
//    }
//  }
//
//  SECTION("VAP snapshot normal")
//  {
//    std::promise<bool> sendVAPPromise;
//    std::future<bool> sendVAPFuture = sendVAPPromise.get_future();
//    bool promiseSet = false;
//
//    manager.snapshotVolumeAtPrice(SYMBOL_TO_TEST,
//    [&](bool success, const cedro::md::models::VAPModel& model, bool isEndOfMessages)
//    {
//      if (promiseSet)
//        return;
//
//      REQUIRE(success);
//      REQUIRE(strcmp(model.symbol, "") != 0);
//      REQUIRE((model.msgType == 'N' ||  model.msgType == 'E'));
//
//      if(!isEndOfMessages)
//      {
//        REQUIRE(!std::isnan(model.tradedPrice));
//        REQUIRE(!std::isnan(model.buyerTrades));
//        REQUIRE(!std::isnan(model.buyerVolume));
//        REQUIRE(!std::isnan(model.sellerTrades));
//        REQUIRE(!std::isnan(model.sellerVolume));
//        REQUIRE(!std::isnan(model.directTrades));
//        REQUIRE(!std::isnan(model.directVolume));
//        REQUIRE(!std::isnan(model.undefinedTrades));
//        REQUIRE(!std::isnan(model.undefinedVolume));
//        REQUIRE(!std::isnan(model.rlpTrades));
//        REQUIRE(!std::isnan(model.rlpVolume));
//
//        REQUIRE(model.period != INVALID_INT32);
//        REQUIRE(strcmp(model.dateRange, "") == 0);
//
//      }
//      else
//      {
//        REQUIRE(model.msgType == 'E');
//        LOG_INFO("VAP snapshot normal: End of messages received");
//        sendVAPPromise.set_value(success);
//        promiseSet = true;
//      }
//    });
//
//    TestHelper::waitForSuccess(sendVAPFuture, streamPtr, 10);
//  }
//
//  SECTION("VAP snapshot minute")
//  {
//    std::promise<bool> sendVAPPromise;
//    std::future<bool> sendVAPFuture = sendVAPPromise.get_future();
//    bool promiseSet = false;
//    int32_t lastMinutes = 10;
//    manager.snapshotVolumeAtPriceLastMinutes(SYMBOL_TO_TEST,
//    [&](bool success, const cedro::md::models::VAPModel& model, bool isEndOfMessages)
//    {
//      if (promiseSet)
//        return;
//
//      REQUIRE(success);
//      REQUIRE(strcmp(model.symbol, "") != 0);
//      REQUIRE((model.msgType == 'M' ||  model.msgType == 'E'));
//
//      if(!isEndOfMessages)
//      {
//        REQUIRE(!std::isnan(model.tradedPrice));
//        REQUIRE(!std::isnan(model.buyerTrades));
//        REQUIRE(!std::isnan(model.buyerVolume));
//        REQUIRE(!std::isnan(model.sellerTrades));
//        REQUIRE(!std::isnan(model.sellerVolume));
//        REQUIRE(!std::isnan(model.directTrades));
//        REQUIRE(!std::isnan(model.directVolume));
//        REQUIRE(!std::isnan(model.undefinedTrades));
//        REQUIRE(!std::isnan(model.undefinedVolume));
//        REQUIRE(!std::isnan(model.rlpTrades));
//        REQUIRE(!std::isnan(model.rlpVolume));
//
//        REQUIRE(model.period != INVALID_INT32);
//        REQUIRE(strcmp(model.dateRange, "") == 0);
//      }
//      else
//      {
//        REQUIRE(model.msgType == 'E');
//        LOG_INFO("VAP snapshot minute: End of messages received");
//        sendVAPPromise.set_value(success);
//        promiseSet = true;
//      }
//    }, lastMinutes);
//
//    TestHelper::waitForSuccess(sendVAPFuture, streamPtr, 10);
//  }
//
//  SECTION("VAP snapshot history")
//  {
//    std::promise<bool> sendVAPPromise;
//    std::future<bool> sendVAPFuture = sendVAPPromise.get_future();
//    bool promiseSet = false;
//    std::string startDate = "20240801";
//    std::string endDate = "20240807";
//    bool accumulated = true;
//    manager.snapshotVolumeAtPriceHistory(SYMBOL_TO_TEST,
//    [&](bool success, const cedro::md::models::VAPModel& model, bool isEndOfMessages)
//    {
//     if (promiseSet)
//       return;
//
//     REQUIRE(success);
//     REQUIRE(strcmp(model.symbol, "") != 0);
//     REQUIRE((model.msgType == 'H' ||  model.msgType == 'E'));
//
//     if(!isEndOfMessages)
//     {
//       REQUIRE(!std::isnan(model.tradedPrice));
//       REQUIRE(!std::isnan(model.buyerTrades));
//       REQUIRE(!std::isnan(model.buyerVolume));
//       REQUIRE(!std::isnan(model.sellerTrades));
//       REQUIRE(!std::isnan(model.sellerVolume));
//       REQUIRE(!std::isnan(model.directTrades));
//       REQUIRE(!std::isnan(model.directVolume));
//       REQUIRE(!std::isnan(model.undefinedTrades));
//       REQUIRE(!std::isnan(model.undefinedVolume));
//       REQUIRE(!std::isnan(model.rlpTrades));
//       REQUIRE(!std::isnan(model.rlpVolume));
//
//       REQUIRE(model.period == INVALID_INT32);
//       REQUIRE(strcmp(model.dateRange, "") != 0);
//     }
//     else
//     {
//       REQUIRE(model.msgType == 'E');
//       LOG_INFO("VAP snapshot history: End of messages received");
//       sendVAPPromise.set_value(success);
//       promiseSet = true;
//     }
//    }, startDate, endDate, accumulated);
//
//    TestHelper::waitForSuccess(sendVAPFuture, streamPtr, 10);
//  }

  SECTION("GPN processed")
  {
    std::promise<bool> sendGPNPromise;
    std::future<bool> sendGPNFuture = sendGPNPromise.get_future();
    bool promiseSet = false;
    bool sortedByName = true;
    manager.getPlayerNames("bmf", sortedByName,
    [&](bool success, const cedro::md::models::GPNModel& model, bool isEndOfMessages)
    {
      if (promiseSet)
        return;

      REQUIRE(success);
      REQUIRE(strcmp(model.market, "") != 0);

      if(!isEndOfMessages)
      {
        REQUIRE(model.brokerCode != INVALID_INT32);
        REQUIRE(model.brokerCodeAtBank != INVALID_INT32);
        REQUIRE(strcmp(model.brokerName, "") != 0);
        REQUIRE(model.msgType == 'M');
      }
      else
      {
        REQUIRE(model.msgType == 'E');
        LOG_INFO("GPN: End of messages received");
        sendGPNPromise.set_value(success);
        promiseSet = true;
      }
    });

    TestHelper::waitForSuccess(sendGPNFuture, streamPtr, 10);
  }
}