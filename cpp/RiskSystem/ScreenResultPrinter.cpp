#include "ScreenResultPrinter.h"
#include <iostream>

void ScreenResultPrinter::printResults(ScalarResults &results) {
    for (const auto &result: results) {
        const std::string tradeId = result.getTradeId();
        const std::optional<double> resultValue = result.getResult();
        std::optional<std::string> errorValue = result.getError();

        std::string line;
        if (resultValue && errorValue) {
            std::cout << "BOTH" << "\n";
            line.append(tradeId);
            line.append(" : ");
            line.append(std::to_string(resultValue.value()));
            line.append(" : ");
            line.append(errorValue.value());
            line.append("\n");
            std::cout << line;
        } else if (resultValue) {
            line.append(tradeId);
            line.append(" : ");
            line.append(std::to_string(resultValue.value()));
            line.append("\n");
            std::cout << line;
        } else if (errorValue) {
            line.append(tradeId);
            line.append(" : ");
            line.append(errorValue.value());
            line.append("\n");
            std::cout << line;
        } else {
            std::cout << "Unable to print tradeID: " << tradeId << "\n";
        }
        // Write code here to print out the results such that we have:
        // TradeID : Result : Error
        // If there is no result then the output should be:
        // TradeID : Error
        // If there is no error the output should be:
        // TradeID : Result
    }
}
