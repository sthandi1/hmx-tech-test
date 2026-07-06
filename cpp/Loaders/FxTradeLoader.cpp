#include "FxTradeLoader.h"

#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string>

// NOTE: These methods are only here to allow the solution to compile prior to the test being completed.

std::unique_ptr<FxTrade> FxTradeLoader::createTradeFromLine(const std::string& line) {

    std::vector<std::string> items;
    std::stringstream ss(line);
    std::string item;


    return {};
}

std::vector<ITrade*> FxTradeLoader::loadTrades() {
    throw std::runtime_error("Not implemented");
}

std::string FxTradeLoader::getDataFile() const {
    return dataFile_;
}

void FxTradeLoader::setDataFile(const std::string& file) {
    dataFile_ = file;
}
