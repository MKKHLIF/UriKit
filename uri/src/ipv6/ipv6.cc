#include "ipv6.h"
#include <regex>
#include "../ipv4/ipv4.h"
#include "../characters/character_sets.h"

bool IPv6Validator::isValid(const std::string &address) {
    auto state = ValidationState::NO_GROUPS_YET;

    size_t num_groups = 0;
    size_t num_digits = 0;
    bool double_colon_encountered = false;
    size_t potential_ipv4_address_start = 0;
    size_t position = 0;
    bool ipv4_address_encountered = false;
    for (const auto c: address) {
        switch (state) {
            case ValidationState::NO_GROUPS_YET: {
                if (c == ':') {
                    state = ValidationState::COLON_BUT_NO_GROUPS_YET;
                } else if (CharacterSets::DIGIT.contains(c)) {
                    potential_ipv4_address_start = position;
                    num_digits = 1;
                    state = ValidationState::IN_GROUP_COULD_BE_IPV4;
                } else if (CharacterSets::HEXDIG.contains(c)) {
                    num_digits = 1;
                    state = ValidationState::IN_GROUP_NOT_IPV4;
                } else {
                    return false;
                }
            }
            break;

            case ValidationState::COLON_BUT_NO_GROUPS_YET: {
                if (c == ':') {
                    double_colon_encountered = true;
                    state = ValidationState::AFTER_DOUBLE_COLON;
                } else {
                    return false;
                }
            }
            break;

            case ValidationState::AFTER_DOUBLE_COLON: {
                if (CharacterSets::DIGIT.contains(c)) {
                    potential_ipv4_address_start = position;
                    if (++num_digits > 4) {
                        return false;
                    }
                    state = ValidationState::IN_GROUP_COULD_BE_IPV4;
                } else if (CharacterSets::HEXDIG.contains(c)) {
                    if (++num_digits > 4) {
                        return false;
                    }
                    state = ValidationState::IN_GROUP_NOT_IPV4;
                } else {
                    return false;
                }
            }
            break;

            case ValidationState::IN_GROUP_NOT_IPV4: {
                if (c == ':') {
                    num_digits = 0;
                    ++num_groups;
                    state = ValidationState::COLON_AFTER_GROUP;
                } else if (CharacterSets::HEXDIG.contains(c)) {
                    if (++num_digits > 4) {
                        return false;
                    }
                } else {
                    return false;
                }
            }
            break;

            case ValidationState::IN_GROUP_COULD_BE_IPV4: {
                if (c == ':') {
                    num_digits = 0;
                    ++num_groups;
                    state = ValidationState::COLON_AFTER_GROUP;
                } else if (c == '.') {
                    ipv4_address_encountered = true;
                    break;
                } else if (CharacterSets::DIGIT.contains(c)) {
                    if (++num_digits > 4) {
                        return false;
                    }
                } else if (CharacterSets::HEXDIG.contains(c)) {
                    if (++num_digits > 4) {
                        return false;
                    }
                    state = ValidationState::IN_GROUP_NOT_IPV4;
                } else {
                    return false;
                }
            }
            break;

            case ValidationState::COLON_AFTER_GROUP: {
                if (c == ':') {
                    if (double_colon_encountered) {
                        return false;
                    } else {
                        double_colon_encountered = true;
                        state = ValidationState::AFTER_DOUBLE_COLON;
                    }
                } else if (CharacterSets::DIGIT.contains(c)) {
                    potential_ipv4_address_start = position;
                    ++num_digits;
                    state = ValidationState::IN_GROUP_COULD_BE_IPV4;
                } else if (CharacterSets::HEXDIG.contains(c)) {
                    ++num_digits;
                    state = ValidationState::IN_GROUP_NOT_IPV4;
                } else {
                    return false;
                }
            }
            break;
        }
        if (ipv4_address_encountered) {
            break;
        }
        ++position;
    }
    if (
        (state == ValidationState::IN_GROUP_NOT_IPV4)
        || (state == ValidationState::IN_GROUP_COULD_BE_IPV4)
    ) {
        // count trailing group
        ++num_groups;
    }
    if (
        (position == address.length())
        && (
            (state == ValidationState::COLON_BUT_NO_GROUPS_YET)
            || (state == ValidationState::COLON_AFTER_GROUP)
        )
    ) {
        // trailing single colon
        return false;
    }
    if (ipv4_address_encountered) {
        if (!IPv4Validator::isValid(address.substr(potential_ipv4_address_start))) {
            return false;
        }
        num_groups += 2;
    }
    if (double_colon_encountered) {
        // A double colon matches one or more groups (of 0).
        return (num_groups <= 7);
    } else {
        return (num_groups == 8);
    }
}

