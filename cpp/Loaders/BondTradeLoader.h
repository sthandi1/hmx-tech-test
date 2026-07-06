#ifndef BONDTRADELOADER_H
#define BONDTRADELOADER_H

#include "ITradeLoader.h"
#include "../Models/BondTrade.h"
#include "../Models/BondTradeList.h"
#include <string>
#include <vector>
#include <memory>

class BondTradeLoader : public ITradeLoader {
    static constexpr char separator = ',';
    std::string dataFile_;

    static std::unique_ptr<BondTrade> createTradeFromLine(const std::string &line);

    static void loadTradesFromFile(const std::string& filename, BondTradeList &tradeList);

public:
    std::vector<ITrade *> loadTrades() override;

    [[nodiscard]] std::string getDataFile() const override;

    void setDataFile(const std::string &file) override;
};

#endif // BONDTRADELOADER_H
