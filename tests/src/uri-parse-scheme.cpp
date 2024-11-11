#include <gtest/gtest.h>
#include <uri/uri.h>

TEST(UriParseScheme, ParseScheme) {
    const Uri uri;
    bool success = uri.parse("https://www.google.com/search?q=uri");
    ASSERT_TRUE(success);
    ASSERT_EQ(uri.getScheme(), "https");

    success = uri.parse("file:///path/to/file");
    ASSERT_TRUE(success);
    ASSERT_EQ(uri.getScheme(), "file");

    success = uri.parse("ftp://ftp.example.com");
    ASSERT_TRUE(success);
    ASSERT_EQ(uri.getScheme(), "ftp");

    success = uri.parse("mailto:user@example.com");
    ASSERT_TRUE(success);
    ASSERT_EQ(uri.getScheme(), "mailto");
}


TEST(UriParseScheme, NoScheme) {
    const Uri uri;
    const bool success = uri.parse("foo/bar");
    ASSERT_TRUE(success);
    ASSERT_EQ(uri.getScheme(), "");
}

TEST(UriParseScheme, EmptyUriScheme) {
    const Uri uri;
    const bool success = uri.parse("");
    ASSERT_TRUE(success);
    ASSERT_EQ(uri.getScheme(), "");
}

TEST(UriParseScheme, SchemeCaseSensitive) {
    const Uri uri;
    const bool success = uri.parse("hTTps://www.google.com/");
    ASSERT_TRUE(success);
    ASSERT_EQ(uri.getScheme(), "https");
}

TEST(UriParseScheme, SchemeNotAllowedCharacters) {
    const Uri uri;
    bool success = uri.parse("++hTTps://www.google.com/");
    ASSERT_FALSE(success);
    ASSERT_EQ(uri.getScheme(), "");

    success = uri.parse("hT---+Tps://www.google.com/");

    ASSERT_TRUE(success);
    ASSERT_EQ(uri.getScheme(), "ht---+tps");
}
