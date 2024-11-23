#pragma once
#include <string>

/**
 * @class PortValidator
 * @brief Validates a port number.
 *
 * The `PortValidator` class provides functionality to validate a string representation of a port number.
 * A valid port is an integer between 0 and 65535 inclusive.
 */
class PortValidator {
public:
    /**
     * @brief Validates if a string represents a valid port number.
     *
     * This method checks the following:
     * 1. The string must represent a valid integer.
     * 2. The integer must be within the valid range for port numbers (0-65535).
     *
     * @param port The string to be validated as a port number.
     * @return `true` if the string is a valid port number, `false` otherwise.
     *
     * @note A port number must be a non-negative integer and cannot exceed 65535.
     *
     * @example
     * std::string port = "8080";
     * bool isValid = PortValidator::isValid(port);  // Returns true
     *
     * @example
     * std::string port = "70000";
     * bool isValid = PortValidator::isValid(port);  // Returns false because it exceeds 65535
     */
    [[nodiscard]] static bool isValid(const std::string &port);
};
