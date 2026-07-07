#include "PricingConfigLoader.h"
#include <stdexcept>

std::string PricingConfigLoader::getConfigFile() const {
    return configFile_;
}

void PricingConfigLoader::setConfigFile(const std::string& file) {
    configFile_ = file;
}

PricingEngineConfig PricingConfigLoader::parseXml(const std::string &content) {
    return {};
}

PricingEngineConfig PricingConfigLoader::loadConfig() {
    PricingEngineConfig config;
    throw std::runtime_error("Not implemented");
}
