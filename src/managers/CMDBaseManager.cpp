//
// Created by Arthur Motelevicz on 29/07/24.
//

#include "managers/CMDBaseManager.h"
#include "StringHelper.h"
#include <memory>
#include "CMDTypes.h"
#include "StringHelper.h"

namespace cedro::md
{
  CMDBaseManager::CMDBaseManager(const std::string &username, const std::string &password, const std::string &softKey):
  _username(username),
  _password(password),
  _softKey(softKey)
  {
    _streamer = std::make_shared<bb::RawStreamer>();
    _messenger = std::make_shared<bb::RawMessenger>();
  }

  CMDBaseManager::~CMDBaseManager()
  {
    logI << ("CMDBaseManager destructor");
    _bqtCallbacks.clear();
    _sqtCallbacks.clear();
    _sabCallbacks.clear();
    _isConnected = false;
  }

  void CMDBaseManager::reset()
  {
    if(!_stream)
      return;

    _stream->stop(
      [&]()
      {
        _bqtCallbacks.clear();
        _sqtCallbacks.clear();
        _sabCallbacks.clear();
        _isConnected = false;
      });
  }

  void CMDBaseManager::subscribeQuote(const std::string& symbol,
                                      const StreamCallback& cb,
                                      bool snapshot)
  {
    if(!safetyCheck(symbol, cb))
      return;

    std::string message = "SQT " + symbol;
    if(snapshot)
      message += " N";

    message += "\n";

    _messenger->sendMessage(_stream, message,
    [&, cb, symbol](bool success)
    {
      if (!success)
      {
        std::string errorMsg = "Failed to send SQT message";
        logE << (errorMsg);
        cb(false, errorMsg.c_str(), errorMsg.length());
      }
      else
      {
        _sqtCallbacks[mgutils::string::toUpper(symbol)] = cb;
        logI << ("Subscribed successfully");
      }
    });
  }

  void CMDBaseManager::unsubscribeQuote(const std::string& symbol, const SuccessCallback& cb)
  {
    if(!safetyCheck(symbol))
    {
      cb(false);
      return;
    }

    std::string message = "USQ " + symbol + "\n";
    _messenger->sendMessage(_stream, message,
    [&, cb, symbol](bool success)
    {
      if (!success)
      {
        logE << ("Failed to send USQ message");
        cb(false);
      }
      else
      {
        logI << ("Unsubscribed successfully");
        auto it = _sqtCallbacks.find(symbol);
        if (it != _sqtCallbacks.end())
          _sqtCallbacks.erase(it);

        cb(true);
      }
    });
  }

  void CMDBaseManager::subscribeBookQuote(const std::string& symbol, const StreamCallback& cb)
  {
    if(!safetyCheck(symbol, cb))
      return;

    std::string message = "BQT " + symbol + "\n";
    _messenger->sendMessage(_stream, message,
    [&, cb, symbol](bool success)
    {
      if (!success)
      {
        std::string errorMsg = "Failed to send BQT message";
        logE << (errorMsg);
        cb(false, errorMsg.c_str(), errorMsg.length());
      }
      else
      {
        _bqtCallbacks[mgutils::string::toUpper(symbol)] = cb;
        logI << ("Subscribed to book quote successfully");
      }
    });
  }

  void CMDBaseManager::unsubscribeBookQuote(const std::string& symbol, const SuccessCallback& cb)
  {
    if(!safetyCheck(symbol))
    {
      cb(false);
      return;
    }

    std::string message = "UBQ " + symbol + "\n";
    _messenger->sendMessage(_stream, message,
    [&, cb, symbol](bool success)
    {
      if (!success)
      {
        logE << ("Failed to send UBQ message");
        cb(false);
      }
      else
      {
        logI << ("Unsubscribed from book quote successfully");
        auto it = _bqtCallbacks.find(symbol);
        if (it != _bqtCallbacks.end())
          _bqtCallbacks.erase(it);

        cb(true);
      }
    });
  }

