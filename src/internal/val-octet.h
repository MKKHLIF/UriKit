#pragma once
#include <string>

class OctetValidator {
public:
    [[nodiscard]] static bool isValidOctet(const std::string &octet);
};

