//
// Created by Arthur Motelevicz on 30/07/24.
//

#ifndef CEDRO_MD_SQTMODEL_H
#define CEDRO_MD_SQTMODEL_H

#include <string>
#include <vector>
#include "CMDTypes.h"

namespace cedro::md::models
{
  enum SQTFieldID : int16_t
  {
    LAST_MOD_TIME = 0,                // 0 - Horário da última modificação (HHMMSS)
    LAST_MOD_DATE = 1,                // 1 - Data da última modificação (YYYYMMDD)
    LAST_TRADE_PRICE = 2,             // 2 - Preço do último negócio
    BEST_BID_PRICE = 3,               // 3 - Melhor oferta de compra
    BEST_ASK_PRICE = 4,               // 4 - Melhor oferta de venda
    LAST_TRADE_TIME = 5,              // 5 - Horário do último negócio (HHMMSS)
    CURRENT_TRADE_SIZE = 6,           // 6 - Quantidade do negócio atual
    LAST_TRADE_SIZE = 7,              // 7 - Quantidade do último negócio
    TOTAL_TRADES = 8,                 // 8 - Quantidade de negócios realizados
    TOTAL_VOLUME = 9,                 // 9 - Volume acumulado dos negócios
    TOTAL_FINANCIAL_VOLUME = 10,      // 10 - Volume financeiro dos negócios
    HIGHEST_PRICE_OF_DAY = 11,        // 11 - Maior preço do dia
    LOWEST_PRICE_OF_DAY = 12,         // 12 - Menor preço do dia
    PREVIOUS_DAY_CLOSE_PRICE = 13,    // 13 - Preço de fechamento do dia anterior
    OPENING_PRICE = 14,               // 14 - Preço de abertura
    BEST_BID_TIME = 15,               // 15 - Horário da melhor oferta de compra (HHMMSS)
    BEST_ASK_TIME = 16,               // 16 - Horário da melhor oferta de venda (HHMMSS)
    BEST_BID_VOLUME = 17,             // 17 - Volume acumulado das melhores ofertas de compra
    BEST_ASK_VOLUME = 18,             // 18 - Volume acumulado das melhores ofertas de venda
    BEST_BID_SIZE = 19,               // 19 - Volume da melhor oferta de compra
    BEST_ASK_SIZE = 20,               // 20 - Volume da melhor oferta de venda
    VARIATION = 21,                   // 21 - Variação do preço
    LAST_WEEK_CLOSE_PRICE = 36,       // 36 - Preço de fechamento da última semana
    LAST_MONTH_CLOSE_PRICE = 37,      // 37 - Preço de fechamento do último mês
    LAST_YEAR_CLOSE_PRICE = 38,       // 38 - Preço de fechamento do último ano
    PREVIOUS_DAY_OPENING_PRICE = 39,  // 39 - Preço de abertura do dia anterior
    PREVIOUS_DAY_HIGHEST_PRICE = 40,  // 40 - Maior preço do dia anterior
    PREVIOUS_DAY_LOWEST_PRICE = 41,   // 41 - Menor preço do dia anterior
    AVERAGE_PRICE = 42,               // 42 - Média do preço
    VH_DAILY = 43,                    // 43 - VHDaily
    MARKET_CODE = 44,                 // 44 - Código do Mercado
    ASSET_TYPE = 45,                  // 45 - Código do tipo do ativo
    STANDARD_LOT = 46,                // 46 - Lote padrão
    ASSET_DESCRIPTION = 47,           // 47 - Descrição do ativo
    CLASSIFICATION_NAME = 48,         // 48 - Nome de classificação
    QUOTE_FORM = 49,                  // 49 - Forma de cotação
    INTRADAY_DATE = 50,               // 50 - Intraday Date (YYYYMMDDHHMMSS)
    LAST_TRADE_DATE = 51,             // 51 - LastTrade Date (YYYYMMDDHHMMSS)
    SHORT_ASSET_DESCRIPTION = 52,     // 52 - Descrição abreviada do ativo
    CANCELED_TRADE_ID = 53,           // 53 - Identificador do negócio cancelado
    LAST_TRADE_DATE_SIMPLE = 54,      // 54 - Data do último negócio (YYYYMMDD)
    OPENING_UNFULFILLED_SIDE = 56,    // 56 - Sentido das ofertas não atendidas ao preço de abertura
    OPENING_UNFULFILLED_SIZE = 57,    // 57 - Quantidade não atendida ao preço de abertura
    SCHEDULED_OPENING_TIME = 58,      // 58 - Horário programado para abertura do papel (HHMMSS)
    RESCHEDULED_OPENING_TIME = 59,    // 59 - Horário reprogramado para abertura do papel (HHMMSS)
    BEST_BID_BROKER = 60,             // 60 - Código da corretora que fez a melhor oferta de compra
    BEST_ASK_BROKER = 61,             // 61 - Código da corretora que fez a melhor oferta de venda
    LAST_BUY_BROKER = 62,             // 62 - Código da corretora que realizou a última compra
    LAST_SELL_BROKER = 63,            // 63 - Código da corretora que realizou a última venda
    OPTION_EXPIRATION_DATE = 64,      // 64 - Data do vencimento (Mercado de opções) (YYYYMMDD)
    EXPIRED = 65,                     // 65 - Expirado
    TOTAL_PAPERS = 66,                // 66 - Número total de papéis
    INSTRUMENT_STATUS = 67,           // 67 - Status do instrumento
    OPTION_TYPE = 72,                 // 72 - Tipo da opção (A = Americana, E = Européia, 0 = não existe)
    OPTION_DIRECTION = 74,            // 74 - Direção da opção (P = venda, C = compra)
    PARENT_SYMBOL = 81,               // 81 - Símbolo do ativo pai (para opções)
    THEORETICAL_OPENING_PRICE = 82,   // 82 - Preço teórico de abertura
    THEORETICAL_SIZE = 83,            // 83 - Quantidade teórica
    ASSET_STATUS = 84,                // 84 - Status do ativo
    STRIKE_PRICE = 85,                // 85 - Preço de Exercício
    DIFF_PRICE = 86,                  // 86 - Diff (Preço Atual - Previous)
    PREVIOUS_DAY = 87,                // 87 - Data do Previous (YYYYMMDD)
    ASSET_GROUP_PHASE = 88,           // 88 - Fase do grupo do ativo
    PREVIOUS_DAY_AVERAGE_PRICE = 89,  // 89 - Média do dia anterior
    MARGIN_RANGE = 90,                // 90 - Intervalo de Margem (mercado BTC)
    AVERAGE_VOLUME_20_DAYS = 94,      // 94 - Volume médio nos últimos 20 dias
    MARKET_CAPITALIZATION = 95,       // 95 - Market Capitalization
    MARKET_TYPE = 96,                 // 96 - Tipo de Mercado (RT = RealTime, D = Delay , EOD = End of Day)
    WEEK_CLOSE_VARIATION = 97,        // 97 - Variação do fechamento em uma semana
    MONTH_CLOSE_VARIATION = 98,       // 98 - Variação do fechamento em um mês
    YEAR_CLOSE_VARIATION = 99,        // 99 - Variação do fechamento em um ano
    OPEN_CONTRACTS = 100,             // 100 - Quantidade de contratos abertos
    BUSINESS_DAYS_TO_EXPIRY = 101,    // 101 - Número dias úteis até o vencimento
    DAYS_TO_EXPIRY = 102,             // 102 - Número dias para o vencimento
    ADJUSTMENT_PRICE = 103,           // 103 - Ajuste do dia
    PREVIOUS_DAY_ADJUSTMENT_PRICE = 104, // 104 - Ajuste do dia anterior
    SECURITY_ID = 105,                // 105 - SecurityId (BMF FIX)
    TICK_DIRECTION = 106,             // 106 - TickDirection(BMF FIX)
    TUNNEL_UPPER_LIMIT = 107,         // 107 - TunnelUpperLimit
    TUNNEL_LOWER_LIMIT = 108,         // 108 - TunnelLowerLimit
    TRADING_PHASE = 109,              // 109 - TradingPhase(BMF FIX)
    TICK_SIZE = 110,                  // 110 - TickSize
    MIN_TRADE_VOLUME = 111,           // 111 - Volume mínimo de negociação do instrumento
    MIN_PRICE_INCREMENT = 112,        // 112 - Intervalo mínimo para incrementos de preço
    MIN_OFFER_SIZE = 113,             // 113 - Quantidade mínima para o instrumento em uma oferta
    MAX_OFFER_SIZE = 114,             // 114 - Quantidade máxima para o instrumento em uma oferta
    UNIQUE_INSTRUMENT_ID = 115,       // 115 - Número único de identificação do instrumento
    CURRENCY = 116,                   // 116 - Moeda utilizada no preço
    SECURITY_TYPE = 117,              // 117 - SecurityType
    SECURITY_SUB_TYPE = 118,          // 118 - Código de negociação do instrumento
    ASSOCIATED_PRODUCT = 119,         // 119 - Produto associado ao instrumento
    EXPIRY_MONTH_YEAR = 120,          // 120 - Mês e ano de vencimento (YYYYMM)
    OPTION_STRIKE_PRICE = 121,        // 121 - Preço de exercício da opção
    OPTION_CURRENCY = 122,            // 122 - Moeda do preço de exercício da opção
    CONTRACT_MULTIPLIER = 123,        // 123 - Multiplicador do contrato
    PRICE_TYPE = 124,                 // 124 - Código que representa o tipo de preço do instrumento
    END_OF_TRADE_TIME = 125,          // 125 - Horário em que um instrumento não é mais passível de negociação (YYYYMMDDHHMMSS)
    ASSET_GROUP = 126,                // 126 - Indica o grupo ao qual o ativo pertence
    CURRENT_ADJUSTMENT_RATE = 127,    // 127 - Ajuste atual em taxa
    PREVIOUS_ADJUSTMENT_RATE = 128,   // 128 - Ajuste anterior em taxa
    CURRENT_ADJUSTMENT_DATE = 129,    // 129 - Data do Ajuste atual em taxa (YYYYMMDD)
    WITHDRAWALS_TO_EXPIRY = 130,      // 130 - Número de saques até data de vencimento
    HOURLY_VOLUME_VARIATION = 134,    // 134 - Variação do volume da hora com base na média do volume do horário nos últimos 20 dias
    CUMULATIVE_VOLUME_VARIATION = 135,// 135 - Variação do volume até a hora com base na média do volume até o horário nos últimos 20 dias
    SECTOR_CODE = 136,                // 136 - Código do setor do Ativo
    SUBSECTOR_CODE = 137,             // 137 - Código do subsetor do Ativo
    SEGMENT_CODE = 138,               // 138 - Código do segmento do Ativo
    ADJUSTMENT_TYPE = 139,            // 139 - Tipo do ajuste atual em taxa
    REFERENCE_PRICE = 140,            // 140 - Preço de referência
    REFERENCE_DATE = 141,             // 141 - Data do preço de referência
    LAST_MOD_TIME_MILLIS = 142,       // 142 - Horário da última modificação com milissegundos (HHMMSSmmm)
    LAST_TRADE_TIME_MILLIS = 143,     // 143 - Horário do último negócio com milissegundos (HHMMSSmmm)
    BEST_BID_TIME_MILLIS = 144,     // 143 - Horário do último negócio com milissegundos (HHMMSSmmm)
    BEST_ASK_TIME_MILLIS = 145,     // 143 - Horário do último negócio com milissegundos (HHMMSSmmm)
    ADJUSTED_PRICE_VARIATION = 146,   // 146 - Variação utilizando o ajuste do dia anterior
    DIFF_ADJUSTED_PRICE = 147,        // 147 - Diff (Preço Atual - Ajuste do dia anterior)
    TUNNEL_UPPER_AUCTION_LIMIT = 148, // 148 - Tunnel Upper Auction Limit (Auction Band)
    TUNNEL_LOWER_AUCTION_LIMIT = 149, // 149 - Tunnel Lower Auction Limit (Auction Band)
    TUNNEL_UPPER_REJECTION_LIMIT = 150,// 150 - Tunnel Upper Rejection Limit (Rejection Band)
    TUNNEL_LOWER_REJECTION_LIMIT = 151,// 151 - Tunnel Lower Rejection Limit (Rejection Band)
    TUNNEL_UPPER_STATIC_LIMIT = 152,  // 152 - Tunnel Upper Static Limit (Static Limit)
    TUNNEL_LOWER_STATIC_LIMIT = 153,  // 153 - Tunnel Lower Static Limit (Static Limit)

