#ifndef SCALARRESULTS_H
#define SCALARRESULTS_H

#include "IScalarResultReceiver.h"
#include "ScalarResult.h"
#include <map>
#include <vector>
#include <optional>
#include <string>
#include <iterator>

class ScalarResults : public IScalarResultReceiver {
public:
    ~ScalarResults() override;
    std::optional<ScalarResult> operator[](const std::string& tradeId) const;

    bool containsTrade(const std::string& tradeId) const;

    void addResult(const std::string& tradeId, double result) override;

    void addError(const std::string& tradeId, const std::string& error) override;

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ScalarResult;
        using difference_type = std::ptrdiff_t;
        using pointer = ScalarResult*;
        using reference = ScalarResult&;

        Iterator() = default;
        explicit Iterator(const std::vector<ScalarResult>::const_iterator it) : it_(it) {}

        // Iterator must be constructable from ScalarResults parent
        Iterator& operator++();
        ScalarResult operator*() const;
        bool operator!=(const Iterator& other) const;
    private:
        // Add private iterator for the storage vector
        std::vector<ScalarResult>::const_iterator it_;
    };

    Iterator begin() const;
    Iterator end() const;

private:
    // Map between tradeId and result
    std::map<std::string, double> results_;
    // Map between tradeId and Error
    std::map<std::string, std::string> errors_;
    // Storage cache to combine maps
    mutable std::vector<ScalarResult> cache_;
};

#endif // SCALARRESULTS_H
