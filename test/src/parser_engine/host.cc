#include <gtest/gtest.h>
#include <uri/uri.h>
#include <parser/parser_engine.h>

TEST(ParserEngineTests, ParseRegistredHost) {
    ASSERT_EQ(ParserEngine::parseHost("user:password@www.amazon.co.uk:4523"), "www.amazon.co.uk");
    ASSERT_EQ(ParserEngine::parseHost("user:password@www.amazon.co.uk"), "www.amazon.co.uk");

    ASSERT_EQ(ParserEngine::parseHost("www.amazon.co.uk:4523"), "www.amazon.co.uk");
    ASSERT_EQ(ParserEngine::parseHost("www.amazon.co.uk"), "www.amazon.co.uk");
}

TEST(ParserEngineTests, ParseHostIPv4) {
    ASSERT_EQ(ParserEngine::parseHost("user:password@127.0.0.1:4523"), "127.0.0.1");
    ASSERT_EQ(ParserEngine::parseHost("user:password@127.0.0.1"), "127.0.0.1");

    ASSERT_EQ(ParserEngine::parseHost("127.0.0.1:4523"), "127.0.0.1");
    ASSERT_EQ(ParserEngine::parseHost("127.0.0.1"), "127.0.0.1");
}

TEST(ParserEngineTests, ParseHostIPv6) {
    ASSERT_EQ(ParserEngine::parseHost("user:password@[2001:db8::1]:8080"), "[2001:db8::1]");
    ASSERT_EQ(ParserEngine::parseHost("user:password@[2001:db8::1]"), "[2001:db8::1]");

    ASSERT_EQ(ParserEngine::parseHost("[2001:db8::1]:8080"), "[2001:db8::1]");
    ASSERT_EQ(ParserEngine::parseHost("[2001:db8::1]"), "[2001:db8::1]");
}