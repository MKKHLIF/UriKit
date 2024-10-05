#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParseUserInfo) {
    ASSERT_EQ(Parser::parseUserInfo("user:password@www.example.com:8080"), "user:password");
}