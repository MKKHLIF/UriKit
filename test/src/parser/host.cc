#include <gtest/gtest.h>
#include <uri/uri.h>
#include "parser_engine.h"

TEST(StaticParseHelpers, ParseRegisteredHost)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseHost("user:password@www.amazon.co.uk:4523", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "www.amazon.co.uk");

    result = Parser::parseHost("user:password@www.amazon.co.uk", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "www.amazon.co.uk");

    result = Parser::parseHost("www.amazon.co.uk:4523", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "www.amazon.co.uk");

    result = Parser::parseHost("www.amazon.co.uk", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "www.amazon.co.uk");
}

TEST(StaticParseHelpers, ParseHostIPv4)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseHost("user:password@127.0.0.1:4523", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "127.0.0.1");

    result = Parser::parseHost("user:password@127.0.0.1", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "127.0.0.1");

    result = Parser::parseHost("127.0.0.1:4523", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "127.0.0.1");

    result = Parser::parseHost("127.0.0.1", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "127.0.0.1");
}

TEST(StaticParseHelpers, ParseHostIPv6)
{
    constexpr size_t cursor = 0;

    auto result = Parser::parseHost("user:password@[2001:db8::1]:8080", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "[2001:db8::1]");

    result = Parser::parseHost("user:password@[2001:db8::1]", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "[2001:db8::1]");

    result = Parser::parseHost("[2001:db8::1]:8080", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "[2001:db8::1]");

    result = Parser::parseHost("[2001:db8::1]", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, "[2001:db8::1]");
}
