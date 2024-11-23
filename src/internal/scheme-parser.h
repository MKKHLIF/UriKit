#pragma once
#include <string>

/**
 * @class SchemeParser
 * @brief A class responsible for parsing the scheme component of a URI.
 *
 * The `SchemeParser` class extracts the scheme part of a URI, which typically precedes the `://` in a URI string.
 * It validates the scheme and removes it from the URI string for further processing. Supported schemes may include
 * "http", "https", "file", "mailto", and others.
 */
class SchemeParser {
public:
    /**
     * @brief Parses the scheme component from a URI string.
     * @param uri The URI string from which the scheme component will be extracted.
     * @param scheme A string that will hold the parsed scheme component.
     * @return true if the scheme was successfully parsed and is valid, false otherwise.
     *
     * This method extracts the scheme portion of the URI (i.e., the part before the first `:`). It then validates
     * the scheme to ensure it adheres to proper format rules. If the scheme is valid, it is stored in the `scheme`
     * string, and the scheme is removed from the original URI. The method also handles cases where the URI may be
     * a relative reference (lacking a scheme), and it will return `true` in such cases. If the scheme is invalid,
     * the method returns `false`.
     */
    [[nodiscard]] static bool parse(std::string &uri, std::string &scheme);
};
