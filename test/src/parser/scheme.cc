#include <gtest/gtest.h>
#include <uri/uri.h>

TEST(UriTests, ParseScheme) {
    // Test cases for different schemes
    ASSERT_EQ(Uri::parseScheme("https://www.google.com/search?q=uri"), "https");
    ASSERT_EQ(Uri::parseScheme("file:///path/to/file"), "file");
    ASSERT_EQ(Uri::parseScheme("ftp://ftp.example.com"), "ftp");
    ASSERT_EQ(Uri::parseScheme("mailto:user@example.com"), "mailto");
    ASSERT_EQ(Uri::parseScheme("mailto:user@example.com"), "mailto");
}