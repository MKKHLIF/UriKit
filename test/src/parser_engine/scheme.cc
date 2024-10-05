#include <gtest/gtest.h>
#include <parser/parser_engine.h>

TEST(ParserEngineTests, ParseScheme) {
    // Test cases for different schemes
    ASSERT_EQ(ParserEngine::parseScheme("https://www.google.com/search?q=uri"), "https");
    ASSERT_EQ(ParserEngine::parseScheme("file:///path/to/file"), "file");
    ASSERT_EQ(ParserEngine::parseScheme("ftp://ftp.example.com"), "ftp");
    ASSERT_EQ(ParserEngine::parseScheme("mailto:user@example.com"), "mailto");
    ASSERT_EQ(ParserEngine::parseScheme("mailto:user@example.com"), "mailto");
}