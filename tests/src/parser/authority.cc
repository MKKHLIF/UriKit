#include <gtest/gtest.h>
#include <uri/uri.h>

TEST(StaticParseHelpers, ParseAuthorityWithPath) {
    const Uri uri;
    bool success = uri.parse("https://www.google.com/search?q=uri");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());

    ASSERT_EQ(uri.getHost(), "www.google.com");
    ASSERT_FALSE(uri.hasPort());

    success = uri.parse("https://user:password@www.example.com:8080/path");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());

    ASSERT_EQ(uri.getUserInfo(), "user:password");
    ASSERT_EQ(uri.getHost(), "www.example.com");
    ASSERT_TRUE(uri.hasPort());
    ASSERT_EQ(uri.getPort(), 8080);
}

TEST(StaticParseHelpers, ParseAuthorityWithQuery) {
    const Uri uri;
    bool success = uri.parse("https://www.google.com/search?q=uri");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getHost(), "www.google.com");
    ASSERT_FALSE(uri.hasPort());

    success = uri.parse("https://user:password@www.example.com:8080?query");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getUserInfo(), "user:password");
    ASSERT_EQ(uri.getHost(), "www.example.com");
    ASSERT_TRUE(uri.hasPort());
    ASSERT_EQ(uri.getPort(), 8080);
}

TEST(StaticParseHelpers, ParseAuthorityWithFragment) {
    const Uri uri;

    const bool success = uri.parse("https://user:password@www.example.com:8080#fragment");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getUserInfo(), "user:password");
    ASSERT_EQ(uri.getHost(), "www.example.com");
    ASSERT_TRUE(uri.hasPort());
    ASSERT_EQ(uri.getPort(), 8080);
}

TEST(StaticParseHelpers, ParseAuthorityOnly) {
    const Uri uri;
    bool success = uri.parse("https://www.google.com");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getHost(), "www.google.com");
    ASSERT_FALSE(uri.hasPort());

    success = uri.parse("https://user:password@www.example.com:8080");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getUserInfo(), "user:password");
    ASSERT_EQ(uri.getHost(), "www.example.com");
    ASSERT_TRUE(uri.hasPort());
    ASSERT_EQ(uri.getPort(), 8080);
}

TEST(StaticParseHelpers, ParseAuthorityHostIPv4) {
    const Uri uri;
    bool success = uri.parse("https://user:password@127.0.0.1:4523");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getUserInfo(), "user:password");
    ASSERT_EQ(uri.getHost(), "127.0.0.1");
    ASSERT_TRUE(uri.hasPort());
    ASSERT_EQ(uri.getPort(), 4523);

    success = uri.parse("https://user:password@127.0.0.1");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getUserInfo(), "user:password");
    ASSERT_EQ(uri.getHost(), "127.0.0.1");
    ASSERT_FALSE(uri.hasPort());
}

TEST(StaticParseHelpers, ParseHostIPv6) {
    const Uri uri;
    bool success = uri.parse("https://[2001:db8::1]:8080");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getHost(), "2001:db8::1");
    ASSERT_TRUE(uri.hasPort());
    ASSERT_EQ(uri.getPort(), 8080);

    success = uri.parse("https://user:password@[2001:db8::1]:8080");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getUserInfo(), "user:password");
    ASSERT_EQ(uri.getHost(), "2001:db8::1");
    ASSERT_TRUE(uri.hasPort());
    ASSERT_EQ(uri.getPort(), 8080);

    success = uri.parse("https://[2001:db8::1]");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getHost(), "2001:db8::1");
    ASSERT_FALSE(uri.hasPort());
}


TEST(StaticParseHelpers, ParseAuthorityWithUnusualCharacters) {
    const Uri uri;
    bool success = uri.parse("https://www.amazon.co.uk:80#?/");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getHost(), "www.amazon.co.uk");
    ASSERT_TRUE(uri.hasPort());
    ASSERT_EQ(uri.getPort(), 80);

    success = uri.parse("https://www.amazon.co.uk:80");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getHost(), "www.amazon.co.uk");
    ASSERT_TRUE(uri.hasPort());
    ASSERT_EQ(uri.getPort(), 80);
}

TEST(StaticParseHelpers, ParseAuthorityWithoutAuthority) {
    const Uri uri;
    bool success = uri.parse("mailto:user@example.com");
    ASSERT_TRUE(success);
    ASSERT_FALSE(uri.hasAuthority());

    success = uri.parse("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf");
    ASSERT_TRUE(success);
    ASSERT_FALSE(uri.hasAuthority());
}

TEST(StaticParseHelpers, ParseAuthorityForNetworkLocation) {
    const Uri uri;
    bool success = uri.parse("file://server/share/folder/file.txt");
    ASSERT_TRUE(success);
    ASSERT_TRUE(uri.hasAuthority());
    ASSERT_EQ(uri.getHost(), "server");
}
