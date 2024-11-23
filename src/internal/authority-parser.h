#pragma once

#include <string>
#include <vector>

/**
 * @class AuthorityParser
 * @brief A utility class to parse authority components from a URI string.
 *
 * This class provides functionality to extract and validate the userinfo, host,
 * and port components of a URI authority string. It processes various formats,
 * including IPv6 addresses, percent-encoded characters, and userinfo segments.
 */
class AuthorityParser {
public:
    /**
     * @brief Parses a URI authority string into its individual components: userinfo, host, and port.
     *
     * The input authority string can have various formats, including:
     * - user:password@www.example.com:8080
     * - www.example.com:8080
     * - www.example.com
     * - [2001:db8::1]:8080
     * - [2001:db8::1]
     *
     * The function extracts the userinfo, host, and port components and stores them
     * in the provided vector. If the authority string is malformed or invalid, the function
     * returns false and the components vector is not modified.
     *
     * @param authority The URI authority string to be parsed.
     * @param components A vector that will hold the parsed components (userinfo, host, port).
     *
     * @return true if the parsing is successful and all components are valid, false otherwise.
     */
    [[nodiscard]] static bool parse(const std::string &authority, std::vector<std::string> &components);

private:
    enum class HostParsingState {
        FIRST_CHARACTER,
        NOT_IP_LITERAL,
        PERCENT_ENCODED_CHARACTER,
        IP_LITERAL,
        IPV6_ADDRESS,
        IPV_FUTURE_NUMBER,
        IPV_FUTURE_BODY,
        GARBAGE_CHECK,
        PORT,
    };
};
