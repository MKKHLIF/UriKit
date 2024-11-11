#include <gtest/gtest.h>

#include "val-scheme.h"


TEST(SchemeValidatorTests, EmptyScheme) {
    const bool is_valid = SchemeValidator::isValid("");
    EXPECT_FALSE(is_valid);
}

TEST(SchemeValidatorTests, InvalidFirstCharacter) {
    const bool is_valid1 = SchemeValidator::isValid("1http"); // First character is a digit
    const bool is_valid2 = SchemeValidator::isValid("-http"); // First character is a hyphen
    const bool is_valid3 = SchemeValidator::isValid("+https"); // First character is a plus
    const bool is_valid4 = SchemeValidator::isValid(".http"); // First character is a dot
    EXPECT_FALSE(is_valid1);
    EXPECT_FALSE(is_valid2);
    EXPECT_FALSE(is_valid3);
    EXPECT_FALSE(is_valid4);
}

TEST(SchemeValidatorTests, ValidSchemeAlphaOnly) {
    const bool is_valid1 = SchemeValidator::isValid("http");
    const bool is_valid2 = SchemeValidator::isValid("Https");
    EXPECT_TRUE(is_valid1);
    EXPECT_TRUE(is_valid2);
}

TEST(SchemeValidatorTests, ValidSchemeWithDigits) {
    const bool is_valid1 = SchemeValidator::isValid("http1");
    const bool is_valid2 = SchemeValidator::isValid("H2tp");
    const bool is_valid3 = SchemeValidator::isValid("ftp123");
    EXPECT_TRUE(is_valid1);
    EXPECT_TRUE(is_valid2);
    EXPECT_TRUE(is_valid3);
}

TEST(SchemeValidatorTests, ValidSchemeWithSpecialCharacters) {
    const bool is_valid1 = SchemeValidator::isValid("http+");
    const bool is_valid2 = SchemeValidator::isValid("my-scheme");
    const bool is_valid3 = SchemeValidator::isValid("ftp.protocol.");
    EXPECT_TRUE(is_valid1);
    EXPECT_TRUE(is_valid2);
    EXPECT_TRUE(is_valid3);
}

TEST(SchemeValidatorTests, InvalidCharacters) {
    const bool is_valid1 = SchemeValidator::isValid("http^");
    const bool is_valid2 = SchemeValidator::isValid("https*");
    const bool is_valid3 = SchemeValidator::isValid("ftp@domain");
    const bool is_valid4 = SchemeValidator::isValid("ftp!port");
    EXPECT_FALSE(is_valid1);
    EXPECT_FALSE(is_valid2);
    EXPECT_FALSE(is_valid3);
    EXPECT_FALSE(is_valid4);
}

TEST(SchemeValidatorTests, SingleCharacterValidScheme) {
    const bool is_valid1 = SchemeValidator::isValid("h");
    const bool is_valid2 = SchemeValidator::isValid("F");
    EXPECT_TRUE(is_valid1);
    EXPECT_TRUE(is_valid2);
}

TEST(SchemeValidatorTests, SingleCharacterInvalidScheme) {
    const bool is_valid1 = SchemeValidator::isValid("1");
    const bool is_valid2 = SchemeValidator::isValid("-");
    const bool is_valid3 = SchemeValidator::isValid("+");
    const bool is_valid4 = SchemeValidator::isValid(".");
    EXPECT_FALSE(is_valid1);
    EXPECT_FALSE(is_valid2);
    EXPECT_FALSE(is_valid3);
    EXPECT_FALSE(is_valid4);
}

TEST(SchemeValidatorTests, MultiCharacterValidScheme) {
    const bool is_valid1 = SchemeValidator::isValid("http1");
    const bool is_valid2 = SchemeValidator::isValid("my-scheme");
    const bool is_valid3 = SchemeValidator::isValid("ftp+test");
    EXPECT_TRUE(is_valid1);
    EXPECT_TRUE(is_valid2);
    EXPECT_TRUE(is_valid3);
}

TEST(SchemeValidatorTests, MixedCaseScheme) {
    const bool is_valid1 = SchemeValidator::isValid("Http");
    const bool is_valid2 = SchemeValidator::isValid("HttP");
    const bool is_valid3 = SchemeValidator::isValid("FTp");
    EXPECT_TRUE(is_valid1);
    EXPECT_TRUE(is_valid2);
    EXPECT_TRUE(is_valid3);
}

TEST(SchemeValidatorTests, SingleCharacterScheme) {
    const bool is_valid = SchemeValidator::isValid("a");
    EXPECT_TRUE(is_valid);
}

TEST(SchemeValidatorTests, ValidSchemeWithMultipleSpecialChars) {
    const bool is_valid = SchemeValidator::isValid("http+example-test.protocol.");
    EXPECT_TRUE(is_valid);
}

TEST(SchemeValidatorTests, InvalidSchemeStartingWithSpecialChar) {
    const bool is_valid1 = SchemeValidator::isValid("+http");
    const bool is_valid2 = SchemeValidator::isValid("-http");
    const bool is_valid3 = SchemeValidator::isValid(".http");
    EXPECT_FALSE(is_valid1);
    EXPECT_FALSE(is_valid2);
    EXPECT_FALSE(is_valid3);
}

