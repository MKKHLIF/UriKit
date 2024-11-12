#include <gtest/gtest.h>
#include "encoder.h"
#include "sets.h"

class PercentEncoderTest : public ::testing::Test {
};

// User info encoding
TEST_F(PercentEncoderTest, EncodeUserInfoNotEncoded) {
    const std::string segment = "user:password";
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::USER_INFO_NOT_PCT_ENCODED);
    // ':' is allowed, so no encoding should happen
    EXPECT_EQ(encoded, "user:password");
}

TEST_F(PercentEncoderTest, EncodeUserInfoWithSpecialChars) {
    const std::string segment = "user@domain:password#info";
    const std::string expected = "user%40domain:password%23info"; // '@' -> %40, '#' -> %23
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::USER_INFO_NOT_PCT_ENCODED);
    EXPECT_EQ(encoded, expected);
}

// Host encoding
TEST_F(PercentEncoderTest, EncodeHostNotEncoded) {
    const std::string segment = "example.com";
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::REG_NAME_NOT_PCT_ENCODED);
    EXPECT_EQ(encoded, "example.com"); // No encoding for unreserved characters
}

TEST_F(PercentEncoderTest, EncodeHostWithSpecialChars) {
    const std::string segment = "exa#mple.com";
    const std::string expected = "exa%23mple.com"; // '#' -> %23
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::REG_NAME_NOT_PCT_ENCODED);
    EXPECT_EQ(encoded, expected);
}


TEST_F(PercentEncoderTest, EncodePathSegmentWithSpecialChars) {
    const std::string segment = "dir#section";
    const std::string expected = "dir%23section"; // '#' -> %23
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::PCHAR_NOT_PCT_ENCODED);
    EXPECT_EQ(encoded, expected);
}

// Query encoding
TEST_F(PercentEncoderTest, EncodeQueryNotEncoded) {
    const std::string segment = "key=value";
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::QUERY_NOT_PCT_ENCODED_WITHOUT_PLUS);
    EXPECT_EQ(encoded, "key=value"); // No encoding for unreserved characters
}

TEST_F(PercentEncoderTest, EncodeQueryWithSpecialChars) {
    const std::string segment = "key=hello&world";
    const std::string expected = "key=hello&world";
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::QUERY_NOT_PCT_ENCODED_WITHOUT_PLUS);
    EXPECT_EQ(encoded, expected); // & is allowed
}

TEST_F(PercentEncoderTest, EncodeQueryWithPlusInValue) {
    const std::string segment = "key=hello+world";
    const std::string expected = "key=hello%2Bworld"; // '+' should be encoded as %2B
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::QUERY_NOT_PCT_ENCODED_WITHOUT_PLUS);
    EXPECT_EQ(encoded, expected);
}

//  Query or fragment encoding
TEST_F(PercentEncoderTest, EncodeFragmentNotEncoded) {
    const std::string segment = "section1";
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::QUERY_OR_FRAGMENT_NOT_PCT_ENCODED);
    EXPECT_EQ(encoded, "section1"); // No encoding for unreserved characters
}

TEST_F(PercentEncoderTest, EncodeFragmentWithSpecialChars) {
    const std::string segment = "section1#details";
    const std::string expected = "section1%23details"; // '#' -> %23
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::QUERY_OR_FRAGMENT_NOT_PCT_ENCODED);
    EXPECT_EQ(encoded, expected);
}

// Encoding an empty string
TEST_F(PercentEncoderTest, EncodeEmptyString) {
    const std::string segment = "";
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::USER_INFO_NOT_PCT_ENCODED);
    EXPECT_EQ(encoded, "");
}

// Percent encoding of the special character '%'
TEST_F(PercentEncoderTest, EncodePercentCharacter) {
    const std::string segment = "%";
    const std::string expected = "%25"; // Percent itself should be encoded as %25
    const std::string encoded = PercentEncoder::encode(segment, CharacterSets::USER_INFO_NOT_PCT_ENCODED);
    EXPECT_EQ(encoded, expected);
}