    // Campos exclusivos do Tesouro Direto
    UNIT_PRICE = 200,                 // 200 - Preço unitário
    RATE_VALUE = 201,                 // 201 - Valor da taxa (Rentabilidade)
    MIN_APPLICATION_VALUE = 202,      // 202 - Valor mínimo de aplicação
    TREASURY_MARKET = 203,            // 203 - Mercado
    TITLE_CODE = 204,                 // 204 - Código do título
    TYPE_CODE = 205,                  // 205 - Código do tipo
    TYPE_NAME = 206,                  // 206 - Nome do tipo
    SELIC_CODE = 207,                 // 207 - Selic
    ISSUE_DATE = 208,                 // 208 - Data de emissão (YYYYMMDD)
    TRANSACTION_ID = 209,             // 209 - Negócio
    BASE_VALUE = 210,                 // 210 - Valor base
    BUY_RATE = 211,                   // 211 - Valor da taxa de compra
    SELL_RATE = 212,                  // 212 - Valor da taxa de venda
    INDEXER_CODE = 213,               // 213 - Código indexador
    INDEXER_NAME = 214,               // 214 - Nome indexador
    TITLE_NAME = 215                  // 215 - Nome do título
  };

  // The type from the docs
  enum DataType
  {
    INVALID,
    CHAR,
    STRING,
    INT,
    FLOAT,
  };


