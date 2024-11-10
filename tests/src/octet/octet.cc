#include <gtest/gtest.h>
#include "octet.h"

TEST(OctetValidatorTest, ValidOctets) {
    EXPECT_TRUE(OctetValidator::isValidOctet("0"));
    EXPECT_TRUE(OctetValidator::isValidOctet("255"));

    EXPECT_TRUE(OctetValidator::isValidOctet("128"));
    EXPECT_TRUE(OctetValidator::isValidOctet("42"));
    EXPECT_TRUE(OctetValidator::isValidOctet("254"));
}

TEST(OctetValidatorTest, OutOfRangeOctets) {
    EXPECT_FALSE(OctetValidator::isValidOctet("256"));
    EXPECT_FALSE(OctetValidator::isValidOctet("300"));
    EXPECT_FALSE(OctetValidator::isValidOctet("1000"));

    EXPECT_FALSE(OctetValidator::isValidOctet("-1"));
    EXPECT_FALSE(OctetValidator::isValidOctet("-255"));
}

TEST(OctetValidatorTest, NonNumericOctets) {
    EXPECT_FALSE(OctetValidator::isValidOctet("abc"));
    EXPECT_FALSE(OctetValidator::isValidOctet("A"));

    EXPECT_FALSE(OctetValidator::isValidOctet("12a"));
    EXPECT_FALSE(OctetValidator::isValidOctet("a12"));

    EXPECT_FALSE(OctetValidator::isValidOctet("12!"));
    EXPECT_FALSE(OctetValidator::isValidOctet("@123"));
    EXPECT_FALSE(OctetValidator::isValidOctet("123."));
}

TEST(OctetValidatorTest, LeadingZeros) {
    // Single zero is valid
    EXPECT_TRUE(OctetValidator::isValidOctet("0"));

    // Leading zeros not allowed
    EXPECT_FALSE(OctetValidator::isValidOctet("01"));
    EXPECT_FALSE(OctetValidator::isValidOctet("001"));
    EXPECT_FALSE(OctetValidator::isValidOctet("0042"));
    EXPECT_FALSE(OctetValidator::isValidOctet("00255"));
}

// Empty and Whitespace
TEST(OctetValidatorTest, EmptyAndWhitespaceOctets) {
    // Empty string
    EXPECT_FALSE(OctetValidator::isValidOctet(""));

    // Whitespace
    EXPECT_FALSE(OctetValidator::isValidOctet(" "));
    EXPECT_FALSE(OctetValidator::isValidOctet("  "));
    EXPECT_FALSE(OctetValidator::isValidOctet(" 42 "));
    EXPECT_FALSE(OctetValidator::isValidOctet("4 2"));
}

TEST(OctetValidatorTest, LargeNumberOctets) {
    // Numbers beyond int range
    EXPECT_FALSE(OctetValidator::isValidOctet("4294967296")); // 2^32
    EXPECT_FALSE(OctetValidator::isValidOctet("18446744073709551616")); // 2^64
}

TEST(OctetValidatorTest, BoundaryConditions) {
    // Exact boundary values
    EXPECT_TRUE(OctetValidator::isValidOctet("0")); // Minimum
    EXPECT_TRUE(OctetValidator::isValidOctet("255")); // Maximum

    // Just outside boundaries
    EXPECT_FALSE(OctetValidator::isValidOctet("-1")); // Below minimum
    EXPECT_FALSE(OctetValidator::isValidOctet("256")); // Above maximum
}

// Performance and Stress Testing
TEST(OctetValidatorTest, StressTests) {
    // Very long inputs
    EXPECT_FALSE(OctetValidator::isValidOctet("12345678901234567890"));
    EXPECT_FALSE(OctetValidator::isValidOctet(std::string(1000, '1')));
}
