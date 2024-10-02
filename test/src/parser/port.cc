//
#include <gtest/gtest.h>
#include <uri/uri.h>

TEST(UriTests, ParsePortRegistredHost) {
    const std::string default_port = "80";
    ASSERT_EQ(prism::Uri::parsePort("www.amazon.co.uk:4523"), "4523");
    ASSERT_EQ(prism::Uri::parsePort("www.amazon.co.uk"), default_port);

    ASSERT_EQ(prism::Uri::parsePort("user:password@www.amazon.co.uk:4523"), "4523");
    ASSERT_EQ(prism::Uri::parsePort("user:password@www.amazon.co.uk"), default_port);
}

TEST(UriTests, ParsePortIPv4Host) {
    const std::string default_port = "80";

    ASSERT_EQ(prism::Uri::parsePort("127.0.0.1:4523"), "4523");
    ASSERT_EQ(prism::Uri::parsePort("127.0.0.1"), default_port);

    ASSERT_EQ(prism::Uri::parsePort("user:password@127.0.0.1:4523"), "4523");
    ASSERT_EQ(prism::Uri::parsePort("user:password@127.0.0.1"), default_port);
}

TEST(UriTests, ParsePortIPv6Host) {
    const std::string default_port = "80";

    ASSERT_EQ(prism::Uri::parsePort("[2001:db8::1]:8080"), "8080");
    ASSERT_EQ(prism::Uri::parsePort("[2001:db8::1]"), default_port);

    ASSERT_EQ(prism::Uri::parsePort("user:password@[2001:db8::1]:8080"), "8080");
    ASSERT_EQ(prism::Uri::parsePort("user:password@[2001:db8::1]"), default_port);
}