  struct SQTModel
  {
    char symbol[MAX_STRING_SIZE]="";                             // Header 1
    char time[MAX_STRING_SIZE]="";                               // Header 2
    char lastModTime[MAX_STRING_SIZE]="";                        // 0 - Horário da última modificação (HHMMSS)
    char lastModDate[MAX_STRING_SIZE]="";                        // 1 - Data da última modificação (YYYYMMDD)
    double lastTradePrice{dNaN};                         // 2 - Preço do último negócio
    double bestBidPrice{dNaN};                           // 3 - Melhor oferta de compra
    double bestAskPrice{dNaN};                           // 4 - Melhor oferta de venda
    char lastTradeTime[MAX_STRING_SIZE]="";                      // 5 - Horário do último negócio (HHMMSS)
    int32_t currentTradeSize{INVALID_INT32};                    // 6 - Quantidade do negócio atual
    int32_t lastTradeSize{INVALID_INT32};                       // 7 - Quantidade do último negócio
    int32_t totalTrades{INVALID_INT32};                         // 8 - Quantidade de negócios realizados
    int32_t totalVolume{INVALID_INT32};                         // 9 - Volume acumulado dos negócios
    double totalFinancialVolume{dNaN};                   // 10 - Volume financeiro dos negócios
    double highestPriceOfDay{dNaN};                      // 11 - Maior preço do dia
    double lowestPriceOfDay{dNaN};                       // 12 - Menor preço do dia
    double previousDayClosePrice{dNaN};                  // 13 - Preço de fechamento do dia anterior
    double openingPrice{dNaN};                           // 14 - Preço de abertura
    char bestBidTime[MAX_STRING_SIZE]="";                        // 15 - Horário da melhor oferta de compra (HHMMSS)
    char bestAskTime[MAX_STRING_SIZE]="";                        // 16 - Horário da melhor oferta de venda (HHMMSS)"
    double bestBidVolume{dNaN};                          // 17 - Volume acumulado das melhores ofertas de compra
    double bestAskVolume{dNaN};                          // 18 - Volume acumulado das melhores ofertas de venda
    int32_t bestBidSize{INVALID_INT32};                         // 19 - Volume da melhor oferta de compra
    int32_t bestAskSize{INVALID_INT32};                         // 20 - Volume da melhor oferta de venda
    double variation{dNaN};                              // 21 - Variação do preço
    double lastWeekClosePrice{dNaN};                     // 36 - Preço de fechamento da última semana
    double lastMonthClosePrice{dNaN};                    // 37 - Preço de fechamento do último mês
    double lastYearClosePrice{dNaN};                     // 38 - Preço de fechamento do último ano
    double previousDayOpeningPrice{dNaN};                // 39 - Preço de abertura do dia anterior
    double previousDayHighestPrice{dNaN};                // 40 - Maior preço do dia anterior
    double previousDayLowestPrice{dNaN};                 // 41 - Menor preço do dia anterior
    double averagePrice{dNaN};                           // 42 - Média do preço
    double vhDaily{dNaN};                                // 43 - VHDaily //TODO: understand it (volatility history daily???)
    int32_t marketCode{INVALID_INT32};                          // 44 - Código do Mercado
    int32_t assetType{INVALID_INT32};                           // 45 - Código do tipo do ativo
    int32_t standardLot{INVALID_INT32};                         // 46 - Lote padrão
    char assetDescription[MAX_STRING_SIZE]="";                   // 47 - Descrição do ativo
    char classificationName[MAX_STRING_SIZE]="";                 // 48 - Nome de classificação
    int32_t quoteForm{INVALID_INT32};                           // 49 - Forma de cotação
    char intradayDate[MAX_STRING_SIZE]="";                       // 50 - Intraday Date (YYYYMMDDHHMMSS)
    char lastTradeDate[MAX_STRING_SIZE]="";                      // 51 - LastTrade Date (YYYYMMDDHHMMSS)
    char shortAssetDescription[MAX_STRING_SIZE]="";              // 52 - Descrição abreviada do ativo
    char canceledTradeId[MAX_STRING_SIZE]="";                    // 53 - Identificador do negócio cancelado
    char lastTradeDateSimple[MAX_STRING_SIZE]="";                // 54 - Data do último negócio (YYYYMMDD)
    char openingUnfulfilledSide{'x'};               // 56 - Sentido das ofertas não atendidas ao preço de abertura
    int32_t openingUnfulfilledSize{INVALID_INT32};              // 57 - Quantidade não atendida ao preço de abertura
    char scheduledOpeningTime[MAX_STRING_SIZE]="";               // 58 - Horário programado para abertura do papel (HHMMSS)
    char rescheduledOpeningTime[MAX_STRING_SIZE]="";             // 59 - Horário reprogramado para abertura do papel (HHMMSS)
    int32_t bestBidBroker{INVALID_INT32};                       // 60 - Código da corretora que fez a melhor oferta de compra
    int32_t bestAskBroker{INVALID_INT32};                       // 61 - Código da corretora que fez a melhor oferta de venda
    int32_t lastBuyBroker{INVALID_INT32};                       // 62 - Código da corretora que realizou a última compra
    int32_t lastSellBroker{INVALID_INT32};                      // 63 - Código da corretora que realizou a última venda
    char optionExpirationDate[MAX_STRING_SIZE]="";               // 64 - Data do vencimento (Mercado de opções) (YYYYMMDD)
    int8_t expired{INVALID_INT8};                          // 65 - Expirado
    char totalPapers[MAX_STRING_SIZE]="";                        // 66 - Número total de papéis
    int32_t instrumentStatus{INVALID_INT32};                    // 67 - Status do instrumento TODO: understand it (versus asset???)
    char optionType{'\0'};                           // 72 - Tipo da opção (A = Americana, E = Européia, 0 = não existe)
    char optionDirection{'\0'};                      // 74 - Direção da opção (P = venda, C = compra)
    char parentSymbol[MAX_STRING_SIZE]="";                       // 81 - Símbolo do ativo pai (para opções)
    double theoreticalOpeningPrice{dNaN};                // 82 - Preço teórico de abertura
    int32_t theoreticalSize{INVALID_INT32};                     // 83 - Quantidade teórica
    int32_t assetStatus{INVALID_INT32};                        // 84 - Status do ativo TODO: understand it (versus instrument???)
    double strikePrice{dNaN};                            // 85 - Preço de Exercício
    double diffPrice{dNaN};                              // 86 - Diff (Preço Atual - Previous)
    char previousDay[MAX_STRING_SIZE]="";                        // 87 - Data do Previous (YYYYMMDD)
    char assetGroupPhase[MAX_STRING_SIZE]="";                    // 88 - Fase do grupo do ativo
    double previousDayAveragePrice{dNaN};                // 89 - Média do dia anterior
    double marginRange{dNaN};                            // 90 - Intervalo de Margem (mercado BTC)
    double averageVolume20Days{dNaN};                    // 94 - Volume médio nos últimos 20 dias
    double marketCapitalization{dNaN};                   // 95 - Market Capitalization
    char marketType[MAX_STRING_SIZE]="";                         // 96 - Tipo de Mercado (RT = RealTime, D = Delay , EOD = End of Day)
    double weekCloseVariation{dNaN};                     // 97 - Variação do fechamento em uma semana
    double monthCloseVariation{dNaN};                    // 98 - Variação do fechamento em um mês
    double yearCloseVariation{dNaN};                     // 99 - Variação do fechamento em um ano
    int32_t openContracts{INVALID_INT32};                       // 100 - Quantidade de contratos abertos
    int32_t businessDaysToExpiry{INVALID_INT32};                // 101 - Número dias úteis até o vencimento
    int32_t daysToExpiry{INVALID_INT32};                        // 102 - Número dias para o vencimento
    double adjustmentPrice{dNaN};                        // 103 - Ajuste do dia
    double previousDayAdjustmentPrice{dNaN};             // 104 - Ajuste do dia anterior
    char securityId[MAX_STRING_SIZE]="";                         // 105 - SecurityId (BMF FIX)
    char tickDirection[MAX_STRING_SIZE]="";                      // 106 - TickDirection(BMF FIX)
    double tunnelUpperLimit{dNaN};                       // 107 - TunnelUpperLimit
    double tunnelLowerLimit{dNaN};                       // 108 - TunnelLowerLimit
    char tradingPhase[MAX_STRING_SIZE]="";                       // 109 - TradingPhase(BMF FIX)
    int32_t tickSize{INVALID_INT32};                            // 110 - TickSize
    int32_t minTradeVolume{INVALID_INT32};                      // 111 - Volume mínimo de negociação do instrumento
    double minPriceIncrement{dNaN};                      // 112 - Intervalo mínimo para incrementos de preço
    int32_t minOfferSize{INVALID_INT32};                        // 113 - Quantidade mínima para o instrumento em uma oferta
    int32_t maxOfferSize{INVALID_INT32};                        // 114 - Quantidade máxima para o instrumento em uma oferta
    int32_t uniqueInstrumentId;                     // 115 - Número único de identificação do instrumento
    char currency[MAX_STRING_SIZE]="";                           // 116 - Moeda utilizada no preço
    char securityType[MAX_STRING_SIZE]="";                       // 117 - SecurityType
    char securitySubType[MAX_STRING_SIZE]="";                    // 118 - Código de negociação do instrumento
    int32_t associatedProduct{INVALID_INT32};                   // 119 - Produto associado ao instrumento
    char expiryMonthYear[MAX_STRING_SIZE]="";                    // 120 - Mês e ano de vencimento (YYYYMM)
    double optionStrikePrice{dNaN};                      // 121 - Preço de exercício da opção
    char optionCurrency[MAX_STRING_SIZE]="";                     // 122 - Moeda do preço de exercício da opção
    double contractMultiplier{dNaN};                     // 123 - Multiplicador do contrato
    int32_t priceType{INVALID_INT32};                           // 124 - Código que representa o tipo de preço do instrumento
    char endOfTradeTime[MAX_STRING_SIZE]="";                     // 125 - Horário em que um instrumento não é mais passível de negociação (YYYYMMDDHHMMSS)
    char assetGroup[MAX_STRING_SIZE]="";                         // 126 - Indica o grupo ao qual o ativo pertence
    double currentAdjustmentRate{dNaN};                  // 127 - Ajuste atual em taxa
    double previousAdjustmentRate{dNaN};                 // 128 - Ajuste anterior em taxa
    char currentAdjustmentDate[MAX_STRING_SIZE]="";              // 129 - Data do Ajuste atual em taxa (YYYYMMDD)
    int32_t withdrawalsToExpiry{INVALID_INT32};                 // 130 - Número de saques até data de vencimento
    double hourlyVolumeVariation{dNaN};                  // 134 - Variação do volume da hora com base na média do volume do horário nos últimos 20 dias
    double cumulativeVolumeVariation{dNaN};              // 135 - Variação do volume até a hora com base na média do volume até o horário nos últimos 20 dias
    int32_t sectorCode{INVALID_INT32};                          // 136 - Código do setor do Ativo
    int32_t subsectorCode{INVALID_INT32};                       // 137 - Código do subsetor do Ativo
    int32_t segmentCode{INVALID_INT32};                         // 138 - Código do segmento do Ativo
    char adjustmentType[MAX_STRING_SIZE]="";                     // 139 - Tipo do ajuste atual em taxa
    double referencePrice{dNaN};                         // 140 - Preço de referência
    char referenceDate[MAX_STRING_SIZE]="";                      // 141 - Data do preço de referência
    char lastModTimeMillis[MAX_STRING_SIZE]="";                  // 142 - Horário da última modificação com milissegundos (HHMMSSmmm)
    char lastTradeTimeMillis[MAX_STRING_SIZE]="";                // 143 - Horário do último negócio com milissegundos (HHMMSSmmm)
    char bestBidTimeMillis[MAX_STRING_SIZE]="";                  // 144 - Horário da última modificação com milissegundos (HHMMSSmmm)
    char bestAskTimeMillis[MAX_STRING_SIZE]="";                  // 145 - Horário do último negócio com milissegundos (HHMMSSmmm)
    double adjustedPriceVariation{dNaN};                         // 146 - Variação utilizando o ajuste do dia anterior
    double diffAdjustedPrice{dNaN};                             // 147 - Diff (Preço Atual - Ajuste do dia anterior)
    double tunnelUpperAuctionLimit{dNaN};                       // 148 - Tunnel Upper Auction Limit (Auction Band)
    double tunnelLowerAuctionLimit{dNaN};                       // 149 - Tunnel Lower Auction Limit (Auction Band)
    double tunnelUpperRejectionLimit{dNaN};                     // 150 - Tunnel Upper Rejection Limit (Rejection Band)
    double tunnelLowerRejectionLimit{dNaN};                     // 151 - Tunnel Lower Rejection Limit (Rejection Band)
    double tunnelUpperStaticLimit{dNaN};                        // 152 - Tunnel Upper Static Limit (Static Limit)
    double tunnelLowerStaticLimit{dNaN};                        // 153 - Tunnel Lower Static Limit (Static Limit)

