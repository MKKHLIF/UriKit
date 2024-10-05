#include <gtest/gtest.h>
#include <parser/parser_engine.h>

TEST(ParserEngineTests, ParseUserInfo) {
    ASSERT_EQ(ParserEngine::parseUserInfo("user:password@www.example.com:8080"), "user:password");
}