#include <gtest/gtest.h>
#include <uri/uri.h>

TEST(UriTests, ParseAuthorityWithPath) {
    ASSERT_EQ(prism::Uri::parseAuthority("https://www.google.com/search?q=uri"), "www.google.com");
    ASSERT_EQ(prism::Uri::parseAuthority("https://user:password@www.example.com:8080/path"),
        "user:password@www.example.com:8080");
}

TEST(UriTests, ParseAuthorityWithQuery) {
    ASSERT_EQ(prism::Uri::parseAuthority("https://user:password@www.example.com:8080?query"),
        "user:password@www.example.com:8080");
}

TEST(UriTests, ParseAuthorityWithFragment) {
    ASSERT_EQ(prism::Uri::parseAuthority("https://user:password@www.example.com:8080#fragment"),
        "user:password@www.example.com:8080");
}

TEST(UriTests, ParseAuthorityOnly) {
    ASSERT_EQ(prism::Uri::parseAuthority("https://www.example.com:8080"), "www.example.com:8080");
    ASSERT_EQ(prism::Uri::parseAuthority("https://user:password@www.example.com:8080"),
        "user:password@www.example.com:8080");
}

TEST(UriTests, ParseAuthorityWithUnusualCharacters) {
    ASSERT_EQ(prism::Uri::parseAuthority("https://www.amazon.co.uk:80#?/"),
        "www.amazon.co.uk:80");
}

TEST(UriTests, ParseAuthorityWithoutAuthority) {
    ASSERT_EQ(prism::Uri::parseAuthority("mailto:user@example.com"), "");
    ASSERT_EQ(prism::Uri::parseAuthority("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf"), "");
}

TEST(UriTests, ParseAuthorityForNetworkLocation) {
    ASSERT_EQ(prism::Uri::parseAuthority("file://server/share/folder/file.txt"), "server");
}