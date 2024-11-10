#pragma once
#include <regex>
#include <string>


class IPv4Validator {
public:
    static bool isValid(const std::string &address);

private:
    static constexpr size_t EXPECTED_GROUPS = 4;
    static constexpr char DELIMITER = '.';

    enum class ParserState {
        ExpectDigit,
        ParseOctet
    };

    static bool processCharacter(char c,
                                 ParserState &state,
                                 std::string &current_octet,
                                 size_t &group_count);
};
