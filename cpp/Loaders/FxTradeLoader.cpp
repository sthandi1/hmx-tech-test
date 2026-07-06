#include "FxTradeLoader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>
#include "../Models/TradeList.h"

// NOTE: These methods are only here to allow the solution to compile prior to the test being completed.

FxTrade *FxTradeLoader::createTradeFromLine(const std::string &line) {
    // Find and separate string on logical not separator \xC2\xAC or ¬
    std::vector<std::string> items;
    std::size_t start = 0;
    std::size_t pos = 0;

    // Search for separator and use substrings to extract before separator
    while ((pos = line.find(separator, start)) != std::string::npos) {
        items.push_back(line.substr(start, pos - start));
        // Move start position to after separator
        start = pos + separator.length();
    }
    // Add final item
    items.push_back(line.substr(start));

    if (items.size() < 9) {
        throw std::runtime_error("Invalid line format");
    }
    auto *trade = new FxTrade(items[8], items[0]);

    // Trade date
    std::tm tm = {};
    std::istringstream dateStream(items[1]);
    dateStream >> std::get_time(&tm, "%Y-%m-%d");
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    trade->setTradeDate(timePoint);

    // Value date
    std::tm valueTm = {};
    std::istringstream valueDateStream(items[6]);
    valueDateStream >> std::get_time(&valueTm, "%Y-%m-%d");
    auto valueTimePoint = std::chrono::system_clock::from_time_t(std::mktime(&valueTm));
    trade->setValueDate(valueTimePoint);

    // Concatenate Ccy1 Ccy2
    trade->setInstrument(items[2] + items[3]);
    trade->setCounterparty(items[7]);
    trade->setNotional(std::stod(items[4]));
    trade->setRate(std::stod(items[5]));

    return trade;
}

void FxTradeLoader::loadTradesFromFile(const std::string& filename, TradeList &tradeList) {
    if (filename.empty()) {
        throw std::invalid_argument("Filename cannot be null");
    }

    std::ifstream stream(filename);
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    int lineCount = 0;
    std::string line;
    while (std::getline(stream, line)) {
        // Finish when END is found
        if (line.find("END") != std::string::npos) {
            break;
        }
        // Skip first two lines
        if (lineCount < 2) {
        } else {
            tradeList.add(createTradeFromLine(line));
        }
        lineCount++;
    }
}

std::vector<ITrade *> FxTradeLoader::loadTrades() {
    TradeList tradeList;
    loadTradesFromFile(dataFile_, tradeList);

    std::vector<ITrade *> result;
    for (auto i : tradeList) {
        result.push_back(i);
    }
    return result;
}

std::string FxTradeLoader::getDataFile() const {
    return dataFile_;
}

void FxTradeLoader::setDataFile(const std::string &file) {
    dataFile_ = file;
}
