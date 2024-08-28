//
// Created by Arthur Motelevicz on 02/08/24.
//
#include <iostream>
#include <cedromd>

int main()
{
  cedro::md::CMDBaseManager manager(CEDRO_USERNAME, CEDRO_PASSWORD, CEDRO_SOFTKEY);

  std::promise<bool> sendPromise;
  std::future<bool> sendFuture = sendPromise.get_future();

  std::shared_ptr<bb::network::rs::Stream> streamPtr;

  manager.connect([&](bool success, const std::shared_ptr<bb::network::rs::Stream>& stream)
  {
    sendPromise.set_value(success);
    streamPtr = stream;
  });

  sendFuture.wait();

//  cedro::md::models::SQTModel model;
//
//  manager.subscribeQuote("WINQ24",
//  [&](bool success, const char* data, size_t size)
//  {
//    LOG_INFO(std::string(data, size));
//  }, false);
//
//  manager.subscribeQuote("WDOU24",
//  [&](bool success, const char* data, size_t size)
//  {
////    model.parseSQTMessage(data, size);
//    LOG_INFO(std::string(data, size));
//  }, false);
//
//  std::this_thread::sleep_for(std::chrono::seconds(5));
//  manager.unsubscribeQuote("WINQ24");
//  std::this_thread::sleep_for(std::chrono::seconds(5));
//
//  manager.subscribeBookQuote("WINQ24",
//  [&](bool success, const char* data, size_t size)
//  {
//   LOG_INFO(std::string(data, size));
//  });
//
//  manager.subscribeBookQuote("WDOU24",
//  [&](bool success, const char* data, size_t size)
//  {
//    LOG_INFO(std::string(data, size));
//  });
//
//  std::this_thread::sleep_for(std::chrono::seconds(1));

//  manager.getPlayerNames("bmf", true,
//  [](bool success, const char* data, size_t size)
//  {
//    LOG_INFO(std::string(data, size));
//  });

//  manager.unsubscribeBookQuote("WINQ24");


//  manager.subscribeAggBook("WDOU24",
//  [&](bool success, const char* data, size_t size)
//  {
//   LOG_INFO(std::string(data, size));
//  });
//
//  std::this_thread::sleep_for(std::chrono::seconds(1));
//
//  manager.subscribeAggBook("WINQ24",
//   [&](bool success, const char* data, size_t size)
//   {
//     LOG_INFO(std::string(data, size));
//   });
//
//  std::this_thread::sleep_for(std::chrono::seconds(1));
//
//
//  manager.unsubscribeAggBook("WDOU24");


  manager.subscribeQuoteTrades("WDOU24",
  [&](bool success, const char* data, size_t size)
  {
    std::stringstream stm;
    stm << "STREAM: " << std::string(data, size);
    LOG_INFO(stm.str());
  });
//
  std::this_thread::sleep_for(std::chrono::seconds(1));

  manager.snapshotQuoteTrades("WDOU24", 100, [&](bool success, const char *data, size_t size, bool isLastMsg)
  {
    std::stringstream stm;
    stm << "SNAP: " << " isLast: " << isLastMsg << " " << std::string(data, size);
    LOG_INFO(stm.str());
  },0);

  manager.snapshotQuoteTrades("WDOU24", 100, [&](bool success, const char *data, size_t size, bool isLastMsg)
  {
    std::stringstream stm;
    stm << "SNAP1: " << " isLast: " << isLastMsg << " " << std::string(data, size);
    LOG_INFO(stm.str());
  },100);

  manager.snapshotQuoteTrades("WDOU24", 100, [&](bool success, const char *data, size_t size, bool isLastMsg)
  {
    std::stringstream stm;
    stm << "SNAP2: " << " isLast: " << isLastMsg << " " << std::string(data, size);
    LOG_INFO(stm.str());
  },200);

  manager.snapshotQuoteTrades("WDOU24", 100, [&](bool success, const char *data, size_t size, bool isLastMsg)
  {
    std::stringstream stm;
    stm << "SNAP3: " << " isLast: " << isLastMsg << " " << std::string(data, size);
    LOG_INFO(stm.str());
  },300);

//  std::this_thread::sleep_for(std::chrono::seconds(1));
//
//  manager.unsubscribeQuoteTrades("WINQ24");

  std::this_thread::sleep_for(std::chrono::seconds(1));

  return EXIT_SUCCESS;
}