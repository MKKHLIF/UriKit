#pragma once
#include <string>

class SchemeParser {
public:
    static bool parse(std::string &uri, std::string &scheme);
};
