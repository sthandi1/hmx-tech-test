#include "FxTradeLoader.h"
#include <stdexcept>

// NOTE: These methods are only here to allow the solution to compile prior to the test being completed.

std::vector<ITrade*> FxTradeLoader::loadTrades() {
    throw std::runtime_error("Not implemented");
}

std::string FxTradeLoader::getDataFile() const {
    return dataFile_;
}

void FxTradeLoader::setDataFile(const std::string& file) {
    dataFile_ = file;
}
