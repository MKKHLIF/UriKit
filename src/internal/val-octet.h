#pragma once
#include <string>

/**
 * @class OctetValidator
 * @brief Validates an octet in an IPv4 address.
 *
 * The `OctetValidator` class provides functionality to validate a string
 * representation of an octet, which is a numeric value between 0 and 255.
 * Octets are part of an IPv4 address and must follow specific rules:
 * 1. The octet must consist of digits only.
 * 2. The octet cannot have leading zeros (except for the value "0").
 * 3. The value must be between 0 and 255 (inclusive).
 */
class OctetValidator {
public:
    /**
     * @brief Validates if a string represents a valid octet in an IPv4 address.
     *
     * This method checks the following:
     * 1. The string must not be empty.
     * 2. The string cannot contain leading zeros, unless the octet is exactly "0".
     * 3. The string must only contain digits.
     * 4. The string must represent an integer between 0 and 255 (inclusive).
     *
     * @param octet The string to be validated as an octet.
     * @return `true` if the string is a valid octet, `false` otherwise.
     *
     * @note If the string contains non-numeric characters, leading zeros (except for "0"),
     *       or represents a value outside the range 0-255, the method returns `false`.
     *
     * @example
     * std::string octet = "192";
     * bool isValid = OctetValidator::isValidOctet(octet);  // Returns true
     *
     * @example
     * std::string octet = "025";
     * bool isValid = OctetValidator::isValidOctet(octet);  // Returns false due to leading zero
     */
    [[nodiscard]] static bool isValidOctet(const std::string &octet);
};
