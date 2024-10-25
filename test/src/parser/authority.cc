#include <gtest/gtest.h>
#include "parser_engine.h"


TEST(StaticParseHelpers, ParseAuthorityWithPath) {
    // const Uri uri;
    // bool success = uri.parse("https://www.google.com/search?q=uri");
    // ASSERT_TRUE(success);
    // ASSERT_TRUE(uri.hasAuthority());
    //
    // ASSERT_EQ(uri.getHost(), "www.google.com");
    // ASSERT_FALSE(uri.hasPort());
    //
    // success = uri.parse("https://user:password@www.example.com:8080/path");
    // ASSERT_TRUE(success);
    // ASSERT_TRUE(uri.hasAuthority());
    //
    // ASSERT_EQ(uri.getUserInfo(), "user:password");
    // ASSERT_EQ(uri.getHost(), "www.example.com");
    // ASSERT_TRUE(uri.hasPort());
    // ASSERT_EQ(uri.getPort(), 8080);
}

TEST(StaticParseHelpers, ParseAuthorityWithQuery) {
    // constexpr size_t cursor = 0;
    //
    // auto result = Parser::parseAuthority("https://user:password@www.example.com:8080?query", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "user:password@www.example.com:8080");
}

TEST(StaticParseHelpers, ParseAuthorityWithFragment) {
    // constexpr size_t cursor = 0;
    //
    // auto result = Parser::parseAuthority("https://user:password@www.example.com:8080#fragment", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "user:password@www.example.com:8080");
}

TEST(StaticParseHelpers, ParseAuthorityOnly) {
    // constexpr size_t cursor = 0;
    //
    // auto result = Parser::parseAuthority("https://www.example.com:8080", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "www.example.com:8080");
    //
    // result = Parser::parseAuthority("https://www.example.com", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "www.example.com");
    //
    // result = Parser::parseAuthority("https://user:password@www.example.com:8080", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "user:password@www.example.com:8080");
    //
    // result = Parser::parseAuthority("https://user:password@www.example.com", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "user:password@www.example.com");
}

TEST(StaticParseHelpers, ParseAuthorityWithUnusualCharacters) {
    // constexpr size_t cursor = 0;
    //
    // auto result = Parser::parseAuthority("https://www.amazon.co.uk:80#?/", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "www.amazon.co.uk:80");
    //
    // result = Parser::parseAuthority("https://www.amazon.co.uk:80", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "www.amazon.co.uk:80");
}

TEST(StaticParseHelpers, ParseAuthorityWithoutAuthority) {
    // constexpr size_t cursor = 0;
    //
    // auto result = Parser::parseAuthority("mailto:user@example.com", cursor);
    // ASSERT_FALSE(result.error);
    // ASSERT_EQ(result.content, "");
    //
    // result = Parser::parseAuthority("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf", cursor);
    // ASSERT_FALSE(result.error);
    // ASSERT_EQ(result.content, "");
}

TEST(StaticParseHelpers, ParseAuthorityForNetworkLocation) {
    // constexpr size_t cursor = 0;
    //
    // auto result = Parser::parseAuthority("file://server/share/folder/file.txt", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "server");
}
