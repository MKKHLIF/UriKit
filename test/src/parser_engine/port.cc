//
#include <gtest/gtest.h>
#include <parser/parser_engine.h>

TEST(ParserEngineTests, ParsePortRegistredHost) {
    
    /*const std::string default_port = "80";
    ASSERT_EQ(Parser::parsePort("www.amazon.co.uk:4523"), "4523");
    ASSERT_EQ(Parser::parsePort("www.amazon.co.uk"), default_port);

    ASSERT_EQ(Parser::parsePort("user:password@www.amazon.co.uk:4523"), "4523");
    ASSERT_EQ(Parser::parsePort("user:password@www.amazon.co.uk"), default_port);*/
}

TEST(ParserEngineTests, ParsePortIPv4Host) {
   /* const std::string default_port = "80";

    ASSERT_EQ(Parser::parsePort("127.0.0.1:4523"), "4523");
    ASSERT_EQ(Parser::parsePort("127.0.0.1"), default_port);

    ASSERT_EQ(Parser::parsePort("user:password@127.0.0.1:4523"), "4523");
    ASSERT_EQ(Parser::parsePort("user:password@127.0.0.1"), default_port);*/
}

TEST(ParserEngineTests, ParsePortIPv6Host) {
   /* const std::string default_port = "80";

    ASSERT_EQ(Parser::parsePort("[2001:db8::1]:8080"), "8080");
    ASSERT_EQ(Parser::parsePort("[2001:db8::1]"), default_port);

    ASSERT_EQ(Parser::parsePort("user:password@[2001:db8::1]:8080"), "8080");
    ASSERT_EQ(Parser::parsePort("user:password@[2001:db8::1]"), default_port);*/
}