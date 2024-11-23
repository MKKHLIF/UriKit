#pragma once
#include <string>

/**
 * @class FragmentParser
 * @brief A class for parsing the fragment component of a URI.
 *
 * The `FragmentParser` class provides functionality to extract and decode the fragment part of a URI.
 * The fragment is the part of the URI that comes after the `#` symbol, and this class allows parsing and
 * decoding it while also updating the original URI.
 */
class FragmentParser {
public:
    /**
     * @brief Parses the fragment from a URI and decodes it.
     * @param uri The URI to parse.
     * @param fragment The string to store the parsed fragment.
     * @return true if the fragment was successfully parsed and decoded, false otherwise.
     * @details This method looks for a `#` symbol in the URI to identify the start of the fragment. If the
     *          fragment is found, it is extracted and decoded. The URI is updated to remove the fragment part.
     */
    [[nodiscard]] static bool parse(std::string &uri, std::string &fragment);
};
