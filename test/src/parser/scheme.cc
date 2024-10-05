#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParseScheme) {
    // Test cases for different schemes
    ASSERT_EQ(Parser::parseScheme("https://www.google.com/search?q=uri"), "https");
    ASSERT_EQ(Parser::parseScheme("file:///path/to/file"), "file");
    ASSERT_EQ(Parser::parseScheme("ftp://ftp.example.com"), "ftp");
    ASSERT_EQ(Parser::parseScheme("mailto:user@example.com"), "mailto");
    ASSERT_EQ(Parser::parseScheme("mailto:user@example.com"), "mailto");
}