#include <gtest/gtest.h>
#include <uri/uri.h>

TEST(UriTests, ParseUserInfo) {
    ASSERT_EQ(Uri::parseUserInfo("user:password@www.example.com:8080"), "user:password");
}