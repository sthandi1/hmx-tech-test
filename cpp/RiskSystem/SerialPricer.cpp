#include "SerialPricer.h"
#include <stdexcept>

#include "Pricers/GovBondPricingEngine.h"
#include "Pricers/CorpBondPricingEngine.h"
#include "Pricers/FxPricingEngine.h"

SerialPricer::~SerialPricer() {

}

void SerialPricer::loadPricers() {
    PricingConfigLoader pricingConfigLoader;
    pricingConfigLoader.setConfigFile("./PricingConfig/PricingEngines.xml");
    PricingEngineConfig pricerConfig = pricingConfigLoader.loadConfig();
   for (const auto& configItem : pricerConfig) {
       if (configItem.getTradeType() == "GovBond")
           pricers_.emplace(configItem.getTradeType(), std::make_unique<GovBondPricingEngine>());
       else if (configItem.getTradeType() == "CorpBond")
           pricers_.emplace(configItem.getTradeType(),  std::make_unique<CorpBondPricingEngine>());
       else if (configItem.getTradeType() == "FxSpot" || configItem.getTradeType() == "FxFwd")
           pricers_.emplace(configItem.getTradeType(), std::make_unique<FxPricingEngine>());
       else
           throw std::runtime_error("Unable to set pricing engine");
    }
}

void SerialPricer::price(const std::vector<std::vector<ITrade*>>& tradeContainers, 
                         IScalarResultReceiver* resultReceiver) {
    loadPricers();
    
    for (const auto& tradeContainer : tradeContainers) {
        for (ITrade* trade : tradeContainer) {
            std::string tradeType = trade->getTradeType();
            if (pricers_.find(tradeType) == pricers_.end()) {
                resultReceiver->addError(trade->getTradeId(), "No Pricing Engines available for this trade type");
                continue;
            }
            
            IPricingEngine* pricer = pricers_[tradeType].get();
            pricer->price(trade, resultReceiver);
        }
    }
}
