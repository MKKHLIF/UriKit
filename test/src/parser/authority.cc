#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParseAuthorityWithPath) {
    auto result = Parser::parseAuthority("https://www.google.com/search?q=uri");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "www.google.com");

    result = Parser::parseAuthority("https://user:password@www.example.com:8080/path");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "user:password@www.example.com:8080");
}

TEST(ParserTests, ParseAuthorityWithQuery) {
    auto result = Parser::parseAuthority("https://user:password@www.example.com:8080?query");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "user:password@www.example.com:8080");
}

TEST(ParserTests, ParseAuthorityWithFragment) {
    auto result = Parser::parseAuthority("https://user:password@www.example.com:8080#fragment");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "user:password@www.example.com:8080");
}

TEST(ParserTests, ParseAuthorityOnly) {
    auto result = Parser::parseAuthority("https://www.example.com:8080");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "www.example.com:8080");

    result = Parser::parseAuthority("https://www.example.com");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "www.example.com");

    result = Parser::parseAuthority("https://user:password@www.example.com:8080");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "user:password@www.example.com:8080");

    result = Parser::parseAuthority("https://user:password@www.example.com");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "user:password@www.example.com");
}

TEST(ParserTests, ParseAuthorityWithUnusualCharacters) {
    auto result = Parser::parseAuthority("https://www.amazon.co.uk:80#?/");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "www.amazon.co.uk:80");

    result = Parser::parseAuthority("https://www.amazon.co.uk:80");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "www.amazon.co.uk:80");
}

TEST(ParserTests, ParseAuthorityWithoutAuthority) {
    auto result = Parser::parseAuthority("mailto:user@example.com");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, "");

    result = Parser::parseAuthority("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, "");
}

TEST(ParserTests, ParseAuthorityForNetworkLocation) {
    auto result = Parser::parseAuthority("file://server/share/folder/file.txt");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "server");
}