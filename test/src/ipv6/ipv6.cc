#include <gtest/gtest.h>
#include <ipv6/ipv6.h>

class IPv6ValidatorTest : public ::testing::Test {
};

// Valid standard IPv6 addresses
TEST(IPv6ValidatorTest, ValidStandardAddresses) {
    EXPECT_TRUE(IPv6Validator::isValid("2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    EXPECT_TRUE(IPv6Validator::isValid("2001:db8:85a3:0:0:8a2e:370:7334"));
    EXPECT_TRUE(IPv6Validator::isValid("2001:db8:85a3::8a2e:370:7334"));
    EXPECT_TRUE(IPv6Validator::isValid("::1")); // Loopback
    EXPECT_TRUE(IPv6Validator::isValid("::")); // All zeros
    EXPECT_TRUE(IPv6Validator::isValid("2001:db8::"));
}

// Test different valid hex cases
TEST(IPv6ValidatorTest, ValidHexCases) {
    EXPECT_TRUE(IPv6Validator::isValid("2001:0DB8:85A3:0000:0000:8A2E:0370:7334")); // Uppercase
    EXPECT_TRUE(IPv6Validator::isValid("2001:0db8:85a3:0000:0000:8a2e:0370:7334")); // Lowercase
    EXPECT_TRUE(IPv6Validator::isValid("2001:Db8:85A3:0000:0000:8a2E:0370:7334")); // Mixed case
}

// Zero compression cases
TEST(IPv6ValidatorTest, ZeroCompression) {
    // Single group of zeros
    EXPECT_TRUE(IPv6Validator::isValid("2001:db8:85a3::8a2e:370:7334"));

    // Multiple groups of zeros
    EXPECT_TRUE(IPv6Validator::isValid("2001::370:7334"));
    EXPECT_TRUE(IPv6Validator::isValid("2001:db8::1"));

    // Leading zeros
    EXPECT_TRUE(IPv6Validator::isValid("::2:3:4:5:6:7:8"));

    // Trailing zeros
    EXPECT_TRUE(IPv6Validator::isValid("1:2:3:4:5:6:7::"));
}

// Special addresses
TEST(IPv6ValidatorTest, SpecialAddresses) {
    EXPECT_TRUE(IPv6Validator::isValid("::1")); // Loopback
    EXPECT_TRUE(IPv6Validator::isValid("::")); // Unspecified address
    EXPECT_TRUE(IPv6Validator::isValid("fe80::1")); // Link-local
    EXPECT_TRUE(IPv6Validator::isValid("ff02::1")); // Multicast
}

// Invalid formats
TEST(IPv6ValidatorTest, InvalidFormats) {
    // Too many segments
    EXPECT_FALSE(IPv6Validator::isValid("2001:0db8:85a3:0000:0000:8a2e:0370:7334:1111"));

    // Too few segments
    EXPECT_FALSE(IPv6Validator::isValid("2001:0db8:85a3:0000:0000:8a2e:0370"));

    // Invalid characters
    EXPECT_FALSE(IPv6Validator::isValid("2001:0db8:85a3:0000:0000:8a2e:0370:xxxx"));
    EXPECT_FALSE(IPv6Validator::isValid("2001:0db8:85g3:0000:0000:8a2e:0370:7334"));

    // Empty string
    EXPECT_FALSE(IPv6Validator::isValid(""));
}

// Invalid zero compression
TEST(IPv6ValidatorTest, InvalidZeroCompression) {
    // Multiple zero compressions
    EXPECT_FALSE(IPv6Validator::isValid("2001::85a3::7334"));

    // Invalid use with wrong number of segments
    EXPECT_FALSE(IPv6Validator::isValid("2001::85a3::"));
    EXPECT_FALSE(IPv6Validator::isValid("::85a3::"));

    // Too many segments with compression
    EXPECT_FALSE(IPv6Validator::isValid("1:2:3:4:5:6:7:8:9::"));
}

// Invalid segment values
TEST(IPv6ValidatorTest, InvalidSegmentValues) {
    // Segments too long
    EXPECT_FALSE(IPv6Validator::isValid("2001:0db8:85a3:00000:0000:8a2e:0370:7334"));

    // Segments too short
    EXPECT_FALSE(IPv6Validator::isValid("2001:db8:85a3:0:0:8a2e:37:734:"));

    // Invalid hex values
    EXPECT_FALSE(IPv6Validator::isValid("2001:0db8:85a3:0000:0000:8a2e:0370:ghij"));
}

// Edge cases with delimiters
TEST(IPv6ValidatorTest, DelimiterEdgeCases) {
    // Extra colons
    EXPECT_FALSE(IPv6Validator::isValid("2001:::db8:85a3:0000:0000:8a2e:0370:7334"));
    EXPECT_FALSE(IPv6Validator::isValid(":::"));

    // Missing colons
    EXPECT_FALSE(IPv6Validator::isValid("2001:0db885a3:0000:0000:8a2e:0370:7334"));

    // Wrong delimiters
    EXPECT_FALSE(IPv6Validator::isValid("2001.0db8.85a3.0000.0000.8a2e.0370.7334"));
}

// Mixed notation cases
TEST(IPv6ValidatorTest, MixedNotation) {
    // IPv4-mapped IPv6 addresses
    EXPECT_TRUE(IPv6Validator::isValid("::ffff:192.168.1.1"));
    EXPECT_TRUE(IPv6Validator::isValid("::ffff:0:192.168.1.1"));

    // Invalid mixed notation
    // EXPECT_FALSE(IPv6Validator::isValid("2001:db8::192.168.1.1")); // Invalid position
    EXPECT_FALSE(IPv6Validator::isValid("::ffff:192.168.1")); // Incomplete IPv4
    EXPECT_FALSE(IPv6Validator::isValid("::ffff:192.168.1.256")); // Invalid IPv4
}

// Whitespace handling
TEST(IPv6ValidatorTest, WhitespaceHandling) {
    EXPECT_FALSE(IPv6Validator::isValid(" 2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    EXPECT_FALSE(IPv6Validator::isValid("2001:0db8:85a3:0000:0000:8a2e:0370:7334 "));
    EXPECT_FALSE(IPv6Validator::isValid("2001:0db8:85a3:0000 :0000:8a2e:0370:7334"));
}

// Scope ID handling (if supported)
TEST(IPv6ValidatorTest, ScopeIdHandling) {
    // EXPECT_TRUE(IPv6Validator::isValid("fe80::1%eth0"));
    // EXPECT_TRUE(IPv6Validator::isValid("fe80::1%1"));
    EXPECT_FALSE(IPv6Validator::isValid("2001:db8::1%eth0")); // Scope not allowed for global
}

// Performance tests
TEST(IPv6ValidatorTest, PerformanceTests) {
    // Very long invalid input
    std::string longInput(1000, 'a');
    EXPECT_FALSE(IPv6Validator::isValid(longInput));

    // Long valid input with maximum segment lengths
    EXPECT_TRUE(IPv6Validator::isValid("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"));
}
