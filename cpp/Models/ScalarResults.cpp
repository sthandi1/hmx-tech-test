#include "ScalarResults.h"
#include <stdexcept>

ScalarResults::~ScalarResults() = default;

std::optional<ScalarResult> ScalarResults::operator[](const std::string& tradeId) const {
    if (!containsTrade(tradeId)) {
        return std::nullopt;
    }

    std::optional<double> priceResult = std::nullopt;
    std::optional<std::string> error = std::nullopt;

    auto resultIt = results_.find(tradeId);
    if (resultIt != results_.end()) {
        priceResult = resultIt->second;
    }

    auto errorIt = errors_.find(tradeId);
    if (errorIt != errors_.end()) {
        error = errorIt->second;
    }

    return ScalarResult(tradeId, priceResult, error);
}

bool ScalarResults::containsTrade(const std::string& tradeId) const {
    return results_.find(tradeId) != results_.end() || errors_.find(tradeId) != errors_.end();
}

void ScalarResults::addResult(const std::string& tradeId, double result) {
    results_[tradeId] = result;
}

void ScalarResults::addError(const std::string& tradeId, const std::string& error) {
    errors_[tradeId] = error;
}

ScalarResults::Iterator& ScalarResults::Iterator::operator++() {
    ++it_;
    return *this;
}

ScalarResult ScalarResults::Iterator::operator*() const {
    return *it_;
}

bool ScalarResults::Iterator::operator!=(const Iterator& other) const {
    return it_ != other.it_;
}

ScalarResults::Iterator ScalarResults::begin() const {
    cache_.clear();
    // Loop over results using structured bindings
    for (const auto & [tradeId, result] : results_) {
        // Find iterator to error if exists
        auto errorIt = errors_.find(tradeId);
        std::optional<std::string> error = std::nullopt;
        if (errorIt != errors_.end()) {
            // Dereference iterator pointer and store string value in optional
            error = errorIt->second;
        }
        else {
            // If there is no error then store a null optional
            error = std::nullopt;
        }
        cache_.emplace_back(tradeId, result, error);
    }

    // In case result isn't set loop over errors map too

    for (const auto & [tradeId, error] : errors_) {
        // Maps can only have a single key, so check if this is zero
        if (!results_.count(tradeId)) {
            // No result value if true so store a nullopt
            cache_.emplace_back(tradeId, std::nullopt, error);
        }
    }
    return Iterator(cache_.cbegin());
}

ScalarResults::Iterator ScalarResults::end() const {
    return Iterator(cache_.cend());
}
