#include <gtest/gtest.h>
#include <uri/uri.h>
#include <parser/parser.h>

TEST(ParserTests, ParseRegistredHost) {
    ASSERT_EQ(Parser::parseHost("user:password@www.amazon.co.uk:4523"), "www.amazon.co.uk");
    ASSERT_EQ(Parser::parseHost("user:password@www.amazon.co.uk"), "www.amazon.co.uk");

    ASSERT_EQ(Parser::parseHost("www.amazon.co.uk:4523"), "www.amazon.co.uk");
    ASSERT_EQ(Parser::parseHost("www.amazon.co.uk"), "www.amazon.co.uk");
}

TEST(ParserTests, ParseHostIPv4) {
    ASSERT_EQ(Parser::parseHost("user:password@127.0.0.1:4523"), "127.0.0.1");
    ASSERT_EQ(Parser::parseHost("user:password@127.0.0.1"), "127.0.0.1");

    ASSERT_EQ(Parser::parseHost("127.0.0.1:4523"), "127.0.0.1");
    ASSERT_EQ(Parser::parseHost("127.0.0.1"), "127.0.0.1");
}

TEST(ParserTests, ParseHostIPv6) {
    ASSERT_EQ(Parser::parseHost("user:password@[2001:db8::1]:8080"), "[2001:db8::1]");
    ASSERT_EQ(Parser::parseHost("user:password@[2001:db8::1]"), "[2001:db8::1]");

    ASSERT_EQ(Parser::parseHost("[2001:db8::1]:8080"), "[2001:db8::1]");
    ASSERT_EQ(Parser::parseHost("[2001:db8::1]"), "[2001:db8::1]");
}