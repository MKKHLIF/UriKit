#include "val-octet.h"

#include "character.h"
#include "sets.h"

bool OctetValidator::isValidOctet(const std::string &octet) {
    if (octet.empty()) {
        return false;
    }

    // Check for leading zeros (not allowed except for single 0)
    if (octet.length() > 1 && octet[0] == '0') {
        return false;
    }

    for (const char c: octet) {
        if (!CharacterSets::DIGIT.contains(c)) {
            return false;
        }
    }

    try {
        const int value = std::stoi(octet);
        return value >= 0 && value <= 255;
    } catch (...) {
        return false;
    }
}
