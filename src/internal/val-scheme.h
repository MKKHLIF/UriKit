#pragma once
#include <string>

/**
 * @class SchemeValidator
 * @brief Validates a URI scheme.
 *
 * The `SchemeValidator` class provides functionality to validate the format of a URI scheme.
 * A valid URI scheme follows certain syntax rules as specified by the URI standard (RFC 3986).
 * It typically consists of alphanumeric characters and certain special symbols, but must not start with a digit.
 */
class SchemeValidator {
public:
	/**
	 * @brief Validates if a string represents a valid URI scheme.
	 *
	 * This method checks if the string conforms to the syntax rules for URI schemes.
	 * A valid scheme:
	 * 1. Starts with an alphabetic character.
	 * 2. May contain letters, digits, plus (+), period (.), or hyphen (-).
	 * 3. Cannot be empty.
	 *
	 * @param scheme The string to be validated as a URI scheme.
	 * @return `true` if the string is a valid URI scheme, `false` otherwise.
	 *
	 * @note Valid schemes are case-insensitive and should be followed by "://".
	 *
	 * @example
	 * std::string scheme = "https";
	 * bool isValid = SchemeValidator::isValid(scheme);  // Returns true
	 *
	 * @example
	 * std::string scheme = "123scheme";
	 * bool isValid = SchemeValidator::isValid(scheme);  // Returns false because it starts with a digit
	 */
	[[nodiscard]] static bool isValid(const std::string &scheme);
};
