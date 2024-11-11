#include <gtest/gtest.h>

#include "val-port.h"

TEST(PortValidatorTests, ValidPortInRange) {
    EXPECT_TRUE(PortValidator::isValid("1"));
    EXPECT_TRUE(PortValidator::isValid("65535"));
    EXPECT_TRUE(PortValidator::isValid("12345"));
}

// Zero is reserved and not valid for use in TCP and UDP protocols.
TEST(PortValidatorTests, ZeroPort) {
    const bool is_valid = PortValidator::isValid("0");
    EXPECT_FALSE(is_valid);
}

TEST(PortValidatorTests, PortGreaterThanMax) {
    EXPECT_FALSE(PortValidator::isValid("65536"));
    EXPECT_FALSE(PortValidator::isValid("70000"));
}

TEST(PortValidatorTests, NonNumericCharacters) {
    EXPECT_FALSE(PortValidator::isValid("abc"));
    EXPECT_FALSE(PortValidator::isValid("123a"));
    EXPECT_FALSE(PortValidator::isValid("12#45"));
}

TEST(PortValidatorTests, NegativePort) {
    EXPECT_FALSE(PortValidator::isValid("-1"));
    EXPECT_FALSE(PortValidator::isValid("-1234"));
}

TEST(PortValidatorTests, EmptyString) {
    EXPECT_FALSE(PortValidator::isValid(""));
}

TEST(PortValidatorTests, PortWithLeadingZeros) {
    EXPECT_FALSE(PortValidator::isValid("000123"));
    EXPECT_FALSE(PortValidator::isValid("0123"));
}

TEST(PortValidatorTests, PortWithWhitespace) {
    EXPECT_FALSE(PortValidator::isValid(" 123 "));
    EXPECT_FALSE(PortValidator::isValid(" 123"));
    EXPECT_FALSE(PortValidator::isValid("123 "));
}

TEST(PortValidatorTests, ValidMinPort) {
    EXPECT_TRUE(PortValidator::isValid("1"));
}

TEST(PortValidatorTests, ValidMaxPort) {
    EXPECT_TRUE(PortValidator::isValid("65535"));
}

TEST(PortValidatorTests, LargeNumberPort) {
    EXPECT_FALSE(PortValidator::isValid("999999999"));
    EXPECT_FALSE(PortValidator::isValid("1000000000000"));
}

TEST(PortValidatorTests, ValidSingleDigitPort) {
    EXPECT_TRUE(PortValidator::isValid("5"));
    EXPECT_TRUE(PortValidator::isValid("9"));
}

TEST(PortValidatorTests, DecimalPort) {
    EXPECT_FALSE(PortValidator::isValid("1.23"));
    EXPECT_FALSE(PortValidator::isValid("65535.0"));
}

TEST(PortValidatorTests, EmptyInput) {
    EXPECT_FALSE(PortValidator::isValid(" "));
    EXPECT_FALSE(PortValidator::isValid(""));
}
