//
// Created by Arthur Motelevicz on 30/07/24.
//

#ifndef CEDRO_MD_CMDTYPES_H
#define CEDRO_MD_CMDTYPES_H

#include <string>
#include <functional>
#include <beastboys>
#include <mgutils/Utils.h>
#include <cmath>
#include <limits>
#include <algorithm>
#include <cctype>

#define MAX_STRING_SIZE 128

namespace cedro::md
{
  struct Error
  {
    enum Type : int8_t
    {
      UNKNOWN = 0,
      INVALID_COMMAND = 1,
      OBJECT_NOT_FOUND = 2,
      NO_PERMISSION = 3,
      MISSING_PARAMETER = 4,
      NO_PARAMETERS = 5,
      DOUBLE_CONNECTION = 6,
      ACCESS_REVOKED = 7,
      DOUBLE_CONNECTION_SECOND_SERVER = 8,
      ACCESS_PERMISSION_LOST = 9,
      INVALID_PARAMETER = 10,
      SERVER_UNAVAILABLE = 11,
      TRANSFER_HOST_DISCONNECTION = 12,
      INVALID_SUID = 13,
      REQUEST_ID_TOO_LARGE = 14,
      DATABASE_ERROR = 15,
      NEWS_NOT_FOUND = 16,
      NO_PERMISSION_FOR_COMMAND = 17,
      QUANTITY_QUOTE_LIMIT = 18
    };

    explicit Error(Type type) : _val(type) {}

    std::string toString() const
    {
      switch (_val) {
        case INVALID_COMMAND: return "[1]Invalid Command";
        case OBJECT_NOT_FOUND: return "[2]Object Not Found";
        case NO_PERMISSION: return "[3]No Permission";
        case MISSING_PARAMETER: return "[4]Missing Parameter";
        case NO_PARAMETERS: return "[5]No Parameters";
        case DOUBLE_CONNECTION: return "[6]Double Connection";
        case ACCESS_REVOKED: return "[7]Access Revoked";
        case DOUBLE_CONNECTION_SECOND_SERVER: return "[8]Double Connection on Second Server";
        case ACCESS_PERMISSION_LOST: return "[9]Access Permission Lost";
        case INVALID_PARAMETER: return "[10]Invalid Parameter";
        case SERVER_UNAVAILABLE: return "[11]Server Unavailable";
        case TRANSFER_HOST_DISCONNECTION: return "[12]Transfer Host Disconnection";
        case INVALID_SUID: return "[13]Invalid SUID";
        case REQUEST_ID_TOO_LARGE: return "[14]Request ID Too Large";
        case DATABASE_ERROR: return "[15]Database Error";
        case NEWS_NOT_FOUND: return "[16]News Not Found";
        case NO_PERMISSION_FOR_COMMAND: return "[17]No Permission for Command";
        case QUANTITY_QUOTE_LIMIT: return "[18]Quantity Quote Limit";
        default: return "Unknown Error";
      }
    }

    int8_t toInt() const
    {
      return static_cast<int8_t>(_val);
    }

    inline static Error fromInt(int8_t val)
    {
      switch (val)
      {
        case 1: return Error(INVALID_COMMAND);
        case 2: return Error(OBJECT_NOT_FOUND);
        case 3: return Error(NO_PERMISSION);
        case 4: return Error(MISSING_PARAMETER);
        case 5: return Error(NO_PARAMETERS);
        case 6: return Error(DOUBLE_CONNECTION);
        case 7: return Error(ACCESS_REVOKED);
        case 8: return Error(DOUBLE_CONNECTION_SECOND_SERVER);
        case 9: return Error(ACCESS_PERMISSION_LOST);
        case 10: return Error(INVALID_PARAMETER);
        case 11: return Error(SERVER_UNAVAILABLE);
        case 12: return Error(TRANSFER_HOST_DISCONNECTION);
        case 13: return Error(INVALID_SUID);
        case 14: return Error(REQUEST_ID_TOO_LARGE);
        case 15: return Error(DATABASE_ERROR);
        case 16: return Error(NEWS_NOT_FOUND);
        case 17: return Error(NO_PERMISSION_FOR_COMMAND);
        case 18: return Error(QUANTITY_QUOTE_LIMIT);
        default: return Error(UNKNOWN);
      }
    }

    Error& operator=(Error::Type type)
    {
      _val = type;
      return *this;
    }

    bool operator==(const Error::Type& rhs) const
    {
      return _val == rhs;
    }