  void CMDBaseManager::subscribeAggBook(const std::string& symbol,
                                      const StreamCallback& cb,
                                      bool snapshot)
  {
    if(!safetyCheck(symbol, cb))
      return;

    std::string message = "SAB " + symbol;
    if(snapshot)
      message += " N";

    message += "\n";

    _messenger->sendMessage(_stream, message,
    [&, cb, symbol](bool success)
    {
      if (!success)
      {
        std::string errorMsg = "Failed to send SAB message";
        logE << (errorMsg);
        cb(false, errorMsg.c_str(), errorMsg.length());
      }
      else
      {
        _sabCallbacks[mgutils::string::toUpper(symbol)] = cb;
        logI << ("SAB - Subscribed successfully");
      }
    });
  }


  void CMDBaseManager::unsubscribeAggBook(const std::string& symbol, const SuccessCallback& cb)
  {
    if(!safetyCheck(symbol))
    {
      cb(false);
      return;
    }

    std::string message = "UAB " + symbol + "\n";
    _messenger->sendMessage(_stream, message,
    [&, symbol, cb](bool success)
    {
      if (!success)
      {
        logE << ("Failed to send UAB message");
        cb(false);
      }
      else
      {
        logI << ("UAB - Unsubscribed successfully");
        auto it = _sabCallbacks.find(symbol);
        if (it != _sabCallbacks.end())
          _sabCallbacks.erase(it);
        cb(true);
      }
    });
  }

  void CMDBaseManager::subscribeQuoteTrades(const std::string &symbol, const StreamCallback &cb)
  {
    if(!safetyCheck(symbol, cb))
      return;

    std::string message = "GQT " + symbol + " S\n";

    _messenger->sendMessage(_stream, message,
    [&, cb, symbol](bool success)
    {
      if (!success)
      {
        std::string errorMsg = "Failed to send GQT message";
        logE << (errorMsg);
        cb(false, errorMsg.c_str(), errorMsg.length());
      }
      else
      {
        _gqtCallbacks[mgutils::string::toUpper(symbol)] = cb;
        logI << ("GQT - Subscribed successfully");
      }
    });
  }

  void CMDBaseManager::snapshotQuoteTrades(const std::string& symbol,
                                           size_t numberOfTrades,
                                           const StreamWithEndFlagCallback& cb,
                                           size_t offset)
  {
    if(!safetyCheck(symbol, cb))
      return;

    std::stringstream stm;

    auto requestId = mgutils::generateID(6);

    stm << "GQT " <<
    symbol <<
    " N " <<
    numberOfTrades << " " <<
    offset << " " <<
    requestId << "\n";

    std::string message = stm.str();

    _messenger->sendMessage(_stream, message,

    [&, cb, requestId](bool success)
    {
      if (!success)
      {
        std::string errorMsg = "GQT(snap): Failed to send message";
        logE << (errorMsg);
        cb(false, errorMsg.c_str(), errorMsg.length(), true);
      }
      else
      {
        _gqtSnapCallbacks[requestId] = cb;
        logI << ("GQT(snap): Subscribed successfully");
      }
    });
  }

  void CMDBaseManager::unsubscribeQuoteTrades(const std::string &symbol, const SuccessCallback& cb)
  {
    if(!safetyCheck(symbol))
    {
      cb(false);
      return;
    }

    std::string message = "UQT " + symbol + "\n";
    _messenger->sendMessage(_stream, message,
    [&, symbol, cb](bool success)
    {
      if (!success)
      {
        logE << ("UQT: Failed to send UAB message");
        cb(false);
      }
      else
      {
        logI << ("UQT: Unsubscribed successfully");
        auto it = _gqtCallbacks.find(symbol);
        if (it != _gqtCallbacks.end())
          _gqtCallbacks.erase(it);

        cb(true);
      }
    });
  }

