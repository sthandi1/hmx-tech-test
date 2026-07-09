#ifndef PRICINGCONFIGLOADER_H
#define PRICINGCONFIGLOADER_H

#include "PricingEngineConfig.h"
#include <string>

class PricingConfigLoader {
    std::string configFile_;

public:
    [[nodiscard]] std::string getConfigFile() const;

    void setConfigFile(const std::string &file);

    PricingEngineConfig loadConfig() const;
};

#endif // PRICINGCONFIGLOADER_H
