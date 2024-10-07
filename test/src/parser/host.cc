#include <gtest/gtest.h>
#include <uri/uri.h>
#include <parser/parser.h>

TEST(ParserTests, ParseRegisteredHost) {
    auto result = Parser::parseHost("user:password@www.amazon.co.uk:4523");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "www.amazon.co.uk");

    result = Parser::parseHost("user:password@www.amazon.co.uk");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "www.amazon.co.uk");

    result = Parser::parseHost("www.amazon.co.uk:4523");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "www.amazon.co.uk");

    result = Parser::parseHost("www.amazon.co.uk");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "www.amazon.co.uk");
}

TEST(ParserTests, ParseHostIPv4) {
    auto result = Parser::parseHost("user:password@127.0.0.1:4523");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "127.0.0.1");

    result = Parser::parseHost("user:password@127.0.0.1");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "127.0.0.1");

    result = Parser::parseHost("127.0.0.1:4523");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "127.0.0.1");

    result = Parser::parseHost("127.0.0.1");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "127.0.0.1");
}

TEST(ParserTests, ParseHostIPv6) {
    auto result = Parser::parseHost("user:password@[2001:db8::1]:8080");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "[2001:db8::1]");

    result = Parser::parseHost("user:password@[2001:db8::1]");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "[2001:db8::1]");

    result = Parser::parseHost("[2001:db8::1]:8080");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "[2001:db8::1]");

    result = Parser::parseHost("[2001:db8::1]");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "[2001:db8::1]");
}