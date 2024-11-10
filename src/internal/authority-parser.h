#pragma once
#include <string>
#include <vector>

class AuthorityParser {
public:
    [[nodiscard]] static bool parse(const std::string &authority, std::vector<std::string> authority_parts);

};