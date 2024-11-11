#pragma once
#include <string>

class PortValidator {
public:
    [[nodiscard]] static bool isValid(const std::string &port);
};
