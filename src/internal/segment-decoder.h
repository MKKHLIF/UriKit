#pragma once
#include <string>

#include "character.h"

/**
 * @class SegmentDecoder
 * @brief A class responsible for decoding percent-encoded segments in a URI.
 *
 * The `SegmentDecoder` class is designed to decode percent-encoded characters (e.g., `%20` for space) in a URI
 * segment. It ensures that only allowed characters are present in the segment and that percent-encoded sequences
 * are correctly decoded back into their respective characters.
 */
class SegmentDecoder {
public:
    /**
     * @brief Decodes a percent-encoded URI segment.
     * @param segment The segment to be decoded, which will be modified in place.
     * @param allowed A `CharacterSet` that defines the set of allowed characters in the segment.
     * @return true if the segment was successfully decoded, false if an error was encountered (e.g., invalid percent-encoding).
     *
     * This method decodes a given segment of a URI, handling percent-encoded characters. For example, it will
     * convert `%20` to a space character. The segment is checked against the provided `allowed` character set,
     * ensuring that only allowed characters are present (whether they are already decoded or not). If an invalid
     * character or an invalid percent-encoded sequence is encountered, the method will return `false`. If the
     * decoding is successful, the `segment` will be updated with the decoded version.
     */
    static bool decode(std::string &segment, const CharacterSet &allowed);
};
