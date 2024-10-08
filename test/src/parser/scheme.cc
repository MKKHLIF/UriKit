#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParseScheme)
{
    // Test cases for different schemes
    constexpr size_t cursor = 0;
    auto result = Parser::parseScheme("https://www.google.com/search?q=uri", cursor);
    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "https");

    result = Parser::parseScheme("file:///path/to/file", cursor);
    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "file");

    result = Parser::parseScheme("ftp://ftp.example.com", cursor);
    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "ftp");

    result = Parser::parseScheme("mailto:user@example.com", cursor);
    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "mailto");
}

TEST(ParserTests, NoScheme)
{
    size_t cursor = 0;
    const auto result = Parser::parseScheme("www.example.com", cursor);
    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "");
}

TEST(ParserTests, EmptyUriScheme)
{
    size_t cursor = 0;
    const auto result = Parser::parseScheme("", cursor);
    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "");
}

TEST(ParserTests, SchemeCaseSensitive)
{
    size_t cursor = 0;
    const auto result = Parser::parseScheme("hTTps://www.google.com/", cursor);
    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "https");
}

TEST(ParserTests, SchemeNotAllowedCharacters)
{
    size_t cursor = 0;
    auto result = Parser::parseScheme("++hTTps://www.google.com/", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "");

    result = Parser::parseScheme("hT---+Tps://www.google.com/", cursor);

    ASSERT_FALSE(result.error);
    ASSERT_EQ(result.content, "ht---+tps");
}
