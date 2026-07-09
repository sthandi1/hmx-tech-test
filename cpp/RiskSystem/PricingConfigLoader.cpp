#include "PricingConfigLoader.h"
#include <stdexcept>

#include "pugixml.hpp"

std::string PricingConfigLoader::getConfigFile() const {
    return configFile_;
}

void PricingConfigLoader::setConfigFile(const std::string& file) {
    configFile_ = file;
}

PricingEngineConfig PricingConfigLoader::loadConfig() const {
    // Set up object for storage
    PricingEngineConfig pricingEngineConfig;
    // Set up xml parser
    pugi::xml_document doc;
    if (pugi::xml_parse_result result = doc.load_file(configFile_.c_str()); !result) {
        throw std::runtime_error("Parsing xml failed");
    }
    // Set root of xml
    pugi::xml_node root = doc.child("PricingEngines");
    // Loop over all children engines
    for (const auto &engine : root.children("Engine")) {
        PricingEngineConfigItem pricingEngine;
        // Process xml
        std::string tradeType = engine.attribute("tradeType").value();
        std::string assembly = engine.attribute("assembly").value();
        std::string typeName = engine.attribute("pricingEngine").value();
        pricingEngine.setTradeType(tradeType);
        pricingEngine.setAssembly(assembly);
        pricingEngine.setTypeName(typeName);
        // Push pricing engine into vector
        pricingEngineConfig.push_back(pricingEngine);
    }
    return pricingEngineConfig;
}
