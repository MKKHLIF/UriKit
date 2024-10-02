#include <gtest/gtest.h>
#include <uri/uri.h>

TEST(UriTests, ParseScheme) {
    // Test cases for different schemes
    ASSERT_EQ(prism::Uri::parseScheme("https://www.google.com/search?q=uri"), "https");
    ASSERT_EQ(prism::Uri::parseScheme("file:///path/to/file"), "file");
    ASSERT_EQ(prism::Uri::parseScheme("ftp://ftp.example.com"), "ftp");
    ASSERT_EQ(prism::Uri::parseScheme("mailto:user@example.com"), "mailto");
}