  void CMDBaseManager::getPlayerNames(const std::string& marketName,
                                      bool sortedByName,
                                      const StreamWithEndFlagCallback& cb)
  {
    if(!safetyCheck("Dummy", cb))
      return;

    std::string message = "GPN " + marketName;

    if(sortedByName)
      message += " 1";

    _messenger->sendMessage(_stream, message + "\n",
    [&, cb, marketName](bool success)
    {
      if (!success)
      {
        std::string errorMsg = "Failed to send GPN message";
        logE << (errorMsg);
        cb(false, errorMsg.c_str(), errorMsg.length(), true);
      }
      else
      {
        _gpnCallbacks[mgutils::string::toUpper(marketName)]= cb;
        logI << ("Requested player names successfully");
      }
    });
  }

  void CMDBaseManager::sendVAPMessage(const std::string& symbol,
                                      const std::string &message,
                                      const VAPStreamCallback &cb,
                                      const VAPRequestInfo& info)
  {
    _messenger->sendMessage(_stream, message,
    [&, symbol, cb, info](bool success)
    {
      if (!success)
      {
        std::string errorMsg = "VAP(snap): Failed to send message";
        logE << (errorMsg);
        cb(false, errorMsg.c_str(), errorMsg.length(), true, info.type);
      }
      else
      {
        _vapSnapCallbacks[info] = cb;
        logI << ("VAP(snap): Subscribed successfully");
      }
    });
  }


  void CMDBaseManager::snapshotVolumeAtPrice(const std::string& symbol,
                             const VAPStreamCallback& cb)
  {
    if(!safetyCheck(symbol, cb))
      return;

    std::stringstream stm;

    stm << "VAP " << symbol << "\n";

    VAPRequestInfo info(VAPRequestInfo::NORMAL,  mgutils::string::toUpper(symbol));
    std::string message = stm.str();
    sendVAPMessage(symbol, message, cb, info);
  }

  void CMDBaseManager::snapshotVolumeAtPriceLastMinutes(const std::string& symbol,
                                        const VAPStreamCallback& cb,
                                        int32_t lastMinutes)
  {
    if(!safetyCheck(symbol, cb))
      return;

    std::array<int, 7> supportedValues = {1, 2, 5, 10, 15, 30 , 60};

    bool isValueSupported = false;

    for(auto &v : supportedValues)
    {
      isValueSupported = (v == lastMinutes);
      if(isValueSupported) break;
    }

    VAPRequestInfo info(VAPRequestInfo::MINUTE, mgutils::string::toUpper(symbol));

    if(!isValueSupported)
    {
      std::stringstream stm;
      stm << "VAP minutes: " << lastMinutes << " not supported. Please use one of these values: [1, 2, 5, 10, 15, 30 , 60]";
      auto errmsg = stm.str();
      logW << (errmsg);
      cb(false, errmsg.c_str(), errmsg.length(), true, info.type);
      return;
    }

    std::stringstream stm;
    stm << "VAP " << symbol << " " << lastMinutes << "\n";

    std::string message = stm.str();


    sendVAPMessage(symbol, message, cb, info);
  }

  void CMDBaseManager::snapshotVolumeAtPriceHistory(const std::string& symbol,
                                    const VAPStreamCallback& cb,
                                    const std::string& startDate,
                                    const std::string& endDate,
                                    bool accumulated)
  {
    if(!safetyCheck(symbol, cb))
      return;

    bool isHistory = !(startDate.empty() || endDate.empty());

    VAPRequestInfo info(VAPRequestInfo::HISTORY, mgutils::string::toUpper(symbol));

    if(!isHistory)
    {
      std::stringstream stm;
      stm << "VAP history: missing date. Please set a valid date range!";
      auto errmsg = stm.str();
      logW << (errmsg);
      cb(false, errmsg.c_str(), errmsg.length(), true, info.type);
      return;
    }

    std::stringstream stm;
    stm << "VAP "
      << symbol
      << " h "
      << startDate << " "
      << endDate << " "
      << (accumulated ? "ACC" : "") << "\n";

    std::string message = stm.str();


    sendVAPMessage(symbol, message, cb, info);
  }

