//
// Created by Arthur Motelevicz on 29/07/24.
//

#ifndef CEDROMARKETDATA_MANAGER_H
#define CEDROMARKETDATA_MANAGER_H

#include "include/beastboys"
#include <string>
#include <unordered_map>
#include "CMDTypes.h"

namespace cedro::md
{
class CMDBaseManager
{
public:
  CMDBaseManager(const std::string& username, const std::string& password, const std::string& softKey = "");
  ~CMDBaseManager();

  bool isConnected() const;
  void connect(const ConnectionCallback& cb);
  void disconnect(const SuccessCallback& cb);
  void subscribeQuote(const std::string& symbol,
                      const StreamCallback& cb,
                      bool snapshot = false);

  void unsubscribeQuote(const std::string& symbol, const SuccessCallback& cb);
  void subscribeBookQuote(const std::string& symbol, const StreamCallback& cb);
  void unsubscribeBookQuote(const std::string& symbol, const SuccessCallback& cb);

  void subscribeAggBook(const std::string& symbol,
                        const StreamCallback& cb,
                        bool snapshot = false);

  void unsubscribeAggBook(const std::string& symbol, const SuccessCallback& cb);

  void subscribeQuoteTrades(const std::string& symbol,
                        const StreamCallback& cb);

  void snapshotQuoteTrades(const std::string& symbol,
                           size_t numberOfTrades,
                           const StreamWithEndFlagCallback& cb,
                           size_t offset = 0);

  void unsubscribeQuoteTrades(const std::string& symbol,  const SuccessCallback& cb);
  void getPlayerNames(const std::string& marketName, bool sortedByName, const StreamWithEndFlagCallback& cb);

  void snapshotVolumeAtPrice(const std::string& symbol,
                             const VAPStreamCallback& cb);

  void snapshotVolumeAtPriceLastMinutes(const std::string& symbol,
                                        const VAPStreamCallback& cb,
                                        int32_t lastMinutes);

  void snapshotVolumeAtPriceHistory(const std::string& symbol,
                             const VAPStreamCallback& cb,
                             const std::string& startDate,
                             const std::string& endDate,
                             bool accumulated = true);


  void setErrorCallback(const ErrorCallback& cb);

  void setHeartBeatCallback(const HeartBeatCallback& cb);

  // Tests purposes only
  void setUseTestURL()
  {
    _shouldUseTestURL = true;
  }

private:
  void reset();
  void sendVAPMessage(const std::string& symbol, const std::string& message, const VAPStreamCallback& cb, const VAPRequestInfo& info);
  bool safetyCheck(const std::string& symbol, const StreamCallback& cb);
  bool safetyCheck(const std::string& symbol, const StreamWithEndFlagCallback& cb);
  bool safetyCheck(const std::string& symbol, const VAPStreamCallback & cb);
  bool safetyCheck(const std::string& symbol);

  void handleConnectionStep(const std::string& data,
                            const std::shared_ptr<bb::network::rs::Stream>& stream,
                            const ConnectionCallback &cb);

  void handleMessage(const char* data, size_t length);
  void handleSQTMessage(const char* data, size_t length);
  void handleBQTMessage(const char* data, size_t length);
  void handleSABMessage(const char* data, size_t length);
  void handleGQTMessage(const char* data, size_t length);
  void handleGPNMessage(const char* data, size_t length);
  void handleGQTSnapshotMessage(const char* data, size_t length, const std::string& id);
  void handleGQTStreamMessage(const char* data, size_t length);
  void handleVAPSnapshotMessage(const char* data, size_t length);
  void handleErrorMessage(const char* data, size_t length);

  void sendSoftKey(const std::shared_ptr<bb::network::rs::Stream>& stream,
                   const ConnectionCallback &cb) const;
  void sendUsername(const std::shared_ptr<bb::network::rs::Stream>& stream,
                    const ConnectionCallback &cb) const;
  void sendPassword(const std::shared_ptr<bb::network::rs::Stream>& stream,
                    const ConnectionCallback &cb) const;

  inline static const std::string FEED_URL_1 = "datafeed1.cedrotech.com";
  inline static const std::string FEED_URL_2 = "datafeed2.cedrotech.com";
  inline static const std::string FEED_URL_TESTS = "localhost";
  bool switchURL = true;
  inline static const std::string PORT_NUMBER = "81";

  std::string _username;
  std::string _password;
  std::string _softKey;

  std::shared_ptr<bb::RawMessenger> _messenger{nullptr};
  std::shared_ptr<bb::RawStreamer> _streamer{nullptr};

  std::unordered_map<std::string, StreamCallback> _sqtCallbacks;
  std::unordered_map<std::string, StreamCallback> _bqtCallbacks;
  std::unordered_map<std::string, StreamCallback> _sabCallbacks;
  std::unordered_map<std::string, StreamCallback> _gqtCallbacks;
  std::unordered_map<std::string, StreamWithEndFlagCallback> _gqtSnapCallbacks;
  std::unordered_map<std::string, StreamWithEndFlagCallback> _gpnCallbacks;
  std::unordered_map<VAPRequestInfo, VAPStreamCallback, VAPRequestInfoHash> _vapSnapCallbacks;

  HeartBeatCallback _heartBeatCallback{nullptr};

  /**
   * Helper method to extract symbol for
   * SQT - BQT - SAB - GQT
   */
  std::string extractSymbolFromMessage(const char* data, size_t offset = 2);


  std::shared_ptr<bb::network::rs::Stream> _stream{nullptr};
  bool _isConnected = false;

  // get complete messages that has no end character
  static constexpr size_t GPN_BUFFER_SIZE = 512;
  char _gpnBuffer[GPN_BUFFER_SIZE];

  static constexpr size_t BQT_BUFFER_SIZE = 512;
  char _bqtBuffer[BQT_BUFFER_SIZE];

  static constexpr size_t SAB_BUFFER_SIZE = 512;
  char _sabBuffer[SAB_BUFFER_SIZE];

  static constexpr size_t GQT_BUFFER_SIZE = 512;
  char _gqtBuffer[GQT_BUFFER_SIZE];
  char _gqtSnapBuffer[GQT_BUFFER_SIZE];

  static constexpr size_t VAP_BUFFER_SIZE = 512;
  char _vapBuffer[VAP_BUFFER_SIZE];

  ErrorCallback _errorCallback{nullptr};

  bool _shouldUseTestURL = false;

};




}

#endif //CEDROMARKETDATA_MANAGER_H
