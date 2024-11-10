#include "ipv4.h"
#include "sets.h"
#include "octet.h"

bool IPv4Validator::isValid(const std::string &address) {
    if (address.empty()) {
        return false;
    }

    size_t group_count = 0;
    auto state = ParserState::ExpectDigit;
    std::string current_octet;

    for (const char c: address) {
        if (!processCharacter(c, state, current_octet, group_count)) {
            return false;
        }
    }

    // Handle the last octet
    if (!current_octet.empty()) {
        ++group_count;
        if (!OctetValidator::isValidOctet(current_octet)) {
            return false;
        }
    }

    return (group_count == EXPECTED_GROUPS);
}

bool IPv4Validator::processCharacter(const char c,
                                     ParserState &state,
                                     std::string &current_octet,
                                     size_t &group_count) {
    switch (state) {
        case ParserState::ExpectDigit:
            if (!CharacterSets::DIGIT.contains(c)) {
                return false;
            }
            current_octet.push_back(c);
            state = ParserState::ParseOctet;
            return true;

        case ParserState::ParseOctet:
            if (c == DELIMITER) {
                if (++group_count >= EXPECTED_GROUPS) {
                    return false;
                }
                if (!OctetValidator::isValidOctet(current_octet)) {
                    return false;
                }
                current_octet.clear();
                state = ParserState::ExpectDigit;
                return true;
            }

            if (!CharacterSets::DIGIT.contains(c)) {
                return false;
            }
            current_octet.push_back(c);
            return true;
    }
    return false;
}
