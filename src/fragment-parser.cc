#include "fragment-parser.h"

#include "segment-decoder.h"
#include "sets.h"

bool FragmentParser::parse(std::string &uri, std::string &fragment) {
    bool status = true;
    if (const size_t pos = uri.find('#'); pos != std::string::npos) {
        fragment = uri.substr(pos + 1);
        uri = uri.substr(0, pos);
        status = SegmentDecoder::decode(fragment, CharacterSets::QUERY_OR_FRAGMENT_NOT_PCT_ENCODED);
    }

    return status;
}
