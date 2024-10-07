#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParseUserInfo) {
	auto result = Parser::parseUserInfo("user:password@www.example.com:8080");
	ASSERT_TRUE(result.status);
	ASSERT_EQ(result.content, "user:password");
}