    // Campos exclusivos do Tesouro Direto
    double unitPrice{dNaN};              // 200 - Preço unitário
    double rateValue{dNaN};              // 201 - Valor da taxa (Rentabilidade)
    double minApplicationValue{dNaN};    // 202 - Valor mínimo de aplicação
    int32_t treasuryMarket{INVALID_INT32};      // 203 - Mercado
    char titleCode[MAX_STRING_SIZE]="";          // 204 - Código do título
    int32_t typeCode{INVALID_INT32};            // 205 - Código do tipo
    char typeName[MAX_STRING_SIZE]="";           // 206 - Nome do tipo
    char selicCode[MAX_STRING_SIZE]="";          // 207 - Selic
    char issueDate[MAX_STRING_SIZE]="";          // 208 - Data de emissão (YYYYMMDD)
    int32_t transactionId{INVALID_INT32};       // 209 - Negócio
    double baseValue{dNaN};              // 210 - Valor base
    double buyRate{dNaN};                // 211 - Valor da taxa de compra
    double sellRate{dNaN};               // 212 - Valor da taxa de venda
    int32_t indexerCode{INVALID_INT32};         // 213 - Código indexador
    char indexerName[MAX_STRING_SIZE]="";        // 214 - Nome indexador
    char titleName[MAX_STRING_SIZE]="";          // 215 - Nome do título

    void parseSQTMessage(const char* message, size_t length)
    {
      // Remove o prefixo "T:" e o sufixo "!"
      const char* content = message + 2;
      size_t contentLength = length - 3;

      // Encontrar o símbolo e a hora (SYMBOL e HORA)
      const char* firstColon = std::strchr(content, ':');
      if (firstColon == nullptr || firstColon - content >= contentLength) {
        return;
      }

      size_t symbolLength = firstColon - content;
      std::strncpy(symbol, content, symbolLength);
      symbol[symbolLength] = '\0';

      const char* secondColon = std::strchr(firstColon + 1, ':');
      if (secondColon == nullptr || secondColon - content >= contentLength) {
        return;
      }

      size_t timeLength = secondColon - firstColon - 1;
      std::strncpy(time, firstColon + 1, timeLength);
      time[timeLength] = '\0';

      // Começar a ler os campos ID:VALOR
      const char* currentPos = secondColon + 1;
      while (currentPos < content + contentLength)
      {
        const char* nextColon = std::strchr(currentPos, ':');
        if (nextColon == nullptr) break;

        int fieldId = std::atoi(currentPos);

        const char* valueEnd = std::strchr(nextColon + 1, ':');
        if (valueEnd == nullptr) valueEnd = content + contentLength;

        size_t valueLength = valueEnd - (nextColon + 1);

        // Atualizar o modelo com base no ID e no valor
        updateModel(fieldId, nextColon + 1, valueLength);

        currentPos = valueEnd + 1;
      }
    }

