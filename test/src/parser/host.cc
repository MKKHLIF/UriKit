#include <gtest/gtest.h>
#include <uri/uri.h>


TEST(UriTests, ParseRegistredHost) {
    ASSERT_EQ(Uri::parseHost("user:password@www.amazon.co.uk:4523"), "www.amazon.co.uk");
    ASSERT_EQ(Uri::parseHost("user:password@www.amazon.co.uk"), "www.amazon.co.uk");

    ASSERT_EQ(Uri::parseHost("www.amazon.co.uk:4523"), "www.amazon.co.uk");
    ASSERT_EQ(Uri::parseHost("www.amazon.co.uk"), "www.amazon.co.uk");
}

TEST(UriTests, ParseHostIPv4) {
    ASSERT_EQ(Uri::parseHost("user:password@127.0.0.1:4523"), "127.0.0.1");
    ASSERT_EQ(Uri::parseHost("user:password@127.0.0.1"), "127.0.0.1");

    ASSERT_EQ(Uri::parseHost("127.0.0.1:4523"), "127.0.0.1");
    ASSERT_EQ(Uri::parseHost("127.0.0.1"), "127.0.0.1");
}

TEST(UriTests, ParseHostIPv6) {
    ASSERT_EQ(Uri::parseHost("user:password@[2001:db8::1]:8080"), "[2001:db8::1]");
    ASSERT_EQ(Uri::parseHost("user:password@[2001:db8::1]"), "[2001:db8::1]");

    ASSERT_EQ(Uri::parseHost("[2001:db8::1]:8080"), "[2001:db8::1]");
    ASSERT_EQ(Uri::parseHost("[2001:db8::1]"), "[2001:db8::1]");
}