#pragma once
#include <string>
#include <vector>

class AuthorityParser {
public:
    [[nodiscard]] static bool parse(std::string &authority, std::vector<std::string> &components);
};