  void CMDBaseManager::connect(const ConnectionCallback &cb)
  {
    if(_isConnected)
    {
      logW << ("Already connected!");
      cb(true, _stream);
      return;
    }

    auto stream = _streamer->openStream(FEED_URL_2, PORT_NUMBER, "",
      [&, cb](bool success, const char* data, size_t size, auto stream)
      {
        if (!success)
        {
          _isConnected = false;
          cb(false, nullptr);
          return;
        }

        if(_isConnected)
        {
          handleMessage(data, size);
          return;
        }

        handleConnectionStep(data, stream, cb);
      }, '\n');
  }

  void CMDBaseManager::disconnect(const SuccessCallback& cb)
  {
    if(!_isConnected)
    {
      logW << ("Already disconnected!");
      cb(false);
      return;
    }

    _messenger->sendMessage(_stream, "quit",
      [&, cb](bool success)
      {
        reset();
        cb(success);
      }
    );
  }

  void CMDBaseManager::handleMessage(const char* data, size_t size)
  {
    if (size < 3)
      return;

    const char* prefix = nullptr;
    prefix = std::strstr(data, "E:");
    if (prefix && ((prefix - data) <= 2)) // Error
    {
      handleErrorMessage(prefix, size);
    }
    else if ((prefix = std::strstr(data, "T:")) != nullptr) // SQT
    {
      handleSQTMessage(prefix, size);
    }
    else if ((prefix = std::strstr(data, "B:")) != nullptr) // BQT
    {
      handleBQTMessage(prefix, size);
    }
    else if ((prefix = std::strstr(data, "G:")) != nullptr) // GPN
    {
      handleGPNMessage(prefix, size);
    }
    else if ((prefix = std::strstr(data, "Z:")) != nullptr) // SAB
    {
      handleSABMessage(prefix, size);
    }
    else if ((prefix = std::strstr(data, "V:")) != nullptr) // GQT
    {
      handleGQTMessage(prefix, size);
    }
    else if ((prefix = std::strstr(data, "VAP:")) != nullptr) // VAP
    {
      handleVAPSnapshotMessage(prefix, size);
    }
    else if ((prefix = std::strstr(data, "SYN")) != nullptr) // SYN
    {
      logD << ("SYN: Sync message received!");
    }
    else
    {
      logW << ("Unhandled message type received: " + std::string(data, size));
    }
  }

  void CMDBaseManager::handleSQTMessage(const char* data, size_t size)
  {
    std::string symbol = extractSymbolFromMessage(data);
    if (symbol.empty())
    {
      logW << ("Could not extract symbol for SQT");
      return;
    }

    auto callbackIter = _sqtCallbacks.find(symbol);

    // if there is no callback for the symbol ignores the callback
    if (callbackIter == _sqtCallbacks.end())
      return;

    const char* endMsg = std::strchr(data, '!');
    if (endMsg != nullptr)
    {
      size_t messageLength = endMsg - data + 1;
      char message[messageLength + 1];
      std::strncpy(message, data, messageLength);
      message[messageLength] = '\0';

      callbackIter->second(true, message, messageLength);
    }
  }

  void CMDBaseManager::handleBQTMessage(const char* data, size_t size)
  {
    std::string symbol = extractSymbolFromMessage(data);
    if (symbol.empty())
    {
      logW << ("Could not extract symbol for BQT");
      return;
    }

    auto callbackIter = _bqtCallbacks.find(symbol);

    // if there is no callback for the symbol ignores the callback
    if (callbackIter == _bqtCallbacks.end())
      return;

    if(size + 1 > BQT_BUFFER_SIZE)
    {
      logW << ("BQT message size exceeds buffer capacity. Ignoring it!");
      return;
    }

    std::memcpy(_bqtBuffer, data, size);
    _bqtBuffer[size] = '\0';

    callbackIter->second(true, _bqtBuffer, size);
  }

