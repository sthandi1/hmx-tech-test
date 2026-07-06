#ifndef FXTRADELOADER_H
#define FXTRADELOADER_H

#include "ITradeLoader.h"
#include "../Models/FxTrade.h"
#include <string>
#include <vector>

class FxTradeLoader : public ITradeLoader {
    static std::unique_ptr<FxTrade> createTradeFromLine(const std::string &line);

    std::string dataFile_;
    const std::string separator = "\xC2\xAC";

public:
    // NOTE: These methods are only here to allow the solution to compile prior to the test being completed.
    std::vector<ITrade *> loadTrades() override;

    [[nodiscard]] std::string getDataFile() const override;

    void setDataFile(const std::string &file) override;
};

#endif // FXTRADELOADER_H
