#include "decoder.h"
#include "sets.h"

struct PercentDecoder::Impl {
    int decoded_character = 0;
    size_t digitsLeft = 2;

    bool ShiftInHexDigit(const char c) {
        decoded_character <<= 4;
        if (CharacterSets::DIGIT.contains(c)) {
            decoded_character += c - '0';
        } else if (CharacterSets::HEX_UPPER.contains(c)) {
            decoded_character += c - 'A' + 10;
        } else if (CharacterSets::HEX_LOWER.contains(c)) {
            decoded_character += c - 'a' + 10;
        } else {
            return false;
        }
        return true;
    }
};

PercentDecoder::~PercentDecoder() noexcept = default;

PercentDecoder::PercentDecoder(PercentDecoder &&) noexcept = default;

PercentDecoder &PercentDecoder::operator=(PercentDecoder &&) noexcept = default;

PercentDecoder::PercentDecoder()
    : impl_(new Impl) {
}

bool PercentDecoder::next(const char c) const {
    if (!impl_->ShiftInHexDigit(c)) {
        return false;
    }
    --impl_->digitsLeft;
    return true;
}

bool PercentDecoder::done() const {
    return (impl_->digitsLeft == 0);
}

char PercentDecoder::getDecodedCharacter() const {
    return static_cast<char>(impl_->decoded_character);
}
