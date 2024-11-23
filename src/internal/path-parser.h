#pragma once
#include <string>
#include <vector>

/**
 * @class PathParser
 * @brief A class responsible for parsing the path component of a URI.
 *
 * The `PathParser` class provides functionality to extract and parse the path from a URI string. It splits the path
 * into segments and ensures that each segment is properly encoded. Special handling is provided for absolute paths
 * and empty path segments.
 */
class PathParser {
public:
    /**
     * @brief Parses the path component from a URI string.
     * @param uri The URI string from which the path will be extracted and parsed.
     * @param path A vector of strings that will hold the path segments.
     * @return true if the path was successfully parsed, false if any errors occurred during parsing.
     *
     * This method splits the URI string into path segments, with each segment being separated by a `/`. The segments
     * are stored in the `path` vector. The method also decodes each path segment to ensure it follows proper encoding rules.
     * Special handling is provided for empty paths, where a single empty string is added to indicate the path is absolute.
     */
    [[nodiscard]] static bool parse(std::string &uri, std::vector<std::string> &path);
};
