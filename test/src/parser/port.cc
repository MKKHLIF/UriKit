
#include <gtest/gtest.h>
#include "parser_engine.h"

TEST(StaticParseHelpers, ParsePortRegisteredHost)
{
    // size_t cursor = 0;
    // const std::string default_port = "80";
    //
    // auto result = Parser::parsePort("www.amazon.co.uk:4523", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "4523");
    //
    // result = Parser::parsePort("www.amazon.co.uk", cursor);
    // ASSERT_FALSE(result.error);
    // ASSERT_EQ(result.content, default_port);
    //
    // result = Parser::parsePort("user:password@www.amazon.co.uk:4523", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "4523");
    //
    // result = Parser::parsePort("user:password@www.amazon.co.uk", cursor);
    // ASSERT_FALSE(result.error);
    // ASSERT_EQ(result.content, default_port);
}

TEST(StaticParseHelpers, ParsePortIPv4Host)
{
    // size_t cursor = 0;
    //
    // const std::string default_port = "80";
    //
    // auto result = Parser::parsePort("127.0.0.1:4523", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "4523");
    //
    // result = Parser::parsePort("127.0.0.1", cursor);
    // ASSERT_FALSE(result.error);
    // ASSERT_EQ(result.content, default_port);
    //
    // result = Parser::parsePort("user:password@127.0.0.1:4523", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "4523");
    //
    // result = Parser::parsePort("user:password@127.0.0.1", cursor);
    // ASSERT_FALSE(result.error);
    // ASSERT_EQ(result.content, default_port);
}

TEST(StaticParseHelpers, ParsePortIPv6Host)
{
    // size_t cursor = 0;
    //
    // const std::string default_port = "80";
    //
    // auto result = Parser::parsePort("[2001:db8::1]:8080", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "8080");
    //
    // result = Parser::parsePort("[2001:db8::1]", cursor);
    // ASSERT_FALSE(result.error);
    // ASSERT_EQ(result.content, default_port);
    //
    // result = Parser::parsePort("user:password@[2001:db8::1]:8080", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "8080");
    //
    // result = Parser::parsePort("user:password@[2001:db8::1]", cursor);
    // ASSERT_FALSE(result.error);
    // ASSERT_EQ(result.content, default_port);
}