    void updateModel(int fieldId, const char* value, size_t size)
    {

      // Verifica se o fieldId é válido e dentro do intervalo esperado
      if (fieldId < 0 || fieldId >= static_cast<int>(INDEXES_MAP_SIZE))
      {
        std::stringstream stm;
        stm << "SQT ID not supported: " << fieldId << "\n";
        LOG_ERROR(stm.str());
        return;
      }

      auto id = static_cast<SQTFieldID>(fieldId);
      void* varPtr = _idToVarMap[fieldId];  // Obtém o ponteiro a partir do vetor

      // Verifica se o ponteiro é válido
      if (varPtr == nullptr)
      {
        std::stringstream stm;
        stm << "SQT ID not supported: " << fieldId << "\n";
        LOG_ERROR(stm.str());
        return;
      }

      DataType type = _idToTypeMap.at(id);

      if (type == INVALID)
      {
        std::stringstream stm;
        stm << "SQT ID not supported: " << fieldId << "\n";
        LOG_ERROR(stm.str());
        return;
      }

      switch (type)
      {
        case DataType::STRING:
        {
          // Garante que o valor será terminado com '\0'
          char* destination = reinterpret_cast<char*>(_idToVarMap[id]);
          std::strncpy(destination, value, size);
          break;
        }
        case DataType::INT:
          *reinterpret_cast<int32_t*>(_idToVarMap[id]) = std::atoi(value);
          break;
        case DataType::FLOAT:
          *reinterpret_cast<double*>(_idToVarMap[id]) = std::atof(value);
          break;
        case DataType::CHAR:
          *reinterpret_cast<char*>(_idToVarMap[id]) = value[0];
          break;
        default:
          assert(false); // Unreachable
          break;
      }
    }

