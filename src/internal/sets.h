#pragma once
#include "character.h"

/**
 * @class CharacterSets
 * @brief A collection of predefined `CharacterSet` instances for various URI components.
 *
 * The `CharacterSets` class holds a collection of static, predefined `CharacterSet` objects, each representing
 * a specific set of characters that are valid for various parts of a URI. These character sets are used to validate
 * and parse URI segments like the scheme, host, path, query, and fragment, ensuring that characters conform to
 * the appropriate syntax for each URI component.
 */
class CharacterSets {
public:
    /** @brief A `CharacterSet` containing all alphabetic characters (A-Z, a-z). */
    static const CharacterSet ALPHA;

    /** @brief A `CharacterSet` containing all numeric characters (0-9). */
    static const CharacterSet DIGIT;

    /** @brief A `CharacterSet` containing characters valid for the scheme, except the first character. */
    static const CharacterSet SCHEME_NOT_FIRST;

    /** @brief A `CharacterSet` containing valid hexadecimal characters (0-9, A-F, a-f). */
    static const CharacterSet HEXDIG;

    /** @brief A `CharacterSet` containing uppercase hexadecimal characters (A-F). */
    static const CharacterSet HEX_UPPER;

    /** @brief A `CharacterSet` containing lowercase hexadecimal characters (a-f). */
    static const CharacterSet HEX_LOWER;

    /** @brief A `CharacterSet` containing unreserved characters in a URI (letters, digits, '-', '.', '_', '~'). */
    static const CharacterSet UNRESERVED;

    /** @brief A `CharacterSet` containing delimiter characters used in URIs, such as '!', '$', '&', etc. */
    static const CharacterSet SUB_DELIMS;

    /** @brief A `CharacterSet` containing valid characters for a non-percent-encoded PCHAR (path, query, or fragment). */
    static const CharacterSet PCHAR_NOT_PCT_ENCODED;

    /** @brief A `CharacterSet` containing characters valid for query or fragment components, excluding percent-encoding. */
    static const CharacterSet QUERY_OR_FRAGMENT_NOT_PCT_ENCODED;

    /** @brief A `CharacterSet` for query components, excluding percent-encoded characters and '+' signs. */
    static const CharacterSet QUERY_NOT_PCT_ENCODED_WITHOUT_PLUS;

    /** @brief A `CharacterSet` for user information in URIs, excluding percent-encoding. */
    static const CharacterSet USER_INFO_NOT_PCT_ENCODED;

    /** @brief A `CharacterSet` for valid regular name characters in URIs, excluding percent-encoding. */
    static const CharacterSet REG_NAME_NOT_PCT_ENCODED;

    /** @brief A `CharacterSet` for the last part of an IPv6 address in a URI (used for "ipvFuture" notation). */
    static const CharacterSet IPV_FUTURE_LAST_PART;
};

