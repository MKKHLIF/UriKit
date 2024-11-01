#include <gtest/gtest.h>
#include <uri/uri.h>

TEST(StaticParseHelpers, ParseRegisteredHost) {
    // constexpr size_t cursor = 0;
    //
    // auto result = Parser::parseHost("user:password@www.amazon.co.uk:4523", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "www.amazon.co.uk");
    //
    // result = Parser::parseHost("user:password@www.amazon.co.uk", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "www.amazon.co.uk");
    //
    // result = Parser::parseHost("www.amazon.co.uk:4523", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "www.amazon.co.uk");
    //
    // result = Parser::parseHost("www.amazon.co.uk", cursor);
    // ASSERT_TRUE(result.error);
    // ASSERT_EQ(result.content, "www.amazon.co.uk");
}


