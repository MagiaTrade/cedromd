//
// Created by Arthur Motelevicz on 08/08/24.
//

#include "managers/CMDProcessedManager.h"

namespace cedro::md
{
  CMDProcessedManager::CMDProcessedManager(const std::string &username,
                                           const std::string &password,
                                           const std::string &softKey)
  {
    _baseManager = std::make_unique<CMDBaseManager>(username, password, softKey);
  }

  CMDProcessedManager::~CMDProcessedManager(){}

  bool CMDProcessedManager::isConnected() const
  {
    return _baseManager->isConnected();
  }
  void CMDProcessedManager::connect(const ConnectionCallback& cb)
  {
    _baseManager->connect(cb);
  }

  void CMDProcessedManager::disconnect(const SuccessCallback & cb)
  {
    _baseManager->disconnect(cb);
  }

  void CMDProcessedManager::subscribeQuote(const std::string& symbol,
                      const SQTCallback& cb,
                      bool snapshot)
  {
    auto& model = _sqtMap[symbol];

    _baseManager->subscribeQuote(symbol,
    [&,cb](bool success, const char* data, size_t size)
    {
      model.parseSQTMessage(data, size);
      cb(success, model);
    },
    snapshot);
  }

  void CMDProcessedManager::unsubscribeQuote(const std::string& symbol, const SuccessCallback& cb)
  {
    _baseManager->unsubscribeQuote(symbol, cb);
  }

  void CMDProcessedManager::subscribeBookQuote(const std::string& symbol, const BQTCallback& cb)
  {
    _baseManager->subscribeBookQuote(symbol,
     [&,cb](bool success, const char* data, size_t size)
     {
        cedro::md::models::BQTModel model;
        model.parseBQTMessage(data, size);
        cb(success, model);
     });
  }

  void CMDProcessedManager::unsubscribeBookQuote(const std::string& symbol, const SuccessCallback& cb)
  {
    _baseManager->unsubscribeBookQuote(symbol, cb);
  }


  void CMDProcessedManager::subscribeQuoteTrades(const std::string& symbol,
                            const GQTCallback & cb)
  {
    _baseManager->subscribeQuoteTrades(symbol,
    [&,cb](bool success, const char* data, size_t size)
    {
      cedro::md::models::GQTModel model;
      model.setIsSnapshot(false);
      model.parseGQTMessage(data, size);
      cb(success, model);
    });
  }
  void CMDProcessedManager::unsubscribeQuoteTrades(const std::string& symbol,  const SuccessCallback& cb)
  {
    _baseManager->unsubscribeQuoteTrades(symbol, cb);
  }

  void CMDProcessedManager::snapshotQuoteTrades(const std::string& symbol,
                           size_t numberOfTrades,
                           const GQTCallbackWithEndFlag& cb,
                           size_t offset)
  {
    _baseManager->snapshotQuoteTrades(symbol, numberOfTrades,
    [cb](bool success, const char* data, size_t size, bool isEndOfMessages)
    {
      cedro::md::models::GQTModel model;
      model.setIsSnapshot(true);
      model.parseGQTMessage(data, size);
      cb(success, model, isEndOfMessages);
    },
    offset);
  }

  void CMDProcessedManager::subscribeAggBook(const std::string& symbol,
                        const SABCallback& cb,
                        bool snapshot)
  {
    _baseManager->subscribeAggBook(symbol,
    [cb](bool success, const char* data, size_t size)
    {
      cedro::md::models::SABModel model;
      model.parseSABMessage(data, size);
      cb(success, model);
    });
  }

  void CMDProcessedManager::unsubscribeAggBook(const std::string& symbol, const SuccessCallback& cb)
  {
    _baseManager->unsubscribeAggBook(symbol, cb);
  }

  void CMDProcessedManager::snapshotVolumeAtPrice(const std::string& symbol,
                             const VAPCallbackWithEndFlag& cb)
  {
    _baseManager->snapshotVolumeAtPrice(symbol,
    [cb](bool success, const char* data, size_t size, bool isEndOfMessages, VAPRequestInfo::Type requestedType)
    {
      models::VAPModel model;
      model.parseVAPMessage(data, size, requestedType);
      cb(success, model, isEndOfMessages);
    });
  }

  void CMDProcessedManager::snapshotVolumeAtPriceLastMinutes(const std::string& symbol,
                                        const VAPCallbackWithEndFlag& cb,
                                        int32_t lastMinutes)
  {
    _baseManager->snapshotVolumeAtPriceLastMinutes(symbol,
    [cb](bool success, const char* data, size_t size, bool isEndOfMessages, VAPRequestInfo::Type requestedType)
    {
      models::VAPModel model;
      model.parseVAPMessage(data, size, requestedType);
      cb(success, model, isEndOfMessages);
    }, lastMinutes);
  }

  void CMDProcessedManager::snapshotVolumeAtPriceHistory(const std::string& symbol,
                                    const VAPCallbackWithEndFlag& cb,
                                    const std::string& startDate,
                                    const std::string& endDate,
                                    bool accumulated)
  {
    _baseManager->snapshotVolumeAtPriceHistory(symbol,
    [cb](bool success, const char* data, size_t size, bool isEndOfMessages, VAPRequestInfo::Type requestedType)
    {
     models::VAPModel model;
     model.parseVAPMessage(data, size, requestedType);
     cb(success, model, isEndOfMessages);
    }, startDate, endDate, accumulated);
  }

  void CMDProcessedManager::getPlayerNames(const std::string& marketName, bool sortedByName, const GPNCallbackWithEndFlag& cb)
  {
    _baseManager->getPlayerNames(marketName, sortedByName,
    [cb](bool success, const char* data, size_t size, bool isEndOfMessage)
    {
      models::GPNModel model;
      model.parseGPNMessage(data, size);
      cb(success, model, isEndOfMessage);
    });
  }

}