  void CMDBaseManager::handleSABMessage(const char* data, size_t size)
  {
    std::string symbol = extractSymbolFromMessage(data);
    if (symbol.empty())
    {
      logW << ("Could not extract symbol for SAB");
      return;
    }

    auto callbackIter = _sabCallbacks.find(symbol);

    // if there is no callback for the symbol ignores the callback
    if (callbackIter == _sabCallbacks.end())
      return;

    if(size + 1 > SAB_BUFFER_SIZE)
    {
      logW << ("SAB message size exceeds buffer capacity. Ignoring it!");
      return;
    }

    std::memcpy(_sabBuffer, data, size);
    _sabBuffer[size] = '\0';

    callbackIter->second(true, _sabBuffer, size);
  }

  void CMDBaseManager::handleGQTMessage(const char* data, size_t size)
  {
    std::string id;
    bool isSnapshot = false;

    for (const auto& entry : _gqtSnapCallbacks)
    {
      if (std::strstr(data, entry.first.c_str()) != nullptr)
      {
        id = entry.first;
        isSnapshot = true;
        break;
      }
    }

    if (isSnapshot)
      handleGQTSnapshotMessage(data, size, id);
    else
      handleGQTStreamMessage(data, size);
  }

  void CMDBaseManager::handleGQTSnapshotMessage(const char* data, size_t size, const std::string& requestId)
  {
    std::string symbol = extractSymbolFromMessage(data);
    if (symbol.empty())
    {
      logW << ("GQT: Could not extract symbol");
      return;
    }

    auto callbackIter = _gqtSnapCallbacks.find(requestId);

    // if there is no callback for the symbol ignores the callback
    if (callbackIter == _gqtSnapCallbacks.end())
      return;

    if(size + 1 > GQT_BUFFER_SIZE)
    {
      logW << ("GQT: message size exceeds buffer capacity. Ignoring it!");
      return;
    }

    std::memcpy(_gqtSnapBuffer, data, size);
    _gqtSnapBuffer[size] = '\0';

    bool isEndOfMessage = (std::strstr(_gqtSnapBuffer, (":E:" + requestId).c_str()) != nullptr);

    callbackIter->second(true, _gqtSnapBuffer, size, isEndOfMessage);

    if(isEndOfMessage)
      _gqtSnapCallbacks.erase(callbackIter);
  }

  void CMDBaseManager::handleGQTStreamMessage(const char* data, size_t size)
  {
    std::string symbol = extractSymbolFromMessage(data);
    if (symbol.empty())
    {
      logW << ("GQT: Could not extract symbol");
      return;
    }

    auto callbackIter = _gqtCallbacks.find(symbol);

    // if there is no callback for the symbol ignores the callback
    if (callbackIter == _gqtCallbacks.end())
      return;

    if(size + 1 > GQT_BUFFER_SIZE)
    {
      logW << ("GQT: message size exceeds buffer capacity. Ignoring it!");
      return;
    }

    std::memcpy(_gqtBuffer, data, size);
    _gqtBuffer[size] = '\0';

    callbackIter->second(true, _gqtBuffer, size);
  }

  void CMDBaseManager::handleGPNMessage(const char* data, size_t size)
  {
    std::string market = extractSymbolFromMessage(data);
    if (market.empty())
    {
      logW << ("GPN: Could not extract market name.");
      return;
    }

    if(size + 1 > GPN_BUFFER_SIZE)
    {
      logW << ("GPN: message size exceeds buffer capacity. Ignoring it!");
      return;
    }

    std::memcpy(_gpnBuffer, data, size);
    _gpnBuffer[size] = '\0';

    bool isEndOfMessage = (std::strstr(_gpnBuffer, ":E") != nullptr && (size < 10));

    auto callbackIter = _gpnCallbacks.find(market);

    // if there is no callback for the symbol ignores the callback
    if (callbackIter == _gpnCallbacks.end())
    {
      std::stringstream stm;
      stm << "GPN: callback no found for Market: " << market <<  std::string(data, size) << "\n";
      logW << (stm.str());
      return;
    }

    callbackIter->second(true, _gpnBuffer, size, isEndOfMessage);

    if(isEndOfMessage)
      _gpnCallbacks.erase(callbackIter);
  }


