#include <gtest/gtest.h>
#include "scheme-parser.h"

TEST(StaticSchemeParser, HappyScenario) {
    std::string scheme;
    std::string uri;

    uri = "https://www.google.com";
    const bool status_https = SchemeParser::parse(uri, scheme);
    ASSERT_TRUE(status_https);
    ASSERT_EQ(scheme, "https");
    ASSERT_EQ(uri, "www.google.com");

    uri = "ftp://ftp.gnu.org";
    const bool status_ftp = SchemeParser::parse(uri, scheme);
    ASSERT_TRUE(status_ftp);
    ASSERT_EQ(scheme, "ftp");
    ASSERT_EQ(uri, "ftp.gnu.org");

    uri = "mailto:someone@example.com";
    const bool status_mailto = SchemeParser::parse(uri, scheme);
    ASSERT_TRUE(status_mailto);
    ASSERT_EQ(scheme, "mailto");
    ASSERT_EQ(uri, "someone@example.com");

    uri = "file:///home/user/file.txt";
    const bool status_file = SchemeParser::parse(uri, scheme);
    ASSERT_TRUE(status_file);
    ASSERT_EQ(scheme, "file");
    ASSERT_EQ(uri, "/home/user/file.txt");

    uri = "tel:+1234567890";
    const bool status_tel = SchemeParser::parse(uri, scheme);
    ASSERT_TRUE(status_tel);
    ASSERT_EQ(scheme, "tel");
    ASSERT_EQ(uri, "+1234567890");

    uri = "data:text/plain;base64,SGVsbG8gd29ybGQ=";
    const bool status_data = SchemeParser::parse(uri, scheme);
    ASSERT_TRUE(status_data);
    ASSERT_EQ(scheme, "data");
    ASSERT_EQ(uri, "text/plain;base64,SGVsbG8gd29ybGQ=");

    uri = "ldap://ldap.example.com";
    const bool status_ldap = SchemeParser::parse(uri, scheme);
    ASSERT_TRUE(status_ldap);
    ASSERT_EQ(scheme, "ldap");
    ASSERT_EQ(uri, "ldap.example.com");
}

TEST(StaticSchemeParser, MissingScheme) {
    std::string scheme;
    std::string uri = "www.google.com";
    const bool status_no_scheme = SchemeParser::parse(uri, scheme);

    // "Assuming a relative reference."
    ASSERT_TRUE(status_no_scheme);
    ASSERT_EQ(uri, "www.google.com");
}

TEST(StaticSchemeParser, MissingDelimiter) {
    std::string scheme;
    std::string uri = "http//example.com";
    const bool status_missing_delim = SchemeParser::parse(uri, scheme);

    // "Assuming a relative reference."
    ASSERT_TRUE(status_missing_delim);
    ASSERT_EQ(uri, "http//example.com");
}

TEST(StaticSchemeParser, InvalidCharactersInScheme) {
    std::string scheme;
    std::string uri = "htt@p://example.com";
    const bool status_invalid_chars_in_scheme = SchemeParser::parse(uri, scheme);
    ASSERT_FALSE(status_invalid_chars_in_scheme) << "Expected failure due to invalid characters in the scheme.";
}
