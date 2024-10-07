
#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParsePortRegisteredHost) {
    const std::string default_port = "80";

    auto result = Parser::parsePort("www.amazon.co.uk:4523");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "4523");

    result = Parser::parsePort("www.amazon.co.uk");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, default_port);

    result = Parser::parsePort("user:password@www.amazon.co.uk:4523");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "4523");

    result = Parser::parsePort("user:password@www.amazon.co.uk");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, default_port);
}

TEST(ParserTests, ParsePortIPv4Host) {
    const std::string default_port = "80";

    auto result = Parser::parsePort("127.0.0.1:4523");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "4523");

    result = Parser::parsePort("127.0.0.1");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, default_port);

    result = Parser::parsePort("user:password@127.0.0.1:4523");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "4523");

    result = Parser::parsePort("user:password@127.0.0.1");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, default_port);
}

TEST(ParserTests, ParsePortIPv6Host) {
    const std::string default_port = "80";

    auto result = Parser::parsePort("[2001:db8::1]:8080");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "8080");

    result = Parser::parsePort("[2001:db8::1]");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, default_port);

    result = Parser::parsePort("user:password@[2001:db8::1]:8080");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, "8080");

    result = Parser::parsePort("user:password@[2001:db8::1]");
    ASSERT_FALSE(result.status);
    ASSERT_EQ(result.content, default_port);
}