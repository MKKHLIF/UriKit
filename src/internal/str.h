#pragma once
#include <string>

/**
 * @class StringExtensions
 * @brief A utility class for string manipulation functions.
 *
 * The `StringExtensions` class provides various static methods that extend the functionality of standard
 * string operations. These methods aim to simplify common string transformations, such as converting
 * a string to lowercase.
 */
class StringExtensions {
public:
	/**
	 * @brief Converts a string to lowercase.
	 *
	 * This method takes a string and returns a new string with all characters converted to lowercase.
	 * It is case-insensitive and operates by iterating over the input string, transforming each character.
	 *
	 * @param str The input string to convert.
	 * @return A new string with all characters in lowercase.
	 */
	static std::string toLower(const std::string &str);
};
