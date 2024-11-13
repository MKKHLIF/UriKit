#pragma once
#include <string>

class QueryParser {
public:
    [[nodiscard]] static bool parse(const std::string &uri, std::string &query);
};
