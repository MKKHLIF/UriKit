#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParseScheme) {
    // Test cases for different schemes
    auto result = Parser::parseScheme("https://www.google.com/search?q=uri");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "https");

    result = Parser::parseScheme("file:///path/to/file");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "file");

    result = Parser::parseScheme("ftp://ftp.example.com");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "ftp");

    result = Parser::parseScheme("mailto:user@example.com");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "mailto");

    // Test case for URI without scheme
    result = Parser::parseScheme("www.example.com");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, "");

    // Test case for empty string
    result = Parser::parseScheme("");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, "");
}