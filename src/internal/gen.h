#pragma once

#include <string>
#include <uri/uri.h>
/**
 * @class URIGenerator
 * @brief A class for generating URI strings from a `Uri` object.
 *
 * The `URIGenerator` class provides functionality to construct a well-formed URI string based on the components
 * of a `Uri` object. This includes encoding any necessary parts (such as user info, host, path, query, and fragment)
 * and assembling them into a complete URI string.
 */
class URIGenerator {
public:
	/**
	 * @brief Generates a URI string from a `Uri` object.
	 * @param uri The `Uri` object containing the URI components.
	 * @return A string representing the complete URI.
	 * @details This method generates a URI string by concatenating the scheme, authority, path, query, and fragment
	 *          components of the provided `Uri` object. Each part is percent-encoded as needed according to the
	 *          specified character sets. Special handling is provided for IPv6 addresses and certain edge cases like
	 *          empty paths.
	 */
	static std::string generate(const Uri &uri);
};
