#include <gtest/gtest.h>

#include "authority-parser.h"

TEST(StaticAuthorityParser, AllComponents) {
    const std::string authority = "user:password@www.amazon.co.uk:4523";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], "user:password");
    ASSERT_EQ(components[1], "www.amazon.co.uk");
    ASSERT_EQ(components[2], "4523");
}

// Test parsing authority with no userinfo, only host and port
TEST(StaticAuthorityParser, HostAndPortOnly) {
    const std::string authority = "www.amazon.co.uk:4523";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], ""); // No userinfo
    ASSERT_EQ(components[1], "www.amazon.co.uk");
    ASSERT_EQ(components[2], "4523");
}

// Test parsing authority with only userinfo (no host, no port)
TEST(StaticAuthorityParser, UserinfoOnly) {
    const std::string authority = "user:password@";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], "user:password");
    ASSERT_EQ(components[1], "");
    ASSERT_EQ(components[2], "");
}

// Test parsing authority with just host (no userinfo, no port)
TEST(StaticAuthorityParser, HostOnly) {
    const std::string authority = "www.amazon.co.uk";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], ""); // No userinfo
    ASSERT_EQ(components[1], "www.amazon.co.uk");
    ASSERT_EQ(components[2], ""); // No port
}

// Test parsing authority with just port (no userinfo, no host)
TEST(StaticAuthorityParser, PortOnly) {
    const std::string authority = ":8080";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], ""); // No userinfo
    ASSERT_EQ(components[1], ""); // No host
    ASSERT_EQ(components[2], "8080");
}

TEST(StaticAuthorityParser, EmptyAuthority) {
    const std::string authority;
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], ""); // No userinfo
    ASSERT_EQ(components[1], ""); // No host
    ASSERT_EQ(components[2], ""); // No port
}

// Test parsing authority with an invalid format (missing components)
TEST(StaticAuthorityParser, InvalidCharacterInHost) {
    const std::string authority = "user@password@";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_FALSE(status);
}

// Test parsing authority with IPv4 address
TEST(StaticAuthorityParser, IPv4Address) {
    const std::string authority = "user:password@192.168.1.1:8080";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], "user:password");
    ASSERT_EQ(components[1], "192.168.1.1");
    ASSERT_EQ(components[2], "8080");
}

// Test parsing authority with IPv6 address
TEST(StaticAuthorityParser, IPv6Address) {
    const std::string authority = "user:password@[2001:db8::1]:9090";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], "user:password");
    ASSERT_EQ(components[1], "2001:db8::1");
    ASSERT_EQ(components[2], "9090");
}

// Test parsing authority with IPv6 address but missing userinfo
TEST(StaticAuthorityParser, IPv6AddressNoUserinfo) {
    const std::string authority = "[2001:db8::1]:9090";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], ""); // No userinfo
    ASSERT_EQ(components[1], "2001:db8::1");
    ASSERT_EQ(components[2], "9090");
}

// Test parsing authority with IPv6 address and no port
TEST(StaticAuthorityParser, IPv6AddressNoPort) {
    const std::string authority = "[2001:db8::1]";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], ""); // No userinfo
    ASSERT_EQ(components[1], "2001:db8::1");
    ASSERT_EQ(components[2], ""); // No port
}

// Test parsing authority with multiple colons in the userinfo
TEST(StaticAuthorityParser, UserinfoWithMultipleColons) {
    const std::string authority = "user:pass:word@host:8080";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], "user:pass:word");
    ASSERT_EQ(components[1], "host");
    ASSERT_EQ(components[2], "8080");
}

// Test parsing authority with userinfo containing special characters
TEST(StaticAuthorityParser, InvalidNonLiteralHost) {
    const std::string authority = "user!#$&'()*+,/:;=?@[^_`{|}~]:password@host:8080";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_FALSE(status);
}

// Test edge case with only a colon and no userinfo, host, or port
TEST(StaticAuthorityParser, OnlyColon) {
    const std::string authority = ":";
    std::vector<std::string> components(3);

    const bool status = AuthorityParser::parse(authority, components);
    ASSERT_TRUE(status);
    ASSERT_EQ(components[0], ""); // No userinfo
    ASSERT_EQ(components[1], ""); // No host
    ASSERT_EQ(components[2], ""); // No port
}
