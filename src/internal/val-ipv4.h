#pragma once
#include <regex>
#include <string>


/**
 * @class IPv4Validator
 * @brief A utility class for validating IPv4 addresses.
 *
 * The `IPv4Validator` class provides a static method to validate whether a given string is a valid
 * IPv4 address. The class uses a parser that processes each character of the address and ensures it
 * adheres to the format of an IPv4 address, which consists of four octets separated by dots.
 */
class IPv4Validator {
public:
    /**
     * @brief Validates whether a string represents a valid IPv4 address.
     *
     * This method checks if the provided string is a valid IPv4 address. It ensures that the string contains
     * exactly four octets, each in the range of 0 to 255, and that they are properly separated by dots.
     *
     * @param address The IPv4 address string to validate.
     * @return `true` if the address is valid, `false` otherwise.
     */
    [[nodiscard]] static bool isValid(const std::string &address);

private:
    /// The expected number of octets in an IPv4 address (4 groups of digits).
    static constexpr size_t EXPECTED_GROUPS = 4;

    /// The delimiter used to separate the octets in the IPv4 address.
    static constexpr char DELIMITER = '.';

    /// Enum to define the state of the address parser.
    enum class ParserState {
        ExpectDigit, ///< Expecting a digit to begin an octet.
        ParseOctet ///< Parsing an individual octet.
    };

    /**
     * @brief Processes a single character during address validation.
     *
     * This method updates the state of the parser based on the current character being processed. It tracks
     * the octet being formed, ensures that digits are within valid ranges, and handles group counting based
     * on the structure of an IPv4 address.
     *
     * @param c The character to process.
     * @param state The current state of the parser.
     * @param current_octet The current octet being processed.
     * @param group_count The number of octets processed so far.
     * @return `true` if the character is processed successfully, `false` if an error occurs.
     */
    static bool processCharacter(char c,
                                 ParserState &state,
                                 std::string &current_octet,
                                 size_t &group_count);
};
