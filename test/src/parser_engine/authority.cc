#include <gtest/gtest.h>
#include <parser/parser_engine.h>

TEST(ParserEngineTests, ParseAuthorityWithPath) {
    ASSERT_EQ(ParserEngine::parseAuthority("https://www.google.com/search?q=uri"), "www.google.com");
    ASSERT_EQ(ParserEngine::parseAuthority("https://user:password@www.example.com:8080/path"),
        "user:password@www.example.com:8080");
}

TEST(ParserEngineTests, ParseAuthorityWithQuery) {
    ASSERT_EQ(ParserEngine::parseAuthority("https://user:password@www.example.com:8080?query"),
        "user:password@www.example.com:8080");
}

TEST(ParserEngineTests, ParseAuthorityWithFragment) {
    ASSERT_EQ(ParserEngine::parseAuthority("https://user:password@www.example.com:8080#fragment"),
        "user:password@www.example.com:8080");
}

TEST(ParserEngineTests, ParseAuthorityOnly) {
    ASSERT_EQ(ParserEngine::parseAuthority("https://www.example.com:8080"), "www.example.com:8080");
    ASSERT_EQ(ParserEngine::parseAuthority("https://www.example.com"), "www.example.com");

    ASSERT_EQ(ParserEngine::parseAuthority("https://user:password@www.example.com:8080"),
        "user:password@www.example.com:8080");
    ASSERT_EQ(ParserEngine::parseAuthority("https://user:password@www.example.com"),
        "user:password@www.example.com");
}

TEST(ParserEngineTests, ParseAuthorityWithUnusualCharacters) {
    ASSERT_EQ(ParserEngine::parseAuthority("https://www.amazon.co.uk:80#?/"),
        "www.amazon.co.uk:80");
    ASSERT_EQ(ParserEngine::parseAuthority("https://www.amazon.co.uk:80"),
        "www.amazon.co.uk:80");
}

TEST(ParserEngineTests, ParseAuthorityWithoutAuthority) {
    ASSERT_EQ(ParserEngine::parseAuthority("mailto:user@example.com"), "");
    ASSERT_EQ(ParserEngine::parseAuthority("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf"), "");
}

TEST(ParserEngineTests, ParseAuthorityForNetworkLocation) {
    ASSERT_EQ(ParserEngine::parseAuthority("file://server/share/folder/file.txt"), "server");
}