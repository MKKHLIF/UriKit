#include "encoder.h"

std::string PercentEncoder::encode(const std::string &segment, const CharacterSet &allowed) {
    std::string encoded;
    for (const char c: segment) {
        if (allowed.contains(c)) {
            encoded += c;
        } else {
            encoded += '%';
            encoded += "0123456789ABCDEF"[static_cast<unsigned char>(c) >> 4];
            encoded += "0123456789ABCDEF"[static_cast<unsigned char>(c) & 0xf];
        }
    }
    return encoded;
}
