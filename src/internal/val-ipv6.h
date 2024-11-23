#pragma once
#include <string>

/**
 * @class IPv6Validator
 * @brief A utility class for validating IPv6 addresses.
 *
 * The `IPv6Validator` class provides a static method to validate whether a given string represents a valid
 * IPv6 address. It ensures that the address adheres to the format of an IPv6 address, which can consist of
 * up to eight groups of four hexadecimal digits, optionally separated by colons. The address may also include
 * an embedded IPv4 address.
 */
class IPv6Validator {
public:
    /**
     * @brief Validates whether a string represents a valid IPv6 address.
     *
     * This method checks if the provided string is a valid IPv6 address. It ensures that the address follows
     * the correct format, including handling optional embedded IPv4 addresses and double colons (::) used for
     * compression.
     *
     * @param address The IPv6 address string to validate.
     * @return `true` if the address is valid, `false` otherwise.
     */
    [[nodiscard]] static bool isValid(const std::string &address);

private:
    /// Enum representing the state of the validation process.
    enum class ValidationState {
        NoGroupsYet, ///< No groups have been parsed yet.
        ColonButNoGroupsYet, ///< A colon is found but no groups have been parsed.
        AfterDoubleColon, ///< After a double colon (::), which indicates group compression.
        InGroupNotIPv4, ///< In a group that is not an IPv4 address.
        InGroupCouldBeIPv4, ///< In a group that could potentially be an IPv4 address.
        ColonAfterGroup ///< After a group, expecting a colon or next group.
    };

    /// Structure to hold the context of the validation state.
    struct ValidationContext {
        ValidationState state = ValidationState::NoGroupsYet; ///< The current state of validation.
        size_t numGroups = 0; ///< Number of groups parsed.
        size_t numDigits = 0; ///< Number of digits in the current group.
        bool doubleColonFound = false; ///< Flag indicating if a double colon (::) was found.
        size_t ipv4Start = 0; ///< Starting position of an embedded IPv4 address, if any.
        size_t position = 0; ///< The current position in the address string.
        bool ipv4Found = false; ///< Flag indicating if an IPv4 address has been found.
    };

    /// Helper functions to handle each state of the parser.
    static bool handleNoGroupsYet(char c, ValidationContext &ctx);

    static bool handleColonButNoGroupsYet(char c, ValidationContext &ctx);

    static bool handleAfterDoubleColon(char c, ValidationContext &ctx);

    static bool handleInGroupNotIPv4(char c, ValidationContext &ctx);

    static bool handleInGroupCouldBeIPv4(char c, ValidationContext &ctx);

    static bool handleColonAfterGroup(char c, ValidationContext &ctx);

    /**
     * @brief Finalizes the validation process.
     *
     * This method checks whether the address has valid group counts and handles edge cases like a trailing colon
     * or an embedded IPv4 address.
     *
     * @param ctx The validation context holding the parsed state.
     * @param address The original IPv6 address string.
     * @return `true` if the address is valid, `false` otherwise.
     */
    static bool finalizeValidation(const ValidationContext &ctx, const std::string &address);
};
