#include <gtest/gtest.h>
#include "decoder.h"

class PercentDecoderTest : public ::testing::Test {
protected:
    PercentDecoder decoder;

    bool decodeHexSequence(const std::string &seq) const {
        for (const char c: seq) {
            if (!decoder.next(c)) {
                return false;
            }
        }
        return true;
    }
};

TEST_F(PercentDecoderTest, DecodeValidHexCharacter) {
    EXPECT_TRUE(decodeHexSequence("41"));
    EXPECT_TRUE(decoder.done());
    EXPECT_EQ(decoder.getDecodedCharacter(), 'A');
}

TEST_F(PercentDecoderTest, DecodeLowercaseHexCharacter) {
    EXPECT_TRUE(decodeHexSequence("61"));
    EXPECT_TRUE(decoder.done());
    EXPECT_EQ(decoder.getDecodedCharacter(), 'a');
}

TEST_F(PercentDecoderTest, RejectInvalidHexCharacter) {
    EXPECT_FALSE(decodeHexSequence("G1"));
    EXPECT_FALSE(decoder.done());
}

TEST_F(PercentDecoderTest, CaseInsensitiveHexCharacters) {
    EXPECT_TRUE(decodeHexSequence("a1"));
    EXPECT_TRUE(decoder.done());
    EXPECT_EQ(decoder.getDecodedCharacter(), static_cast<char>(0xA1));

    decoder = PercentDecoder();
    EXPECT_TRUE(decodeHexSequence("A1"));
    EXPECT_TRUE(decoder.done());
    EXPECT_EQ(decoder.getDecodedCharacter(), static_cast<char>(0xA1));
}

TEST_F(PercentDecoderTest, MultipleValidHexCharacters) {
    EXPECT_TRUE(decodeHexSequence("41"));
    EXPECT_TRUE(decoder.done());
    EXPECT_EQ(decoder.getDecodedCharacter(), 'A');

    decoder = PercentDecoder();
    EXPECT_TRUE(decodeHexSequence("20"));
    EXPECT_TRUE(decoder.done());
    EXPECT_EQ(decoder.getDecodedCharacter(), ' ');

    decoder = PercentDecoder();
    EXPECT_TRUE(decodeHexSequence("42"));
    EXPECT_TRUE(decoder.done());
    EXPECT_EQ(decoder.getDecodedCharacter(), 'B');
}

TEST_F(PercentDecoderTest, DoneFlagBehavior) {
    PercentDecoder freshDecoder;
    EXPECT_FALSE(freshDecoder.done());
    EXPECT_TRUE(freshDecoder.next('4'));
    EXPECT_FALSE(freshDecoder.done());
    EXPECT_TRUE(freshDecoder.next('1'));
    EXPECT_TRUE(freshDecoder.done());
    EXPECT_EQ(freshDecoder.getDecodedCharacter(), 'A');
}

TEST_F(PercentDecoderTest, UppercaseAndLowercaseHex) {
    EXPECT_TRUE(decodeHexSequence("7f"));
    EXPECT_TRUE(decoder.done());
    EXPECT_EQ(decoder.getDecodedCharacter(), static_cast<char>(0x7F));

    decoder = PercentDecoder();
    EXPECT_TRUE(decodeHexSequence("7F"));
    EXPECT_TRUE(decoder.done());
    EXPECT_EQ(decoder.getDecodedCharacter(), static_cast<char>(0x7F));
}

TEST_F(PercentDecoderTest, InvalidCharacterSequence) {
    EXPECT_FALSE(decodeHexSequence("Z1"));
    EXPECT_FALSE(decoder.done());
}
