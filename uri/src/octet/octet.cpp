#include "octet.h"

#include "../characters/character.h"
#include "../characters/character_sets.h"

bool OctetValidator::isValidOctet(const std::string &octet) {
    // Check if the string is empty
    if (octet.empty()) {
        return false;
    }

    // Check for leading zeros (not allowed except for single 0)
    if (octet.length() > 1 && octet[0] == '0') {
        return false;
    }

    // Check if all characters are digits
    for (const char c: octet) {
        if (!CharacterSets::DIGIT.contains(c)) {
            return false;
        }
    }

    // Convert to integer and check range
    try {
        const int value = std::stoi(octet);
        return value >= 0 && value <= 255;
    } catch (...) {
        return false;
    }
}
