#include <gtest/gtest.h>
#include <parser/parser.h>


TEST(ParserTests, ParseAuthorityWithPath)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseAuthority("https://www.google.com/search?q=uri", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "www.google.com");

    result = Parser::parseAuthority("https://user:password@www.example.com:8080/path", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "user:password@www.example.com:8080");
}

TEST(ParserTests, ParseAuthorityWithQuery)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseAuthority("https://user:password@www.example.com:8080?query", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "user:password@www.example.com:8080");
}

TEST(ParserTests, ParseAuthorityWithFragment)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseAuthority("https://user:password@www.example.com:8080#fragment", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "user:password@www.example.com:8080");
}

TEST(ParserTests, ParseAuthorityOnly)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseAuthority("https://www.example.com:8080", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "www.example.com:8080");

    result = Parser::parseAuthority("https://www.example.com", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "www.example.com");

    result = Parser::parseAuthority("https://user:password@www.example.com:8080", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "user:password@www.example.com:8080");

    result = Parser::parseAuthority("https://user:password@www.example.com", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "user:password@www.example.com");
}

TEST(ParserTests, ParseAuthorityWithUnusualCharacters)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseAuthority("https://www.amazon.co.uk:80#?/", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "www.amazon.co.uk:80");

    result = Parser::parseAuthority("https://www.amazon.co.uk:80", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "www.amazon.co.uk:80");
}

TEST(ParserTests, ParseAuthorityWithoutAuthority)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseAuthority("mailto:user@example.com", cursor);
    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "");

    result = Parser::parseAuthority("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf", cursor);
    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "");
}

TEST(ParserTests, ParseAuthorityForNetworkLocation)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseAuthority("file://server/share/folder/file.txt", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "server");
}