  void CMDBaseManager::handleVAPSnapshotMessage(const char *data, size_t size)
  {
    std::string symbol = extractSymbolFromMessage(data, 4);
    if (symbol.empty())
    {
      logW << ("VAP(snap): Could not extract symbol");
      return;
    }

    if(size + 1 > VAP_BUFFER_SIZE)
    {
      logW << ("VAP(snap): message size exceeds buffer capacity. Ignoring it!");
      return;
    }

    std::memcpy(_vapBuffer, data, size);
    _vapBuffer[size] = '\0';

    bool isEndOfMessage = (std::strstr(_vapBuffer, ":E") != nullptr);

    auto msgType = VAPRequestInfo::determineTypeByFieldCount(data, size, isEndOfMessage);

    VAPRequestInfo info(msgType, mgutils::string::toUpper(symbol));

    auto callbackIter = _vapSnapCallbacks.find(info);

    // if there is no callback for the symbol ignores the callback
    if (callbackIter == _vapSnapCallbacks.end())
    {
      std::stringstream stm;
      stm << "VAP: callback no found for: "
          << info.symbol << " Type: "
          << info.type << "\n";

      logW << (stm.str());
      return;
    }

    callbackIter->second(true, _vapBuffer, size, isEndOfMessage, info.type);

    if(isEndOfMessage)
      _vapSnapCallbacks.erase(callbackIter);
  }

  void CMDBaseManager::handleErrorMessage(const char* data, size_t size)
  {
    if(!_errorCallback)
      return;

    std::string strErr;
    std::string strMessage;

    const char *content = data + 2;
    size_t contentLength = size - 2;

    // find the error code
    const char *firstColon = std::strchr(content, ':');

    bool onlyCode = ((firstColon == nullptr) && (contentLength <= 2) && (contentLength >= 1));
    //there is no message or content
    if (onlyCode)
    {
      strErr = std::string(content, contentLength);
      auto errorCode = static_cast<int8_t>(std::stoi(strErr));
      Error err = Error::fromInt(errorCode);
      _errorCallback(err, err.toString());
      return;
    }

    if (firstColon == nullptr || firstColon - content >= contentLength)
      return;

    size_t errorLength = firstColon - content;
    strErr = std::string(content, errorLength);
    auto errorCode = static_cast<int8_t>(std::stoi(strErr));
    Error err = Error::fromInt(errorCode);

    strMessage = std::string(firstColon + 1, contentLength - errorLength - 1);
    _errorCallback(err, strMessage);
  }

  void CMDBaseManager::handleConnectionStep(const std::string& data,
                                            const std::shared_ptr<bb::network::rs::Stream>& stream,
                                            const ConnectionCallback &cb)
  {
    std::string trimmedData = trim(data);

    if (trimmedData.empty())
    {
      logI << ("Received empty or irrelevant message");
      return;
    }

    if (data.find("Connecting") != std::string::npos)
    {
      sendSoftKey(stream, cb);
    }
    else if (data.find("Username:") != std::string::npos)
    {
      sendUsername(stream, cb);
    }
    else if (data.find("Password:") != std::string::npos)
    {
      sendPassword(stream, cb);
    }
    else if (data.find("Invalid Login") != std::string::npos)
    {
      cb(false, nullptr);
    }
    else if (data.find("You are connected") != std::string::npos)
    {
      _stream = stream;
      _isConnected = true;
      cb(true, stream);
    }
    else
    {
      logI << ("Useless message: " + data);
    }
  }

