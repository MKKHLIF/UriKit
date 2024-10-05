#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParseAuthorityWithPath) {
    ASSERT_EQ(Parser::parseAuthority("https://www.google.com/search?q=uri"), "www.google.com");
    ASSERT_EQ(Parser::parseAuthority("https://user:password@www.example.com:8080/path"),
        "user:password@www.example.com:8080");
}

TEST(ParserTests, ParseAuthorityWithQuery) {
    ASSERT_EQ(Parser::parseAuthority("https://user:password@www.example.com:8080?query"),
        "user:password@www.example.com:8080");
}

TEST(ParserTests, ParseAuthorityWithFragment) {
    ASSERT_EQ(Parser::parseAuthority("https://user:password@www.example.com:8080#fragment"),
        "user:password@www.example.com:8080");
}

TEST(ParserTests, ParseAuthorityOnly) {
    ASSERT_EQ(Parser::parseAuthority("https://www.example.com:8080"), "www.example.com:8080");
    ASSERT_EQ(Parser::parseAuthority("https://www.example.com"), "www.example.com");

    ASSERT_EQ(Parser::parseAuthority("https://user:password@www.example.com:8080"),
        "user:password@www.example.com:8080");
    ASSERT_EQ(Parser::parseAuthority("https://user:password@www.example.com"),
        "user:password@www.example.com");
}

TEST(ParserTests, ParseAuthorityWithUnusualCharacters) {
    ASSERT_EQ(Parser::parseAuthority("https://www.amazon.co.uk:80#?/"),
        "www.amazon.co.uk:80");
    ASSERT_EQ(Parser::parseAuthority("https://www.amazon.co.uk:80"),
        "www.amazon.co.uk:80");
}

TEST(ParserTests, ParseAuthorityWithoutAuthority) {
    ASSERT_EQ(Parser::parseAuthority("mailto:user@example.com"), "");
    ASSERT_EQ(Parser::parseAuthority("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf"), "");
}

TEST(ParserTests, ParseAuthorityForNetworkLocation) {
    ASSERT_EQ(Parser::parseAuthority("file://server/share/folder/file.txt"), "server");
}