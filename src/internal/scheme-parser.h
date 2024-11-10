#pragma once
#include <string>

class SchemeParser {
public:
     [[nodiscard]] static bool parse(std::string &uri, std::string &scheme);
};