  void CMDBaseManager::sendSoftKey(const std::shared_ptr<bb::network::rs::Stream>& stream,
                                   const ConnectionCallback &cb) const
  {
    _messenger->sendMessage(stream, _softKey + "\n", [&, cb](bool success)
    {
      if (!success)
      {
        logE << ("Failed to send soft key");
        cb(false, nullptr);
      }
      else
      {
        logI << ("Soft key sent successfully");
      }
    });
  }

  void CMDBaseManager::sendUsername(const std::shared_ptr<bb::network::rs::Stream>& stream,
                                    const ConnectionCallback &cb) const
  {
    _messenger->sendMessage(stream, _username + "\n", [&,cb](bool success)
    {
      if (!success)
      {
        logE << ("Failed to send username");
        cb(false, nullptr);
      }
      else
      {
        logI << ("Username sent successfully");
      }
    });
  }

  void CMDBaseManager::sendPassword(const std::shared_ptr<bb::network::rs::Stream>& stream,
                                    const ConnectionCallback &cb) const
  {
    _messenger->sendMessage(stream, _password + "\n", [&, cb](bool success)
    {
      if (!success)
      {
        logE << ("Failed to send password");
        cb(false, nullptr);
      }
      else
      {
        logI << ("Password sent successfully");
      }
    });
  }

  bool CMDBaseManager::isConnected() const
  {
    return _isConnected;
  }


  std::string CMDBaseManager::extractSymbolFromMessage(const char* data, size_t offset)
  {
    auto symbolStart = data + offset;
    const char* symbolEnd = std::strchr(symbolStart, ':');
    if (symbolEnd != nullptr)
    {
      size_t symbolLength = symbolEnd - symbolStart;
      return std::string(symbolStart, symbolLength);
    }

    return "";
  }

  bool CMDBaseManager::safetyCheck(const std::string& symbol, const StreamCallback& cb)
  {
    assert(cb != nullptr && "Callback cannot be null");

    if(!isConnected())
    {
      std::string errorMsg = "Stream not connected!";
      cb(false, errorMsg.c_str(), errorMsg.length());
      return false;
    }

    if(symbol.empty())
    {
      std::string errorMsg = "Symbol is empty!";
      cb(false, errorMsg.c_str(), errorMsg.length());
      return false;
    }

    return true;
  }

  bool CMDBaseManager::safetyCheck(const std::string& symbol, const StreamWithEndFlagCallback& cb)
  {
    assert(cb != nullptr && "Callback cannot be null");

    if(!isConnected())
    {
      std::string errorMsg = "Stream not connected!";
      cb(false, errorMsg.c_str(), errorMsg.length(), true);
      return false;
    }

    if(symbol.empty())
    {
      std::string errorMsg = "Symbol is empty!";
      cb(false, errorMsg.c_str(), errorMsg.length(), true);
      return false;
    }

    return true;
  }

  bool CMDBaseManager::safetyCheck(const std::string& symbol, const VAPStreamCallback& cb)
  {
    assert(cb != nullptr && "Callback cannot be null");

    if(!isConnected())
    {
      std::string errorMsg = "Stream not connected!";
      cb(false, errorMsg.c_str(), errorMsg.length(), true, VAPRequestInfo::UNKNOWN);
      return false;
    }

    if(symbol.empty())
    {
      std::string errorMsg = "Symbol is empty!";
      cb(false, errorMsg.c_str(), errorMsg.length(), true, VAPRequestInfo::UNKNOWN);
      return false;
    }

    return true;
  }


  bool CMDBaseManager::safetyCheck(const std::string& symbol)
  {

    if(!isConnected())
    {
      logE << ("Stream not connected!");
      return false;
    }

    if(symbol.empty())
    {
      logE << ("Symbol is empty!");
      return false;
    }

    return true;
  }

  void CMDBaseManager::setErrorCallback(const ErrorCallback& cb)
  {
    _errorCallback = cb;
  }
}