    bool operator==(const Error& rhs) const
    {
      return _val == rhs._val;
    }

    bool operator!=(const Error::Type& rhs) const
    {
      return _val != rhs;
    }

  private:
    Type _val;
  };

  struct VAPRequestInfo
  {
    enum Type
    {
      UNKNOWN = 0,
      NORMAL,
      MINUTE,
      HISTORY
    };
    Type type;
    std::string symbol;
    VAPRequestInfo(Type t, const std::string& s):
        type(t),
        symbol(s)
    {}

    static Type determineTypeByFieldCount(const char* data, size_t size, bool isEndOfMessage)
    {
      int8_t fieldsCounter = 0;
      const char* start = data;
      const char* end = data + size;

      int32_t periodField{INVALID_INT32};

      while (start < end)
      {
        const char* delim = std::strchr(start, ':');
        if (delim == nullptr || delim >= end)
        {
          fieldsCounter++; // Contagem do último campo
          break;
        }
        else
        {
          fieldsCounter++;
          // save the period field content
          if(isEndOfMessage)
          {
            if (fieldsCounter == 3)
            {
              char *outEnd;
              long value = std::strtol(delim + 1, &outEnd, 10);
              if (outEnd != (delim + 1))
                periodField = static_cast<int32_t>(value);;
            }
          }
          else
          {
            if (fieldsCounter == 11)
            {
              char *outEnd;
              long value = std::strtol(delim + 1, &outEnd, 10);
              if (outEnd != (delim + 1))
                periodField = static_cast<int32_t>(value);
            }
          }

          start = delim + 1;
        }
      }

      if(isEndOfMessage)
      {
        // if conversion fails it's history
        if (periodField == INVALID_INT32 || periodField > INT8_MAX)
          return HISTORY;

        if (periodField > 0)
          return MINUTE;
        else
          return NORMAL;
      }

      if (fieldsCounter == 14)
      {
        if (periodField > 0)
          return MINUTE;
        return NORMAL;
      }
      else if (fieldsCounter == 15)
        return HISTORY;
      else
        return UNKNOWN;
    }

    bool operator==(const VAPRequestInfo& other) const
    {
      return type == other.type && symbol == other.symbol;
    }
  };

  struct VAPRequestInfoHash
  {
    std::size_t operator()(const VAPRequestInfo& k) const
    {
      return std::hash<int>()(k.type) ^ (std::hash<std::string>()(k.symbol) << 1);
    }
  };

  using SuccessCallback = std::function<void(bool)>;
  using ConnectionCallback = std::function<void(bool, const std::shared_ptr<bb::network::rs::Stream>&)>;
  using StreamCallback = std::function<void(bool, const char* data, size_t size)>;
  using StreamWithEndFlagCallback = std::function<void(bool, const char* data, size_t size, bool isLast)>;

  using VAPStreamCallback = std::function<void(bool, const char* data, size_t size, bool isLast, VAPRequestInfo::Type requestedType)>;

  using ErrorCallback = std::function<void(const Error& error, const std::string& msg)>;

//  struct Side
//  {
//    enum Opts: char
//    {
//      UNKNOWN = '0',  // Não informado
//      BUY = 'A',      // Compra
//      SELL = 'V'      // Venda
//    };
//
//    explicit Side(Opts opt) : _val(opt) {}
//
//    std::string toString() const
//    {
//      switch (_val) {
//        case BUY: return "A";
//        case SELL: return "V";
//        default: return "0";
//      }
//    }
//
//    char toChar() const
//    {
//      return static_cast<char>(_val);
//    }
//
//    inline static Side fromChar(char val)
//    {
//      switch (val)
//      {
//        case 'A': return Side(BUY);
//        case 'V': return Side(SELL);
//        default: return Side(UNKNOWN);
//      }
//    }
//
//    Side& operator=(Side::Opts opt)
//    {
//      _val = opt;
//      return *this;
//    }
//
//    bool operator==(const Side::Opts& rhs) const
//    {
//      return _val == rhs;
//    }
//
//    bool operator!=(const Side::Opts& rhs) const
//    {
//      return _val != rhs;
//    }
//
//  private:
//    Opts _val;
//  };