  private:
    static constexpr size_t INDEXES_MAP_SIZE = 216;
    std::array<DataType, INDEXES_MAP_SIZE> _idToTypeMap =
        {
        DataType::STRING,  // 0 - LAST_MOD_TIME
        DataType::STRING,  // 1 - LAST_MOD_DATE
        DataType::FLOAT,   // 2 - LAST_TRADE_PRICE
        DataType::FLOAT,   // 3 - BEST_BID_PRICE
        DataType::FLOAT,   // 4 - BEST_ASK_PRICE
        DataType::STRING,  // 5 - LAST_TRADE_TIME
        DataType::INT,     // 6 - CURRENT_TRADE_SIZE
        DataType::INT,     // 7 - LAST_TRADE_SIZE
        DataType::INT,     // 8 - TOTAL_TRADES
        DataType::INT,     // 9 - TOTAL_VOLUME
        DataType::FLOAT,   // 10 - TOTAL_FINANCIAL_VOLUME
        DataType::FLOAT,   // 11 - HIGHEST_PRICE_OF_DAY
        DataType::FLOAT,   // 12 - LOWEST_PRICE_OF_DAY
        DataType::FLOAT,   // 13 - PREVIOUS_DAY_CLOSE_PRICE
        DataType::FLOAT,   // 14 - OPENING_PRICE
        DataType::STRING,  // 15 - BEST_BID_TIME
        DataType::STRING,  // 16 - BEST_ASK_TIME
        DataType::FLOAT,   // 17 - BEST_BID_VOLUME
        DataType::FLOAT,   // 18 - BEST_ASK_VOLUME
        DataType::INT,     // 19 - BEST_BID_SIZE
        DataType::INT,     // 20 - BEST_ASK_SIZE
        DataType::FLOAT,   // 21 - VARIATION
        DataType::INVALID, // 22 - not used
        DataType::INVALID, // 23 - not used
        DataType::INVALID, // 24 - not used
        DataType::INVALID, // 25 - not used
        DataType::INVALID, // 26 - not used
        DataType::INVALID, // 27 - not used
        DataType::INVALID, // 28 - not used
        DataType::INVALID, // 29 - not used
        DataType::INVALID, // 30 - not used
        DataType::INVALID, // 31 - not used
        DataType::INVALID, // 32 - not used
        DataType::INVALID, // 33 - not used
        DataType::INVALID, // 34 - not used
        DataType::INVALID, // 35 - not used
        DataType::FLOAT,   // 36 - LAST_WEEK_CLOSE_PRICE
        DataType::FLOAT,   // 37 - LAST_MONTH_CLOSE_PRICE
        DataType::FLOAT,   // 38 - LAST_YEAR_CLOSE_PRICE
        DataType::FLOAT,   // 39 - PREVIOUS_DAY_OPENING_PRICE
        DataType::FLOAT,   // 40 - PREVIOUS_DAY_HIGHEST_PRICE
        DataType::FLOAT,   // 41 - PREVIOUS_DAY_LOWEST_PRICE
        DataType::FLOAT,   // 42 - AVERAGE_PRICE
        DataType::FLOAT,   // 43 - VH_DAILY
        DataType::INT,     // 44 - MARKET_CODE
        DataType::INT,     // 45 - ASSET_TYPE
        DataType::INT,     // 46 - STANDARD_LOT
        DataType::STRING,  // 47 - ASSET_DESCRIPTION
        DataType::STRING,  // 48 - CLASSIFICATION_NAME
        DataType::INT,     // 49 - QUOTE_FORM
        DataType::STRING,  // 50 - INTRADAY_DATE
        DataType::STRING,  // 51 - LAST_TRADE_DATE
        DataType::STRING,  // 52 - SHORT_ASSET_DESCRIPTION
        DataType::STRING,  // 53 - CANCELED_TRADE_ID
        DataType::STRING,  // 54 - LAST_TRADE_DATE_SIMPLE
        DataType::INVALID, // 55 - not used
        DataType::CHAR,    // 56 - OPENING_UNFULFILLED_SIDE
        DataType::INT,     // 57 - OPENING_UNFULFILLED_SIZE
        DataType::STRING,  // 58 - SCHEDULED_OPENING_TIME
        DataType::STRING,  // 59 - RESCHEDULED_OPENING_TIME
        DataType::INT,     // 60 - BEST_BID_BROKER
        DataType::INT,     // 61 - BEST_ASK_BROKER
        DataType::INT,     // 62 - LAST_BUY_BROKER
        DataType::INT,     // 63 - LAST_SELL_BROKER
        DataType::STRING,  // 64 - OPTION_EXPIRATION_DATE
        DataType::INT,     // 65 - EXPIRED
        DataType::STRING,  // 66 - TOTAL_PAPERS
        DataType::INT,     // 67 - INSTRUMENT_STATUS
        DataType::INVALID, // 68 - not used
        DataType::INVALID, // 69 - not used
        DataType::INVALID, // 70 - not used
        DataType::INVALID, // 71 - not used
        DataType::CHAR,    // 72 - OPTION_TYPE
        DataType::INVALID, // 73 - not used
        DataType::CHAR,    // 74 - OPTION_DIRECTION
        DataType::INVALID, // 75 - not used
        DataType::INVALID, // 76 - not used
        DataType::INVALID, // 77 - not used
        DataType::INVALID, // 78 - not used
        DataType::INVALID, // 79 - not used
        DataType::INVALID, // 80 - not used
        DataType::STRING,  // 81 - PARENT_SYMBOL
        DataType::FLOAT,   // 82 - THEORETICAL_OPENING_PRICE
        DataType::INT,     // 83 - THEORETICAL_SIZE
        DataType::INT,     // 84 - ASSET_STATUS
        DataType::FLOAT,   // 85 - STRIKE_PRICE
        DataType::FLOAT,   // 86 - DIFF_PRICE
        DataType::STRING,  // 87 - PREVIOUS_DAY
        DataType::STRING,  // 88 - ASSET_GROUP_PHASE
        DataType::FLOAT,   // 89 - PREVIOUS_DAY_AVERAGE_PRICE
        DataType::FLOAT,   // 90 - MARGIN_RANGE
        DataType::INVALID, // 91 - not used
        DataType::INVALID, // 92 - not used
        DataType::INVALID, // 93 - not used
        DataType::FLOAT,   // 94 - AVERAGE_VOLUME_20_DAYS
        DataType::FLOAT,   // 95 - MARKET_CAPITALIZATION
        DataType::STRING,  // 96 - MARKET_TYPE
        DataType::FLOAT,   // 97 - WEEK_CLOSE_VARIATION
        DataType::FLOAT,   // 98 - MONTH_CLOSE_VARIATION
        DataType::FLOAT,   // 99 - YEAR_CLOSE_VARIATION
        DataType::INT,     // 100 - OPEN_CONTRACTS
        DataType::INT,     // 101 - BUSINESS_DAYS_TO_EXPIRY
        DataType::INT,     // 102 - DAYS_TO_EXPIRY
        DataType::FLOAT,   // 103 - ADJUSTMENT_PRICE
        DataType::FLOAT,   // 104 - PREVIOUS_DAY_ADJUSTMENT_PRICE
        DataType::STRING,  // 105 - SECURITY_ID
        DataType::STRING,  // 106 - TICK_DIRECTION
        DataType::FLOAT,   // 107 - TUNNEL_UPPER_LIMIT
        DataType::FLOAT,   // 108 - TUNNEL_LOWER_LIMIT
        DataType::STRING,  // 109 - TRADING_PHASE
        DataType::INT,     // 110 - TICK_SIZE
        DataType::INT,     // 111 - MIN_TRADE_VOLUME
        DataType::FLOAT,   // 112 - MIN_PRICE_INCREMENT
        DataType::INT,     // 113 - MIN_OFFER_SIZE
        DataType::INT,     // 114 - MAX_OFFER_SIZE
        DataType::INT,     // 115 - UNIQUE_INSTRUMENT_ID
        DataType::STRING,  // 116 - CURRENCY
        DataType::STRING,  // 117 - SECURITY_TYPE
        DataType::STRING,  // 118 - SECURITY_SUB_TYPE
        DataType::INT,     // 119 - ASSOCIATED_PRODUCT
        DataType::STRING,  // 120 - EXPIRY_MONTH_YEAR
        DataType::FLOAT,   // 121 - OPTION_STRIKE_PRICE
        DataType::STRING,  // 122 - OPTION_CURRENCY
        DataType::FLOAT,   // 123 - CONTRACT_MULTIPLIER
        DataType::INT,     // 124 - PRICE_TYPE
        DataType::STRING,  // 125 - END_OF_TRADE_TIME
        DataType::STRING,  // 126 - ASSET_GROUP
        DataType::FLOAT,   // 127 - CURRENT_ADJUSTMENT_RATE
        DataType::FLOAT,   // 128 - PREVIOUS_ADJUSTMENT_RATE
        DataType::STRING,  // 129 - CURRENT_ADJUSTMENT_DATE
        DataType::INT,     // 130 - WITHDRAWALS_TO_EXPIRY
        DataType::INVALID, // 131 - not used
        DataType::INVALID, // 132 - not used
        DataType::INVALID, // 133 - not used
        DataType::FLOAT,   // 134 - HOURLY_VOLUME_VARIATION
        DataType::FLOAT,   // 135 - CUMULATIVE_VOLUME_VARIATION
        DataType::INT,     // 136 - SECTOR_CODE
        DataType::INT,     // 137 - SUBSECTOR_CODE
        DataType::INT,     // 138 - SEGMENT_CODE
        DataType::STRING,  // 139 - ADJUSTMENT_TYPE
        DataType::FLOAT,   // 140 - REFERENCE_PRICE
        DataType::STRING,  // 141 - REFERENCE_DATE
        DataType::STRING,  // 142 - LAST_MOD_TIME_MILLIS
        DataType::STRING,  // 143 - LAST_TRADE_TIME_MILLIS
        DataType::STRING,  // 144 - BEST_BID_TIME_MILLIS
        DataType::STRING,  // 145 - BEST_ASK_TIME_MILLIS
        DataType::FLOAT,   // 146 - ADJUSTED_PRICE_VARIATION
        DataType::FLOAT,   // 147 - DIFF_ADJUSTED_PRICE
        DataType::FLOAT,   // 148 - TUNNEL_UPPER_AUCTION_LIMIT
        DataType::FLOAT,   // 149 - TUNNEL_LOWER_AUCTION_LIMIT
        DataType::FLOAT,   // 150 - TUNNEL_UPPER_REJECTION_LIMIT
        DataType::FLOAT,   // 151 - TUNNEL_LOWER_REJECTION_LIMIT
        DataType::FLOAT,   // 152 - TUNNEL_UPPER_STATIC_LIMIT
        DataType::FLOAT,   // 153 - TUNNEL_LOWER_STATIC_LIMIT
        DataType::INVALID, // 154 - not used
        DataType::INVALID, // 155 - not used
        DataType::INVALID, // 156 - not used
        DataType::INVALID, // 157 - not used
        DataType::INVALID, // 158 - not used
        DataType::INVALID, // 159 - not used
        DataType::INVALID, // 160 - not used
        DataType::INVALID, // 161 - not used
        DataType::INVALID, // 162 - not used
        DataType::INVALID, // 163 - not used
        DataType::INVALID, // 164 - not used
        DataType::INVALID, // 165 - not used
        DataType::INVALID, // 166 - not used
        DataType::INVALID, // 167 - not used
        DataType::INVALID, // 168 - not used
        DataType::INVALID, // 169 - not used
        DataType::INVALID, // 170 - not used
        DataType::INVALID, // 171 - not used
        DataType::INVALID, // 172 - not used
        DataType::INVALID, // 173 - not used
        DataType::INVALID, // 174 - not used
        DataType::INVALID, // 175 - not used
        DataType::INVALID, // 176 - not used
        DataType::INVALID, // 177 - not used
        DataType::INVALID, // 178 - not used
        DataType::INVALID, // 179 - not used
        DataType::INVALID, // 180 - not used
        DataType::INVALID, // 181 - not used
        DataType::INVALID, // 182 - not used
        DataType::INVALID, // 183 - not used
        DataType::INVALID, // 184 - not used
        DataType::INVALID, // 185 - not used
        DataType::INVALID, // 186 - not used
        DataType::INVALID, // 187 - not used
        DataType::INVALID, // 188 - not used
        DataType::INVALID, // 189 - not used
        DataType::INVALID, // 190 - not used
        DataType::INVALID, // 191 - not used
        DataType::INVALID, // 192 - not used
        DataType::INVALID, // 193 - not used
        DataType::INVALID, // 194 - not used
        DataType::INVALID, // 195 - not used
        DataType::INVALID, // 196 - not used
        DataType::INVALID, // 197 - not used
        DataType::INVALID, // 198 - not used
        DataType::INVALID, // 199 - not used
        DataType::FLOAT,   // 200 - UNIT_PRICE
        DataType::FLOAT,   // 201 - RATE_VALUE
        DataType::FLOAT,   // 202 - MIN_APPLICATION_VALUE
        DataType::INT,     // 203 - TREASURY_MARKET
        DataType::STRING,  // 204 - TITLE_CODE
        DataType::INT,     // 205 - TYPE_CODE
        DataType::STRING,  // 206 - TYPE_NAME
        DataType::STRING,  // 207 - SELIC_CODE
        DataType::STRING,  // 208 - ISSUE_DATE
        DataType::INT,     // 209 - TRANSACTION_ID
        DataType::FLOAT,   // 210 - BASE_VALUE
        DataType::FLOAT,   // 211 - BUY_RATE
        DataType::FLOAT,   // 212 - SELL_RATE
        DataType::INT,     // 213 - INDEXER_CODE
        DataType::STRING,  // 214 - INDEXER_NAME
        DataType::STRING   // 215 - TITLE_NAME
    };


