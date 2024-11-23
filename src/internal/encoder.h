#pragma once
#include <string>
#include "character.h"

/**
 * @class PercentEncoder
 * @brief A class for encoding characters in percent-encoded format (URL encoding).
 *
 * The `PercentEncoder` class provides a method to encode a string such that all characters not included in
 * the allowed set are percent-encoded (e.g., a space character would be encoded as `%20`).
 */
class PercentEncoder {
public:
    /**
     * @brief Encodes a string by percent-encoding characters not in the allowed set.
     * @param segment The string to encode.
     * @param allowed A `CharacterSet` representing the characters that should not be encoded.
     * @return A new string where characters not in the `allowed` set are percent-encoded.
     * @details Each character in the `segment` is checked against the `allowed` set. If the character is
     *          allowed, it is added as is. If not, it is replaced with its percent-encoded equivalent.
     */
    static std::string encode(const std::string &segment, const CharacterSet &allowed);
};