  //
//  struct AssetType
//  {
//    enum Opts: int8_t
//    {
//      UNKNOWN,            //Unknown
//      SPOT,               // Ativo à vista
//      OPTION,             // Opção
//      INDEX,              // Índice
//      COMMODITY,          // Commodity
//      CURRENCY,           // Moeda
//      TERM,               // Termo
//      FUTURE,             // Futuro
//      AUCTION,            // Leilão
//      BONUS,              // Bônus
//      FRACTIONAL,         // Fracionário
//      OPTION_EXERCISE,    // Exercício de opção
//      INDICATOR,          // Indicador
//      ETF,                // ETF
//      VOLUME,             // Volume
//      OPTION_ON_SPOT,     // Opção sobre à vista
//      OPTION_ON_FUTURE,   // Opção sobre futuro
//      TEST_ASSET,         // Ativo de teste
//      STRATEGY,           // Estratégia
//      CORPORATE,          // Corp
//      SECLOAN,            // Aluguel BTB
//      TREASURY_DIRECT     // Tesouro direto
//    };
//
//    explicit AssetType(Opts opt) :
//    _val(opt)
//    {}
//
//    std::string toString() const
//    {
//      switch (_val) {
//        case SPOT: return "SPOT";
//        case OPTION: return "OPTION";
//        case INDEX: return "INDEX";
//        case COMMODITY: return "COMMODITY";
//        case CURRENCY: return "CURRENCY";
//        case TERM: return "TERM";
//        case FUTURE: return "FUTURE";
//        case AUCTION: return "AUCTION";
//        case BONUS: return "BONUS";
//        case FRACTIONAL: return "FRACTIONAL";
//        case OPTION_EXERCISE: return "OPTION_EXERCISE";
//        case INDICATOR: return "INDICATOR";
//        case ETF: return "ETF";
//        case VOLUME: return "Volume";
//        case OPTION_ON_SPOT: return "OPTION_ON_SPOT";
//        case OPTION_ON_FUTURE: return "OPTION_ON_FUTURE";
//        case TEST_ASSET: return "TEST_ASSET";
//        case STRATEGY: return "STRATEGY";
//        case CORPORATE: return "CORPORATE";
//        case SECLOAN: return "SECLOAN";
//        case TREASURY_DIRECT: return "TREASURY_DIRECT";
//        default: return "Unknown";
//      }
//    }
//
//    inline static AssetType fromInt(int val)
//    {
//      switch (val)
//      {
//        case 1: return AssetType(SPOT);
//        case 2: return AssetType(OPTION);
//        case 3: return AssetType(INDEX);
//        case 4: return AssetType(COMMODITY);
//        case 5: return AssetType(CURRENCY);
//        case 6: return AssetType(TERM);
//        case 7: return AssetType(FUTURE);
//        case 8: return AssetType(AUCTION);
//        case 9: return AssetType(BONUS);
//        case 10: return AssetType(FRACTIONAL);
//        case 11: return AssetType(OPTION_EXERCISE);
//        case 12: return AssetType(INDICATOR);
//        case 13: return AssetType(ETF);
//        case 15: return AssetType(VOLUME);
//        case 16: return AssetType(OPTION_ON_SPOT);
//        case 17: return AssetType(OPTION_ON_FUTURE);
//        case 18: return AssetType(TEST_ASSET);
//        case 19: return AssetType(STRATEGY);
//        case 20: return AssetType(CORPORATE);
//        case 21: return AssetType(SECLOAN);
//        case 22: return AssetType(TREASURY_DIRECT);
//        default: return AssetType(UNKNOWN);
//      }
//    }
//
//    AssetType& operator=(AssetType::Opts opt)
//    {
//      _val = opt;
//      return *this;
//    }
//
//    bool operator==(const AssetType::Opts& rhs) const
//    {
//      return _val == rhs;
//    }
//
//    bool operator!=(const AssetType::Opts& rhs) const
//    {
//      return _val != rhs;
//    }
//
//  private:
//    Opts _val;
//  };
//
//  struct MarketCode
//  {
//    enum Opts: int8_t
//    {
//      UNKNOWN = 0,          // Unknown
//      BOVESPA = 1,          // Bovespa
//      DOW_JONES = 2,        // Dow Jones
//      BMF = 3,              // BM&F
//      INDICES = 4,          // Índices
//      MONEY = 5,            // Money
//      SOMA = 6,             // Soma
//      FOREX = 7,            // Forex
//      INDICATORS = 8,       // Indicators
//      OTHERS = 9,           // Others
//      NYSE = 10,            // Nyse
//      BATS = 11,            // Bats
//      NASDAQ = 12,          // Nasdaq
//      BVL = 14,             // BVL (Bolsa de Valores de Lima)
//      SP_INDEXES = 15,      // S&P Indexes
//      LIFFE = 16,           // Liffe
//      EURONEXT_INDICES = 17,// Euronext Indices
//      CME = 18,             // CME
//      CME_MINI = 19         // CME Mini
//    };
//
//    explicit MarketCode(Opts opt) :
//    _val(opt)
//    {}
//
//    std::string toString() const
//    {
//      switch (_val) {
//        case BOVESPA: return "BOVESPA";
//        case DOW_JONES: return "DOW_JONES";
//        case BMF: return "BMF";
//        case INDICES: return "INDICES";
//        case MONEY: return "MONEY";
//        case SOMA: return "SOMA";
//        case FOREX: return "FOREX";
//        case INDICATORS: return "INDICATORS";
//        case OTHERS: return "OTHERS";
//        case NYSE: return "NYSE";
//        case BATS: return "BATS";
//        case NASDAQ: return "NASDAQ";
//        case BVL: return "BVL";
//        case SP_INDEXES: return "SP_INDEXES";
//        case LIFFE: return "LIFFE";
//        case EURONEXT_INDICES: return "EURONEXT_INDICES";
//        case CME: return "CME";
//        case CME_MINI: return "CME_MINI";
//        default: return "UNKNOWN";
//      }
//    }
//
//    inline static MarketCode fromInt(int val)
//    {
//      switch (val)
//      {
//        case 1: return MarketCode(BOVESPA);
//        case 2: return MarketCode(DOW_JONES);
//        case 3: return MarketCode(BMF);
//        case 4: return MarketCode(INDICES);
//        case 5: return MarketCode(MONEY);
//        case 6: return MarketCode(SOMA);
//        case 7: return MarketCode(FOREX);
//        case 8: return MarketCode(INDICATORS);
//        case 9: return MarketCode(OTHERS);
//        case 10: return MarketCode(NYSE);
//        case 11: return MarketCode(BATS);
//        case 12: return MarketCode(NASDAQ);
//        case 14: return MarketCode(BVL);
//        case 15: return MarketCode(SP_INDEXES);
//        case 16: return MarketCode(LIFFE);
//        case 17: return MarketCode(EURONEXT_INDICES);
//        case 18: return MarketCode(CME);
//        case 19: return MarketCode(CME_MINI);
//        default: return MarketCode(UNKNOWN);
//      }
//    }
//
//    MarketCode& operator=(MarketCode::Opts opt)
//    {
//      _val = opt;
//      return *this;
//    }
//
//    bool operator==(const MarketCode::Opts& rhs) const
//    {
//      return _val == rhs;
//    }
//
//    bool operator!=(const MarketCode::Opts& rhs) const
//    {
//      return _val != rhs;
//    }
//
//  private:
//    Opts _val;
//  };
//
//  struct InstrumentStatus
//  {
//    enum Opts: int16_t
//    {
//      UNKNOWN,      // Não informado
//      NORMAL,       // Normal
//      AUCTION,      // Leilão
//      SUSPENDED,    // Suspenso
//      FROZEN,       // Congelado
//      EMPTY         // Vazio (apenas para internacionais)
//    };
//
//    explicit InstrumentStatus(Opts opt) : _val(opt) {}
//
//    std::string toString() const
//    {
//      switch (_val) {
//        case NORMAL: return "NORMAL";
//        case AUCTION: return "AUCTION";
//        case SUSPENDED: return "SUSPENDED";
//        case FROZEN: return "FROZEN";
//        case EMPTY: return "EMPTY";
//        default: return "UNKNOWN";
//      }
//    }
//
//    inline static InstrumentStatus fromInt(int val)
//    {
//      switch (val)
//      {
//        case 101: return InstrumentStatus(NORMAL);
//        case 102: return InstrumentStatus(AUCTION);
//        case 105: return InstrumentStatus(SUSPENDED);
//        case 118: return InstrumentStatus(FROZEN);
//        case -1: return InstrumentStatus(EMPTY);
//        default: return InstrumentStatus(UNKNOWN);
//      }
//    }
//
//    InstrumentStatus& operator=(InstrumentStatus::Opts opt)
//    {
//      _val = opt;
//      return *this;
//    }
//
//    bool operator==(const InstrumentStatus::Opts& rhs) const
//    {
//      return _val == rhs;
//    }
//
//    bool operator!=(const InstrumentStatus::Opts& rhs) const
//    {
//      return _val != rhs;
//    }
//
//  private:
//    Opts _val;
//  };
//
//  struct OptionType
//  {
//    enum Opts: int8_t
//    {
//      UNKNOWN,        // unknow
//      NOT_SPECIFIED,  // Não especificado ou sem opção
//      AMERICAN,       // Opção Americana
//      EUROPEAN,       // Opção Europeia
//    };
//
//    explicit OptionType(Opts opt) : _val(opt) {}
//
//    std::string toString() const
//    {
//      switch (_val) {
//        case NOT_SPECIFIED: return "NOT_SPECIFIED";
//        case AMERICAN: return "AMERICAN";
//        case EUROPEAN: return "EUROPEAN";
//        default: return "UNKNOWN";
//      }
//    }
//
//    inline static OptionType fromChar(char val)
//    {
//      switch (val)
//      {
//        case 'A': return OptionType(AMERICAN);
//        case 'E': return OptionType(EUROPEAN);
//        case '0': return OptionType(NOT_SPECIFIED);
//        default: return OptionType(UNKNOWN);
//      }
//    }
//
//    OptionType& operator=(OptionType::Opts opt)
//    {
//      _val = opt;
//      return *this;
//    }
//
//    bool operator==(const OptionType::Opts& rhs) const
//    {
//      return _val == rhs;
//    }
//
//    bool operator!=(const OptionType::Opts& rhs) const
//    {
//      return _val != rhs;
//    }
//
//  private:
//    Opts _val;
//  };
//
//  struct OptionDirection
//  {
//    enum Opts: int8_t
//    {
//      UNKNOWN,
//      CALL,   //  buy
//      PUT     //  sell
//    };
//
//    explicit OptionDirection(Opts opt) : _val(opt) {}
//
//    std::string toString() const
//    {
//      switch (_val) {
//        case CALL: return "CALL";
//        case PUT: return "PUT";
//        default: return "UNKNOWN";
//      }
//    }
//
//    inline static OptionDirection fromChar(char val)
//    {
//      switch (val)
//      {
//        case 'C': return OptionDirection(CALL);
//        case 'P': return OptionDirection(PUT);
//        default: return OptionDirection(UNKNOWN);
//      }
//    }
//
//    OptionDirection& operator=(OptionDirection::Opts opt)
//    {
//      _val = opt;
//      return *this;
//    }
//
//    bool operator==(const OptionDirection::Opts& rhs) const
//    {
//      return _val == rhs;
//    }
//
//    bool operator!=(const OptionDirection::Opts& rhs) const
//    {
//      return _val != rhs;
//    }
//
//  private:
//    Opts _val;
//  };
//
//  struct AssetStatus
//  {
//    enum Opts: int8_t
//    {
//      UNKNOWN = -1,   // Unknown
//      NORMAL = 0,     // Negociação normal
//      FROZEN = 1,     // Congelado
//      SUSPENDED = 2,  // Suspenso
//      AUCTION = 3,    // Leilão
//      INHIBITED = 4   // Inibido
//    };
//
//    explicit AssetStatus(Opts opt) : _val(opt) {}
//
//    std::string toString() const
//    {
//      switch (_val) {
//        case NORMAL: return "NORMAL";
//        case FROZEN: return "FROZEN";
//        case SUSPENDED: return "SUSPENDED";
//        case AUCTION: return "AUCTION";
//        case INHIBITED: return "INHIBITED";
//        default: return "UNKNOWN";
//      }
//    }
//
//    int toInt() const
//    {
//      return static_cast<int>(_val);
//    }
//
//    inline static AssetStatus fromInt(int val)
//    {
//      switch (val)
//      {
//        case 0: return AssetStatus(NORMAL);
//        case 1: return AssetStatus(FROZEN);
//        case 2: return AssetStatus(SUSPENDED);
//        case 3: return AssetStatus(AUCTION);
//        case 4: return AssetStatus(INHIBITED);
//        default: return AssetStatus(UNKNOWN);
//      }
//    }
//
//    AssetStatus& operator=(AssetStatus::Opts opt)
//    {
//      _val = opt;
//      return *this;
//    }
//
//    bool operator==(const AssetStatus::Opts& rhs) const
//    {
//      return _val == rhs;
//    }
//
//    bool operator!=(const AssetStatus::Opts& rhs) const
//    {
//      return _val != rhs;
//    }
//
//  private:
//    Opts _val;
//  };
//
//  struct AssetGroupPhase
//  {
//    enum Opts : int8_t
//    {
//      UNKNOWN,              // Unknown or not specified
//      PRE_OPENING,          // P - Pre abertura
//      OPENING,              // A - Abertura
//      PRE_CLOSING,          // PN - Pré fechamento
//      CLOSING,              // N - Fechamento
//      PRE_OPENING_AFTER,    // E - Pré abertura after
//      OPENING_AFTER,        // R - Abertura after
//      CLOSING_AFTER,        // NE - Fechamento after
//      FINAL,                // F - Final
//      CLOSED,               // NO - Fechado
//      PAUSED                // T - Pausado
//    };
//
//    explicit AssetGroupPhase(Opts opt) : _val(opt) {}
//
//    std::string toString() const
//    {
//      switch (_val) {
//        case Opts::PRE_OPENING: return "PRE_OPENING";
//        case Opts::OPENING: return "OPENING";
//        case Opts::PRE_CLOSING: return "PRE_CLOSING";
//        case Opts::CLOSING: return "CLOSING";
//        case Opts::PRE_OPENING_AFTER: return "PRE_OPENING_AFTER";
//        case Opts::OPENING_AFTER: return "OPENING_AFTER";
//        case Opts::CLOSING_AFTER: return "CLOSING_AFTER";
//        case Opts::FINAL: return "FINAL";
//        case Opts::CLOSED: return "CLOSED";
//        case Opts::PAUSED: return "PAUSED";
//        default: return "UNKNOWN";
//      }
//    }
//
//    inline static AssetGroupPhase fromString(const std::string& val)
//    {
//      if(val == "P") return     AssetGroupPhase(Opts::PRE_OPENING);
//      if(val == "A") return     AssetGroupPhase(Opts::OPENING);
//      if(val == "PN") return    AssetGroupPhase(Opts::PRE_CLOSING);
//      if(val == "N") return     AssetGroupPhase(Opts::CLOSING);
//      if(val == "E") return     AssetGroupPhase(Opts::PRE_OPENING_AFTER);
//      if(val == "R") return     AssetGroupPhase(Opts::OPENING_AFTER);
//      if(val == "NE") return    AssetGroupPhase(Opts::CLOSING_AFTER);
//      if(val == "F") return     AssetGroupPhase(Opts::FINAL);
//      if(val == "NO") return    AssetGroupPhase(Opts::CLOSED);
//      if(val == "T") return     AssetGroupPhase(Opts::PAUSED);
//      return AssetGroupPhase(Opts::UNKNOWN);
//    }
//
//    AssetGroupPhase& operator=(AssetGroupPhase::Opts opt)
//    {
//      _val = opt;
//      return *this;
//    }
//
//    bool operator==(const AssetGroupPhase::Opts& rhs) const
//    {
//      return _val == rhs;
//    }
//
//    bool operator!=(const AssetGroupPhase::Opts& rhs) const
//    {
//      return _val != rhs;
//    }
//
//  private:
//    Opts _val;
//  };
//
//  struct MarketType
//  {
//    enum Opts : int8_t
//    {
//      UNKNOWN,        // Unknown or not specified
//      REAL_TIME,      // RT - Real-time
//      DELAY,          // D - Delay
//      END_OF_DAY      // EOD - End of Day
//    };
//
//    explicit MarketType(Opts opt) : _val(opt) {}
//
//    std::string toString() const
//    {
//      switch (_val) {
//        case Opts::REAL_TIME: return "REAL_TIME";
//        case Opts::DELAY: return "DELAY";
//        case Opts::END_OF_DAY: return "END_OF_DAY";
//        default: return "UNKNOWN";
//      }
//    }
//
//    inline static MarketType fromString(const std::string& val)
//    {
//      if(val == "RT") return     MarketType(Opts::REAL_TIME);
//      if(val == "D") return      MarketType(Opts::DELAY);
//      if(val == "EOD") return    MarketType(Opts::END_OF_DAY);
//      return MarketType(Opts::UNKNOWN);
//    }
//
//    MarketType& operator=(MarketType::Opts opt)
//    {
//      _val = opt;
//      return *this;
//    }
//
//    bool operator==(const MarketType::Opts& rhs) const
//    {
//      return _val == rhs;
//    }
//
//    bool operator!=(const MarketType::Opts& rhs) const
//    {
//      return _val != rhs;
//    }
//
//  private:
//    Opts _val;
//  };
}
#endif //CEDRO_MD_CMDTYPES_H
