//
// Created by Arthur Motelevicz on 08/08/24.
//

#ifndef CEDRO_MD_CMDPROCESSEDMANAGER_H
#define CEDRO_MD_CMDPROCESSEDMANAGER_H

#include "CMDBaseManager.h"
#include "SQTModel.h"
#include "BQTModel.h"
#include "GQTModel.h"
#include "SABModel.h"
#include "VAPModel.h"
#include "GPNModel.h"

namespace cedro::md
{
  using SQTCallback = std::function<void(bool, const models::SQTModel& model)>;
  using BQTCallback = std::function<void(bool, const models::BQTModel& model)>;
  using GQTCallback = std::function<void(bool, const models::GQTModel& model)>;
  using GQTCallbackWithEndFlag = std::function<void(bool, const models::GQTModel& model, bool)>;
  using SABCallback = std::function<void(bool, const models::SABModel& model)>;
  using VAPCallbackWithEndFlag = std::function<void(bool, const models::VAPModel& model, bool)>;
  using GPNCallbackWithEndFlag = std::function<void(bool, const models::GPNModel& model, bool)>;

  class CMDProcessedManager
  {
  public:
    CMDProcessedManager(const std::string& username, const std::string& password, const std::string& softKey = "");
    ~CMDProcessedManager();

    bool isConnected() const;
    void connect(const ConnectionCallback& cb);
    void disconnect(const SuccessCallback & cb);

    void subscribeQuote(const std::string& symbol, const SQTCallback& cb, bool snapshot = false);
    void unsubscribeQuote(const std::string& symbol, const SuccessCallback& cb);

    void subscribeBookQuote(const std::string& symbol, const BQTCallback& cb);
    void unsubscribeBookQuote(const std::string& symbol, const SuccessCallback& cb);

    void subscribeQuoteTrades(const std::string& symbol,
                              const GQTCallback& cb);
    void unsubscribeQuoteTrades(const std::string& symbol,  const SuccessCallback& cb);

    void snapshotQuoteTrades(const std::string& symbol,
                             size_t numberOfTrades,
                             const GQTCallbackWithEndFlag& cb,
                             size_t offset = 0);

    void subscribeAggBook(const std::string& symbol,
                          const SABCallback& cb,
                          bool snapshot = false);

    void unsubscribeAggBook(const std::string& symbol, const SuccessCallback& cb);

    void snapshotVolumeAtPrice(const std::string& symbol,
                               const VAPCallbackWithEndFlag& cb);

    void snapshotVolumeAtPriceLastMinutes(const std::string& symbol,
                                          const VAPCallbackWithEndFlag& cb,
                                          int32_t lastMinutes);

    void snapshotVolumeAtPriceHistory(const std::string& symbol,
                                      const VAPCallbackWithEndFlag& cb,
                                      const std::string& startDate,
                                      const std::string& endDate,
                                      bool accumulated = true);

    void getPlayerNames(const std::string& marketName, bool sortedByName, const GPNCallbackWithEndFlag& cb);

    void setErrorCallback(const ErrorCallback& cb);
    void setHeartBeatCallback(const HeartBeatCallback& cb);


  private:
    std::unique_ptr<CMDBaseManager> _baseManager;
    std::unordered_map<std::string, models::SQTModel> _sqtMap;
  };
}
#endif //CEDRO_MD_CMDPROCESSEDMANAGER_H
