#pragma once
#include <string>

/**
 * @class QueryParser
 * @brief A class responsible for parsing the query component of a URI.
 *
 * The `QueryParser` class is designed to extract the query part from a URI string, which appears after the `?` character.
 * It stores the extracted query in a string, allowing for further processing or decoding.
 */
class QueryParser {
public:
    /**
     * @brief Parses the query component from a URI string.
     * @param uri The URI string from which the query component will be extracted.
     * @param query A string that will hold the parsed query component.
     * @return true if the query was successfully extracted, false otherwise.
     *
     * This method looks for the query portion of the URI, which is the part following the `?` character. If the URI
     * contains a query, it will be stored in the `query` string, excluding the leading `?` character. If there is no
     * query, the `query` string will remain empty.
     */
    [[nodiscard]] static bool parse(const std::string &uri, std::string &query);
};
