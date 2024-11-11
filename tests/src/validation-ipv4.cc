#include <gtest/gtest.h>
#include "val-ipv4.h"

TEST(IPv4ValidatorTest, ValidAddresses) {
    EXPECT_TRUE(IPv4Validator::isValid("192.168.1.1"));
    EXPECT_TRUE(IPv4Validator::isValid("255.255.255.255"));
    EXPECT_TRUE(IPv4Validator::isValid("0.0.0.0"));
    EXPECT_TRUE(IPv4Validator::isValid("10.0.0.1"));
    EXPECT_TRUE(IPv4Validator::isValid("172.16.254.1"));
}

// Test invalid IPv4 addresses
TEST(IPv4ValidatorTest, InvalidAddresses) {
    EXPECT_FALSE(IPv4Validator::isValid("256.100.50.25")); // 256 is invalid
    EXPECT_FALSE(IPv4Validator::isValid("192.168.1")); // Missing last octet
    EXPECT_FALSE(IPv4Validator::isValid("192.168.1.256")); // Last octet is invalid
    EXPECT_FALSE(IPv4Validator::isValid("192.168.1.-1")); // Negative number
    EXPECT_FALSE(IPv4Validator::isValid("192.168.1.1.1")); // Too many octets
    EXPECT_FALSE(IPv4Validator::isValid("abc.def.ghi.jkl")); // Non-numeric
    EXPECT_FALSE(IPv4Validator::isValid("192.168.1.1/24")); // CIDR notation
    EXPECT_FALSE(IPv4Validator::isValid("")); // Empty string
    EXPECT_FALSE(IPv4Validator::isValid("192.168.1.1.1")); // Too many segments
}

// Test edge cases
TEST(IPv4ValidatorTest, EdgeCases) {
    EXPECT_TRUE(IPv4Validator::isValid("0.0.0.0")); // Lower edge case
    EXPECT_TRUE(IPv4Validator::isValid("255.255.255.255")); // Upper edge case
    EXPECT_FALSE(IPv4Validator::isValid("01.02.03.04")); // Leading zeros
}
