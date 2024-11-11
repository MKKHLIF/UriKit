#pragma once

#include <string>
#include <vector>

class AuthorityParser {
public:
    [[nodiscard]] static bool parse(std::string &authority, std::vector<std::string> &components);

private:
    enum class HostParsingState {
        FIRST_CHARACTER,
        NOT_IP_LITERAL,
        PERCENT_ENCODED_CHARACTER,
        IP_LITERAL,
        IPV6_ADDRESS,
        IPV_FUTURE_NUMBER,
        IPV_FUTURE_BODY,
        GARBAGE_CHECK,
        PORT,
    };
};
