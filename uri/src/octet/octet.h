#pragma once
#include <string>

class OctetValidator {
public:
    // Static method for validating a single octet
    static bool isValidOctet(const std::string &octet);
};

