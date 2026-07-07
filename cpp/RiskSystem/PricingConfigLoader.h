#ifndef PRICINGCONFIGLOADER_H
#define PRICINGCONFIGLOADER_H

#include "PricingEngineConfig.h"
#include <string>

class PricingConfigLoader {
    std::string configFile_;

    PricingEngineConfig parseXml(const std::string &content);

public:
    [[nodiscard]] std::string getConfigFile() const;

    void setConfigFile(const std::string &file);

    PricingEngineConfig loadConfig();
};

#endif // PRICINGCONFIGLOADER_H
