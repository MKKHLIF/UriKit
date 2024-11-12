#include "segment-decoder.h"
#include "decoder.h"

bool SegmentDecoder::decode(std::string &segment, const CharacterSet &allowed) {
    const auto original_segment = std::move(segment);
    segment.clear();

    bool decoding_pec = false;
    PercentDecoder decoder;

    for (const auto c: original_segment) {
        if (decoding_pec) {
            if (!decoder.next(c)) {
                return false;
            }
            if (decoder.done()) {
                decoding_pec = false;
                segment.push_back(decoder.getDecodedCharacter());
            }
        } else if (c == '%') {
            decoding_pec = true;
            decoder = PercentDecoder();
        } else {
            if (allowed.contains(c)) {
                segment.push_back(c);
            } else {
                return false;
            }
        }
    }
    return true;
}