    std::array<void*, INDEXES_MAP_SIZE> _idToVarMap =
    {
        &lastModTime,          // 0 - LAST_MOD_TIME
        &lastModDate,          // 1 - LAST_MOD_DATE
        &lastTradePrice,       // 2 - LAST_TRADE_PRICE
        &bestBidPrice,         // 3 - BEST_BID_PRICE
        &bestAskPrice,         // 4 - BEST_ASK_PRICE
        &lastTradeTime,        // 5 - LAST_TRADE_TIME
        &currentTradeSize,     // 6 - CURRENT_TRADE_SIZE
        &lastTradeSize,        // 7 - LAST_TRADE_SIZE
        &totalTrades,          // 8 - TOTAL_TRADES
        &totalVolume,          // 9 - TOTAL_VOLUME
        &totalFinancialVolume, // 10 - TOTAL_FINANCIAL_VOLUME
        &highestPriceOfDay,    // 11 - HIGHEST_PRICE_OF_DAY
        &lowestPriceOfDay,     // 12 - LOWEST_PRICE_OF_DAY
        &previousDayClosePrice,// 13 - PREVIOUS_DAY_CLOSE_PRICE
        &openingPrice,         // 14 - OPENING_PRICE
        &bestBidTime,          // 15 - BEST_BID_TIME
        &bestAskTime,          // 16 - BEST_ASK_TIME
        &bestBidVolume,        // 17 - BEST_BID_VOLUME
        &bestAskVolume,        // 18 - BEST_ASK_VOLUME
        &bestBidSize,          // 19 - BEST_BID_SIZE
        &bestAskSize,          // 20 - BEST_ASK_SIZE
        &variation,            // 21 - VARIATION
        nullptr,               // 22 - not used
        nullptr,               // 23 - not used
        nullptr,               // 24 - not used
        nullptr,               // 25 - not used
        nullptr,               // 26 - not used
        nullptr,               // 27 - not used
        nullptr,               // 28 - not used
        nullptr,               // 29 - not used
        nullptr,               // 30 - not used
        nullptr,               // 31 - not used
        nullptr,               // 32 - not used
        nullptr,               // 33 - not used
        nullptr,               // 34 - not used
        nullptr,               // 35 - not used
        &lastWeekClosePrice,   // 36 - LAST_WEEK_CLOSE_PRICE
        &lastMonthClosePrice,  // 37 - LAST_MONTH_CLOSE_PRICE
        &lastYearClosePrice,   // 38 - LAST_YEAR_CLOSE_PRICE
        &previousDayOpeningPrice,// 39 - PREVIOUS_DAY_OPENING_PRICE
        &previousDayHighestPrice,// 40 - PREVIOUS_DAY_HIGHEST_PRICE
        &previousDayLowestPrice,// 41 - PREVIOUS_DAY_LOWEST_PRICE
        &averagePrice,         // 42 - AVERAGE_PRICE
        &vhDaily,              // 43 - VH_DAILY
        &marketCode,           // 44 - MARKET_CODE
        &assetType,            // 45 - ASSET_TYPE
        &standardLot,          // 46 - STANDARD_LOT
        &assetDescription,     // 47 - ASSET_DESCRIPTION
        &classificationName,   // 48 - CLASSIFICATION_NAME
        &quoteForm,            // 49 - QUOTE_FORM
        &intradayDate,         // 50 - INTRADAY_DATE
        &lastTradeDate,        // 51 - LAST_TRADE_DATE
        &shortAssetDescription,// 52 - SHORT_ASSET_DESCRIPTION
        &canceledTradeId,      // 53 - CANCELED_TRADE_ID
        &lastTradeDateSimple,  // 54 - LAST_TRADE_DATE_SIMPLE
        nullptr,               // 55 - not used
        &openingUnfulfilledSide,// 56 - OPENING_UNFULFILLED_SIDE
        &openingUnfulfilledSize,// 57 - OPENING_UNFULFILLED_SIZE
        &scheduledOpeningTime, // 58 - SCHEDULED_OPENING_TIME
        &rescheduledOpeningTime,// 59 - RESCHEDULED_OPENING_TIME
        &bestBidBroker,        // 60 - BEST_BID_BROKER
        &bestAskBroker,        // 61 - BEST_ASK_BROKER
        &lastBuyBroker,        // 62 - LAST_BUY_BROKER
        &lastSellBroker,       // 63 - LAST_SELL_BROKER
        &optionExpirationDate, // 64 - OPTION_EXPIRATION_DATE
        &expired,              // 65 - EXPIRED
        &totalPapers,          // 66 - TOTAL_PAPERS
        &instrumentStatus,     // 67 - INSTRUMENT_STATUS
        nullptr,               // 68 - not used
        nullptr,               // 69 - not used
        nullptr,               // 70 - not used
        nullptr,               // 71 - not used
        &optionType,           // 72 - OPTION_TYPE
        nullptr,               // 73 - not used
        &optionDirection,      // 74 - OPTION_DIRECTION
        nullptr,               // 75 - not used
        nullptr,               // 76 - not used
        nullptr,               // 77 - not used
        nullptr,               // 78 - not used
        nullptr,               // 79 - not used
        nullptr,               // 80 - not used
        &parentSymbol,         // 81 - PARENT_SYMBOL
        &theoreticalOpeningPrice,// 82 - THEORETICAL_OPENING_PRICE
        &theoreticalSize,      // 83 - THEORETICAL_SIZE
        &assetStatus,          // 84 - ASSET_STATUS
        &strikePrice,          // 85 - STRIKE_PRICE
        &diffPrice,            // 86 - DIFF_PRICE
        &previousDay,          // 87 - PREVIOUS_DAY
        &assetGroupPhase,      // 88 - ASSET_GROUP_PHASE
        &previousDayAveragePrice,// 89 - PREVIOUS_DAY_AVERAGE_PRICE
        &marginRange,          // 90 - MARGIN_RANGE
        nullptr,               // 91 - not used
        nullptr,               // 92 - not used
        nullptr,               // 93 - not used
        &averageVolume20Days,  // 94 - AVERAGE_VOLUME_20_DAYS
        &marketCapitalization, // 95 - MARKET_CAPITALIZATION
        &marketType,           // 96 - MARKET_TYPE
        &weekCloseVariation,   // 97 - WEEK_CLOSE_VARIATION
        &monthCloseVariation,  // 98 - MONTH_CLOSE_VARIATION
        &yearCloseVariation,   // 99 - YEAR_CLOSE_VARIATION
        &openContracts,        // 100 - OPEN_CONTRACTS
        &businessDaysToExpiry, // 101 - BUSINESS_DAYS_TO_EXPIRY
        &daysToExpiry,         // 102 - DAYS_TO_EXPIRY
        &adjustmentPrice,      // 103 - ADJUSTMENT_PRICE
        &previousDayAdjustmentPrice,// 104 - PREVIOUS_DAY_ADJUSTMENT_PRICE
        &securityId,           // 105 - SECURITY_ID
        &tickDirection,        // 106 - TICK_DIRECTION
        &tunnelUpperLimit,     // 107 - TUNNEL_UPPER_LIMIT
        &tunnelLowerLimit,     // 108 - TUNNEL_LOWER_LIMIT
        &tradingPhase,         // 109 - TRADING_PHASE
        &tickSize,             // 110 - TICK_SIZE
        &minTradeVolume,       // 111 - MIN_TRADE_VOLUME
        &minPriceIncrement,    // 112 - MIN_PRICE_INCREMENT
        &minOfferSize,         // 113 - MIN_OFFER_SIZE
        &maxOfferSize,         // 114 - MAX_OFFER_SIZE
        &uniqueInstrumentId,   // 115 - UNIQUE_INSTRUMENT_ID
        &currency,             // 116 - CURRENCY
        &securityType,         // 117 - SECURITY_TYPE
        &securitySubType,      // 118 - SECURITY_SUB_TYPE
        &associatedProduct,    // 119 - ASSOCIATED_PRODUCT
        &expiryMonthYear,      // 120 - EXPIRY_MONTH_YEAR
        &optionStrikePrice,    // 121 - OPTION_STRIKE_PRICE
        &optionCurrency,       // 122 - OPTION_CURRENCY
        &contractMultiplier,   // 123 - CONTRACT_MULTIPLIER
        &priceType,            // 124 - PRICE_TYPE
        &endOfTradeTime,       // 125 - END_OF_TRADE_TIME
        &assetGroup,           // 126 - ASSET_GROUP
        &currentAdjustmentRate,// 127 - CURRENT_ADJUSTMENT_RATE
        &previousAdjustmentRate,// 128 - PREVIOUS_ADJUSTMENT_RATE
        &currentAdjustmentDate,// 129 - CURRENT_ADJUSTMENT_DATE
        &withdrawalsToExpiry,  // 130 - WITHDRAWALS_TO_EXPIRY
        nullptr,               // 131 - not used
        nullptr,               // 132 - not used
        nullptr,               // 133 - not used
        &hourlyVolumeVariation,// 134 - HOURLY_VOLUME_VARIATION
        &cumulativeVolumeVariation,// 135 - CUMULATIVE_VOLUME_VARIATION
        &sectorCode,           // 136 - SECTOR_CODE
        &subsectorCode,        // 137 - SUBSECTOR_CODE
        &segmentCode,          // 138 - SEGMENT_CODE
        &adjustmentType,       // 139 - ADJUSTMENT_TYPE
        &referencePrice,       // 140 - REFERENCE_PRICE
        &referenceDate,        // 141 - REFERENCE_DATE
        &lastModTimeMillis,    // 142 - LAST_MOD_TIME_MILLIS
        &lastTradeTimeMillis,  // 143 - LAST_TRADE_TIME_MILLIS
        &bestBidTimeMillis,    // 144 - BEST_BID_TIME_MILLIS
        &bestAskTimeMillis,    // 145 - BEST_ASK_TIME_MILLIS
        &adjustedPriceVariation,// 146 - ADJUSTED_PRICE_VARIATION
        &diffAdjustedPrice,    // 147 - DIFF_ADJUSTED_PRICE
        &tunnelUpperAuctionLimit,// 148 - TUNNEL_UPPER_AUCTION_LIMIT
        &tunnelLowerAuctionLimit,// 149 - TUNNEL_LOWER_AUCTION_LIMIT
        &tunnelUpperRejectionLimit,// 150 - TUNNEL_UPPER_REJECTION_LIMIT
        &tunnelLowerRejectionLimit,// 151 - TUNNEL_LOWER_REJECTION_LIMIT
        &tunnelUpperStaticLimit,// 152 - TUNNEL_UPPER_STATIC_LIMIT
        &tunnelLowerStaticLimit,// 153 - TUNNEL_LOWER_STATIC_LIMIT
        nullptr,               // 154 - not used
        nullptr,               // 155 - not used
        nullptr,               // 156 - not used
        nullptr,               // 157 - not used
        nullptr,               // 158 - not used
        nullptr,               // 159 - not used
        nullptr,               // 160 - not used
        nullptr,               // 161 - not used
        nullptr,               // 162 - not used
        nullptr,               // 163 - not used
        nullptr,               // 164 - not used
        nullptr,               // 165 - not used
        nullptr,               // 166 - not used
        nullptr,               // 167 - not used
        nullptr,               // 168 - not used
        nullptr,               // 169 - not used
        nullptr,               // 170 - not used
        nullptr,               // 171 - not used
        nullptr,               // 172 - not used
        nullptr,               // 173 - not used
        nullptr,               // 174 - not used
        nullptr,               // 175 - not used
        nullptr,               // 176 - not used
        nullptr,               // 177 - not used
        nullptr,               // 178 - not used
        nullptr,               // 179 - not used
        nullptr,               // 180 - not used
        nullptr,               // 181 - not used
        nullptr,               // 182 - not used
        nullptr,               // 183 - not used
        nullptr,               // 184 - not used
        nullptr,               // 185 - not used
        nullptr,               // 186 - not used
        nullptr,               // 187 - not used
        nullptr,               // 188 - not used
        nullptr,               // 189 - not used
        nullptr,               // 190 - not used
        nullptr,               // 191 - not used
        nullptr,               // 192 - not used
        nullptr,               // 193 - not used
        nullptr,               // 194 - not used
        nullptr,               // 195 - not used
        nullptr,               // 196 - not used
        nullptr,               // 197 - not used
        nullptr,               // 198 - not used
        nullptr,               // 199 - not used
        &unitPrice,            // 200 - UNIT_PRICE
        &rateValue,            // 201 - RATE_VALUE
        &minApplicationValue,  // 202 - MIN_APPLICATION_VALUE
        &treasuryMarket,       // 203 - TREASURY_MARKET
        &titleCode,            // 204 - TITLE_CODE
        &typeCode,             // 205 - TYPE_CODE
        &typeName,             // 206 - TYPE_NAME
        &selicCode,            // 207 - SELIC_CODE
        &issueDate,            // 208 - ISSUE_DATE
        &transactionId,        // 209 - TRANSACTION_ID
        &baseValue,            // 210 - BASE_VALUE
        &buyRate,              // 211 - BUY_RATE
        &sellRate,             // 212 - SELL_RATE
        &indexerCode,          // 213 - INDEXER_CODE
        &indexerName,          // 214 - INDEXER_NAME
        &titleName             // 215 - TITLE_NAME
    };
  };

}

#endif //CEDRO_MD_SQTMODEL_H
