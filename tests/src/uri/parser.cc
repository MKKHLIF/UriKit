#include <gtest/gtest.h>
#include <uri/uri.h>
//
TEST(UriTests, parseNoScheme) {
    const Uri uri;
    const bool success = uri.parse("foo/bar");
    ASSERT_TRUE(success);
    ASSERT_EQ("", uri.getScheme());
    ASSERT_EQ(
        (std::vector< std::string >{
            "foo",
            "bar",
            }),
        uri.getPath()
    );
}


TEST(UriTests, parseUrl) {
    const Uri uri;
    ASSERT_TRUE(uri.parse("http://www.example.com/foo/bar"));
    ASSERT_EQ("http", uri.getScheme());
    ASSERT_EQ("www.example.com", uri.getHost());
    ASSERT_EQ(
        (std::vector< std::string >{
            "",
            "foo",
            "bar",
            }),
        uri.getPath()
    );
}

// TEST(UriTests, parseUrnDefaultPathDelimiter) {
//     const Uri uri;
//     ASSERT_TRUE(uri.parse("urn:book:fantasy:Hobbit"));
//     ASSERT_EQ("urn", uri.getScheme());
//     ASSERT_EQ("", uri.getHost());
//     ASSERT_EQ(
//         (std::vector< std::string >{
//             "book:fantasy:Hobbit",
//             }),
//         uri.getPath()
//     );
// }

// TEST(UriTests, parsePathCornerCases)
// {
//     struct TestVector
//     {
//         std::string pathIn;
//         std::vector<std::string> pathOut;
//     };
//     const std::vector<TestVector> testVectors{
//         {"", {}},
//         {"/", {""}},
//         {"/foo", {"", "foo"}},
//         {"foo/", {"foo", ""}},
//     };
//     size_t index = 0;
//     for (const auto& [pathIn, pathOut] : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(pathIn)) << index;
//         ASSERT_EQ(pathOut, uri.getPath()) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseHasAPortNumber)
// {
//     const Uri uri;
//     ASSERT_TRUE(uri.parse("http://www.example.com:8080/foo/bar"));
//     ASSERT_EQ("www.example.com", uri.getHost());
//     ASSERT_TRUE(uri.hasPort());
//     ASSERT_EQ(8080, uri.getPort());
// }
//
// TEST(UriTests, parseDoesNotHaveAPortNumber)
// {
//     const Uri uri;
//     ASSERT_TRUE(uri.parse("http://www.example.com/foo/bar"));
//     ASSERT_EQ("www.example.com", uri.getHost());
//     ASSERT_FALSE(uri.hasPort());
// }
//
// TEST(UriTests, parseTwiceFirstWithPortNumberThenWithout)
// {
//     const Uri uri;
//     ASSERT_TRUE(uri.parse("http://www.example.com:8080/foo/bar"));
//     ASSERT_TRUE(uri.parse("http://www.example.com/foo/bar"));
//     ASSERT_FALSE(uri.hasPort());
// }
//
// TEST(UriTests, parseBadPortNumberPurelyAlphabetic)
// {
//     const Uri uri;
//     ASSERT_FALSE(uri.parse("http://www.example.com:spam/foo/bar"));
// }
//
// TEST(UriTests, parseBadPortNumberStartsNumericEndsAlphabetic)
// {
//     const Uri uri;
//     ASSERT_FALSE(uri.parse("http://www.example.com:8080spam/foo/bar"));
// }
//
// TEST(UriTests, parseLargestValidPortNumber)
// {
//     const Uri uri;
//     ASSERT_TRUE(uri.parse("http://www.example.com:65535/foo/bar"));
//     ASSERT_TRUE(uri.hasPort());
//     ASSERT_EQ(65535, uri.getPort());
// }
//
// TEST(UriTests, parseBadPortNumberTooBig)
// {
//     Uri uri;
//     ASSERT_FALSE(uri.parse("http://www.example.com:65536/foo/bar"));
// }
//
// TEST(UriTests, parseBadPortNumberNegative)
// {
//     Uri uri;
//     ASSERT_FALSE(uri.parse("http://www.example.com:-1234/foo/bar"));
// }
//
// TEST(UriTests, parseEndsAfterAuthority)
// {
//     Uri uri;
//     ASSERT_TRUE(uri.parse("http://www.example.com"));
// }
//
// TEST(UriTests, parseRelativeVsNonRelativeReferences)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         bool isRelative;
//     };
//     const std::vector<TestVector> testVectors{
//         {"http://www.example.com/", false},
//         {"http://www.example.com", false},
//         {"/", true},
//         {"foo", true},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.isRelative, uri.isRelative()) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseRelativeVsNonRelativePaths)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         bool containsRelativePath;
//     };
//     const std::vector<TestVector> testVectors{
//         {"http://www.example.com/", false},
//         {"http://www.example.com", false},
//         {"/", false},
//         {"foo", true},
//
//         /*
//          * This is only a valid test vector if we understand
//          * correctly that an empty string IS a valid
//          * "relative reference" URI with an empty path.
//          */
//         {"", true},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.containsRelativePath, uri.containsRelativePath()) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseQueryAndFragmentElements)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string host;
//         std::string query;
//         std::string fragment;
//     };
//     const std::vector<TestVector> testVectors{
//         {"http://www.example.com/", "www.example.com", "", ""},
//         {"http://example.com?foo", "example.com", "foo", ""},
//         {"http://www.example.com#foo", "www.example.com", "", "foo"},
//         {"http://www.example.com?foo#bar", "www.example.com", "foo", "bar"},
//         {"http://www.example.com?earth?day#bar", "www.example.com", "earth?day", "bar"},
//         {"http://www.example.com/spam?foo#bar", "www.example.com", "foo", "bar"},
//
//         /*
//          * NOTE: curiously, but we think this is correct, that
//          * having a trailing question mark is equivalent to not having
//          * any question mark, because in both cases, the query element
//          * is empty string.  Perhaps research deeper to see if this is right.
//          */
//         {"http://www.example.com/?", "www.example.com", "", ""},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.host, uri.getHost()) << index;
//         ASSERT_EQ(testVector.query, uri.getQuery()) << index;
//         ASSERT_EQ(testVector.fragment, uri.getFragment()) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseUserInfo)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string userInfo;
//     };
//     const std::vector<TestVector> testVectors{
//         {"http://www.example.com/", ""},
//         {"http://joe@www.example.com", "joe"},
//         {"http://pepe:feelsbadman@www.example.com", "pepe:feelsbadman"},
//         {"//www.example.com", ""},
//         {"//bob@www.example.com", "bob"},
//         {"/", ""},
//         {"foo", ""},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.userInfo, uri.getUserInfo()) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseTwiceFirstUserInfoThenWithout)
// {
//     Uri uri;
//     ASSERT_TRUE(uri.parse("http://joe@www.example.com/foo/bar"));
//     ASSERT_TRUE(uri.parse("/foo/bar"));
//     ASSERT_TRUE(uri.getUserInfo().empty());
// }
//
// TEST(UriTests, parseSchemeIllegalCharacters)
// {
//     const std::vector<std::string> testVectors{
//         {"://www.example.com/"},
//         {"0://www.example.com/"},
//         {"+://www.example.com/"},
//         {"@://www.example.com/"},
//         {".://www.example.com/"},
//         {"h@://www.example.com/"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_FALSE(uri.parse(testVector)) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseSchemeBarelyLegal)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string scheme;
//     };
//     const std::vector<TestVector> testVectors{
//         {"h://www.example.com/", "h"},
//         {"x+://www.example.com/", "x+"},
//         {"y-://www.example.com/", "y-"},
//         {"z.://www.example.com/", "z."},
//         {"aa://www.example.com/", "aa"},
//         {"a0://www.example.com/", "a0"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.scheme, uri.getScheme());
//         ++index;
//     }
// }
//
// TEST(UriTests, parseSchemeMixedCase)
// {
//     const std::vector<std::string> testVectors{
//         {"http://www.example.com/"},
//         {"hTtp://www.example.com/"},
//         {"HTTP://www.example.com/"},
//         {"Http://www.example.com/"},
//         {"HttP://www.example.com/"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector)) << index;
//         ASSERT_EQ("http", uri.getScheme()) << ">>> Failed for test vector element " << index << " <<<";
//         ++index;
//     }
// }
//
// TEST(UriTests, parseHostEndsInDot)
// {
//     Uri uri;
//     ASSERT_TRUE(uri.parse("http://example.com./foo"));
//     ASSERT_EQ("example.com.", uri.getHost());
// }
//
// TEST(UriTests, parseUserInfoIllegalCharacters)
// {
//     const std::vector<std::string> testVectors{
//         {"//%X@www.example.com/"},
//         {"//{@www.example.com/"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_FALSE(uri.parse(testVector)) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseUserInfoBarelyLegal)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string userInfo;
//     };
//     const std::vector<TestVector> testVectors{
//         {"//%41@www.example.com/", "A"},
//         {"//@www.example.com/", ""},
//         {"//!@www.example.com/", "!"},
//         {"//'@www.example.com/", "'"},
//         {"//(@www.example.com/", "("},
//         {"//;@www.example.com/", ";"},
//         {"http://:@www.example.com/", ":"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.userInfo, uri.getUserInfo());
//         ++index;
//     }
// }
//
// TEST(UriTests, parseHostIllegalCharacters)
// {
//     const std::vector<std::string> testVectors{
//         {"//%X@www.example.com/"},
//         {"//@www:example.com/"},
//         {"//[vX.:]/"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_FALSE(uri.parse(testVector)) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseHostBarelyLegal)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string host;
//     };
//     const std::vector<TestVector> testVectors{
//         {"//%41/", "a"},
//         {"///", ""},
//         {"//!/", "!"},
//         {"//'/", "'"},
//         {"//(/", "("},
//         {"//;/", ";"},
//         {"//1.2.3.4/", "1.2.3.4"},
//         {"//[v7.:]/", "v7.:"},
//         {"//[v7.aB]/", "v7.aB"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.host, uri.getHost());
//         ++index;
//     }
// }
//
// TEST(UriTests, parseHostMixedCase)
// {
//     const std::vector<std::string> testVectors{
//         {"http://www.example.com/"},
//         {"http://www.EXAMPLE.com/"},
//         {"http://www.exAMple.com/"},
//         {"http://www.example.cOM/"},
//         {"http://wWw.exampLe.Com/"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector)) << index;
//         ASSERT_EQ("www.example.com", uri.getHost()) << ">>> Failed for test vector element " << index << " <<<";
//         ++index;
//     }
// }
//
// TEST(UriTests, parseDontMisinterpretColonInOtherPlacesAsSchemeDelimiter)
// {
//     const std::vector<std::string> testVectors{
//         {"//foo:bar@www.example.com/"},
//         {"//www.example.com/a:b"},
//         {"//www.example.com/foo?a:b"},
//         {"//www.example.com/foo#a:b"},
//         {"//[v7.:]/"},
//         {"/:/foo"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector)) << index;
//         ASSERT_TRUE(uri.getScheme().empty());
//         ++index;
//     }
// }
//
// TEST(UriTests, parsePathIllegalCharacters)
// {
//     const std::vector<std::string> testVectors{
//         {"http://www.example.com/foo[bar"},
//         {"http://www.example.com/]bar"},
//         {"http://www.example.com/foo]"},
//         {"http://www.example.com/["},
//         {"http://www.example.com/abc/foo]"},
//         {"http://www.example.com/abc/["},
//         {"http://www.example.com/foo]/abc"},
//         {"http://www.example.com/[/abc"},
//         {"http://www.example.com/foo]/"},
//         {"http://www.example.com/[/"},
//         {"/foo[bar"},
//         {"/]bar"},
//         {"/foo]"},
//         {"/["},
//         {"/abc/foo]"},
//         {"/abc/["},
//         {"/foo]/abc"},
//         {"/[/abc"},
//         {"/foo]/"},
//         {"/[/"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_FALSE(uri.parse(testVector)) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parsePathBarelyLegal)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::vector<std::string> path;
//     };
//     const std::vector<TestVector> testVectors{
//         {"/:/foo", {"", ":", "foo"}},
//         {"bob@/foo", {"bob@", "foo"}},
//         {"hello!", {"hello!"}},
//         {"urn:hello,%20w%6Frld", {"hello, world"}},
//         {"//example.com/foo/(bar)/", {"", "foo", "(bar)", ""}},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.path, uri.getPath());
//         ++index;
//     }
// }
//
// TEST(UriTests, parseQueryIllegalCharacters)
// {
//     const std::vector<std::string> testVectors{
//         {"http://www.example.com/?foo[bar"},
//         {"http://www.example.com/?]bar"},
//         {"http://www.example.com/?foo]"},
//         {"http://www.example.com/?["},
//         {"http://www.example.com/?abc/foo]"},
//         {"http://www.example.com/?abc/["},
//         {"http://www.example.com/?foo]/abc"},
//         {"http://www.example.com/?[/abc"},
//         {"http://www.example.com/?foo]/"},
//         {"http://www.example.com/?[/"},
//         {"?foo[bar"},
//         {"?]bar"},
//         {"?foo]"},
//         {"?["},
//         {"?abc/foo]"},
//         {"?abc/["},
//         {"?foo]/abc"},
//         {"?[/abc"},
//         {"?foo]/"},
//         {"?[/"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_FALSE(uri.parse(testVector)) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseQueryBarelyLegal)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string query;
//     };
//     const std::vector<TestVector> testVectors{
//         {"/?:/foo", ":/foo"},
//         {"?bob@/foo", "bob@/foo"},
//         {"?hello!", "hello!"},
//         {"urn:?hello,%20w%6Frld", "hello, world"},
//         {"//example.com/foo?(bar)/", "(bar)/"},
//         {"http://www.example.com/?foo?bar", "foo?bar"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.query, uri.getQuery());
//         ++index;
//     }
// }
//
// TEST(UriTests, parseFragmentIllegalCharacters)
// {
//     const std::vector<std::string> testVectors{
//         {"http://www.example.com/#foo[bar"},
//         {"http://www.example.com/#]bar"},
//         {"http://www.example.com/#foo]"},
//         {"http://www.example.com/#["},
//         {"http://www.example.com/#abc/foo]"},
//         {"http://www.example.com/#abc/["},
//         {"http://www.example.com/#foo]/abc"},
//         {"http://www.example.com/#[/abc"},
//         {"http://www.example.com/#foo]/"},
//         {"http://www.example.com/#[/"},
//         {"#foo[bar"},
//         {"#]bar"},
//         {"#foo]"},
//         {"#["},
//         {"#abc/foo]"},
//         {"#abc/["},
//         {"#foo]/abc"},
//         {"#[/abc"},
//         {"#foo]/"},
//         {"#[/"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_FALSE(uri.parse(testVector)) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, parseFragmentBarelyLegal)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string fragment;
//     };
//     const std::vector<TestVector> testVectors{
//         {"/#:/foo", ":/foo"},
//         {"#bob@/foo", "bob@/foo"},
//         {"#hello!", "hello!"},
//         {"urn:#hello,%20w%6Frld", "hello, world"},
//         {"//example.com/foo#(bar)/", "(bar)/"},
//         {"http://www.example.com/#foo?bar", "foo?bar"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.fragment, uri.getFragment());
//         ++index;
//     }
// }
//
// TEST(UriTests, parsePathsWithPercentEncodedCharacters)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string pathFirstSegment;
//     };
//     const std::vector<TestVector> testVectors{
//         {"%41", "A"},
//         {"%4A", "J"},
//         {"%4a", "J"},
//         {"%bc", "\xbc"},
//         {"%Bc", "\xbc"},
//         {"%bC", "\xbc"},
//         {"%BC", "\xbc"},
//         {"%41%42%43", "ABC"},
//         {"%41%4A%43%4b", "AJCK"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         ASSERT_EQ(testVector.pathFirstSegment, uri.getPath()[0]);
//         ++index;
//     }
// }
//
// TEST(UriTests, normalizePath)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::vector<std::string> normalizedPathSegments;
//     };
//     const std::vector<TestVector> testVectors{
//         {"/a/b/c/./../../g", {"", "a", "g"}},
//         {"mid/content=5/../6", {"mid", "6"}},
//         {"http://example.com/a/../b", {"", "b"}},
//         {"http://example.com/../b", {"", "b"}},
//         {"http://example.com/a/../b/", {"", "b", ""}},
//         {"http://example.com/a/../../b", {"", "b"}},
//         {"./a/b", {"a", "b"}},
//         {"..", {}},
//         {"/", {""}},
//         {"a/b/..", {"a", ""}},
//         {"a/b/.", {"a", "b", ""}},
//         {"a/b/./c", {"a", "b", "c"}},
//         {"a/b/./c/", {"a", "b", "c", ""}},
//         {"/a/b/..", {"", "a", ""}},
//         {"/a/b/.", {"", "a", "b", ""}},
//         {"/a/b/./c", {"", "a", "b", "c"}},
//         {"/a/b/./c/", {"", "a", "b", "c", ""}},
//         {"./a/b/..", {"a", ""}},
//         {"./a/b/.", {"a", "b", ""}},
//         {"./a/b/./c", {"a", "b", "c"}},
//         {"./a/b/./c/", {"a", "b", "c", ""}},
//         {"../a/b/..", {"a", ""}},
//         {"../a/b/.", {"a", "b", ""}},
//         {"../a/b/./c", {"a", "b", "c"}},
//         {"../a/b/./c/", {"a", "b", "c", ""}},
//         {"../a/b/../c", {"a", "c"}},
//         {"../a/b/./../c/", {"a", "c", ""}},
//         {"../a/b/./../c", {"a", "c"}},
//         {"../a/b/./../c/", {"a", "c", ""}},
//         {"../a/b/.././c/", {"a", "c", ""}},
//         {"../a/b/.././c", {"a", "c"}},
//         {"../a/b/.././c/", {"a", "c", ""}},
//         {"/./c/d", {"", "c", "d"}},
//         {"/../c/d", {"", "c", "d"}},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         ASSERT_TRUE(uri.parse(testVector.uriString)) << index;
//         uri.normalizePath();
//         ASSERT_EQ(testVector.normalizedPathSegments, uri.getPath()) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, ConstructNormalizeAndCompareEquivalentUris)
// {
//     // This was inspired by section 6.2.2
//     // of RFC 3986 (https://tools.ietf.org/html/rfc3986).
//     Uri uri1, uri2;
//     ASSERT_TRUE(uri1.parse("example://a/b/c/%7Bfoo%7D"));
//     ASSERT_TRUE(uri2.parse("eXAMPLE://a/./b/../b/%63/%7bfoo%7d"));
//     ASSERT_NE(uri1, uri2);
//     uri2.normalizePath();
//     ASSERT_EQ(uri1, uri2);
// }
//
// TEST(UriTests, ReferenceResolution)
// {
//     struct TestVector
//     {
//         std::string baseString;
//         std::string relativeReferenceString;
//         std::string targetString;
//     };
//     const std::vector<TestVector> testVectors{
//         // These are all taken from section 5.4.1
//         // of RFC 3986 (https://tools.ietf.org/html/rfc3986).
//         {"http://a/b/c/d;p?q", "g:h", "g:h"},
//         {"http://a/b/c/d;p?q", "g", "http://a/b/c/g"},
//         {"http://a/b/c/d;p?q", "./g", "http://a/b/c/g"},
//         {"http://a/b/c/d;p?q", "g/", "http://a/b/c/g/"},
//         {"http://a/b/c/d;p?q", "//g", "http://g"},
//         {"http://a/b/c/d;p?q", "?y", "http://a/b/c/d;p?y"},
//         {"http://a/b/c/d;p?q", "g?y", "http://a/b/c/g?y"},
//         {"http://a/b/c/d;p?q", "#s", "http://a/b/c/d;p?q#s"},
//         {"http://a/b/c/d;p?q", "g#s", "http://a/b/c/g#s"},
//         {"http://a/b/c/d;p?q", "g?y#s", "http://a/b/c/g?y#s"},
//         {"http://a/b/c/d;p?q", ";x", "http://a/b/c/;x"},
//         {"http://a/b/c/d;p?q", "g;x", "http://a/b/c/g;x"},
//         {"http://a/b/c/d;p?q", "g;x?y#s", "http://a/b/c/g;x?y#s"},
//         {"http://a/b/c/d;p?q", "", "http://a/b/c/d;p?q"},
//         {"http://a/b/c/d;p?q", ".", "http://a/b/c/"},
//         {"http://a/b/c/d;p?q", "./", "http://a/b/c/"},
//         {"http://a/b/c/d;p?q", "..", "http://a/b/"},
//         {"http://a/b/c/d;p?q", "../", "http://a/b/"},
//         {"http://a/b/c/d;p?q", "../g", "http://a/b/g"},
//         {"http://a/b/c/d;p?q", "../..", "http://a"},
//         {"http://a/b/c/d;p?q", "../../", "http://a"},
//         {"http://a/b/c/d;p?q", "../../g", "http://a/g"},
//
//         // Here are some examples of our own.
//         {"http://example.com", "foo", "http://example.com/foo"},
//         {"http://example.com/", "foo", "http://example.com/foo"},
//         {"http://example.com", "foo/", "http://example.com/foo/"},
//         {"http://example.com/", "foo/", "http://example.com/foo/"},
//         {"http://example.com", "/foo", "http://example.com/foo"},
//         {"http://example.com/", "/foo", "http://example.com/foo"},
//         {"http://example.com", "/foo/", "http://example.com/foo/"},
//         {"http://example.com/", "/foo/", "http://example.com/foo/"},
//         {"http://example.com/", "?foo", "http://example.com/?foo"},
//         {"http://example.com/", "#foo", "http://example.com/#foo"},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri baseUri, relativeReferenceUri, expectedTargetUri;
//         ASSERT_TRUE(baseUri.parse(testVector.baseString));
//         ASSERT_TRUE(relativeReferenceUri.parse(testVector.relativeReferenceString)) << index;
//         ASSERT_TRUE(expectedTargetUri.parse(testVector.targetString)) << index;
//         const auto actualTargetUri = baseUri.resolve(relativeReferenceUri);
//         ASSERT_EQ(expectedTargetUri, actualTargetUri) << index;
//         ++index;
//     }
// }
//
// TEST(UriTests, EmptyPathInUriWithAuthorityIsEquivalentToSlashOnlyPath)
// {
//     Uri uri1, uri2;
//     ASSERT_TRUE(uri1.parse("http://example.com"));
//     ASSERT_TRUE(uri2.parse("http://example.com/"));
//     ASSERT_EQ(uri1, uri2);
//     ASSERT_TRUE(uri1.parse("//example.com"));
//     ASSERT_TRUE(uri2.parse("//example.com/"));
//     ASSERT_EQ(uri1, uri2);
// }
//
// TEST(UriTests, IPv6Address)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string expectedHost;
//         bool isValid;
//     };
//     const std::vector<TestVector> testVectors{
//         // valid
//         {"http://[::1]/", "::1", true},
//         {"http://[::ffff:1.2.3.4]/", "::ffff:1.2.3.4", true},
//         {"http://[2001:db8:85a3:8d3:1319:8a2e:370:7348]/", "2001:db8:85a3:8d3:1319:8a2e:370:7348", true},
//         {"http://[2001:db8:85a3:8d3:1319:8a2e:370::]/", "2001:db8:85a3:8d3:1319:8a2e:370::", true},
//         {"http://[2001:db8:85a3:8d3:1319:8a2e::1]/", "2001:db8:85a3:8d3:1319:8a2e::1", true},
//         {"http://[fFfF::1]", "fFfF::1", true},
//         {"http://[1234::1]", "1234::1", true},
//         {"http://[fFfF:1:2:3:4:5:6:a]", "fFfF:1:2:3:4:5:6:a", true},
//         {"http://[2001:db8:85a3::8a2e:0]/", "2001:db8:85a3::8a2e:0", true},
//         {"http://[2001:db8:85a3:8a2e::]/", "2001:db8:85a3:8a2e::", true},
//
//         // invalid
//         {"http://[::fFfF::1]", "", false},
//         {"http://[::ffff:1.2.x.4]/", "", false},
//         {"http://[::ffff:1.2.3.4.8]/", "", false},
//         {"http://[::ffff:1.2.3]/", "", false},
//         {"http://[::ffff:1.2.3.]/", "", false},
//         {"http://[::ffff:1.2.3.256]/", "", false},
//         {"http://[::fxff:1.2.3.4]/", "", false},
//         {"http://[::ffff:1.2.3.-4]/", "", false},
//         {"http://[::ffff:1.2.3. 4]/", "", false},
//         {"http://[::ffff:1.2.3.4 ]/", "", false},
//         {"http://[::ffff:1.2.3.4/", "", false},
//         {"http://::ffff:1.2.3.4]/", "", false},
//         {"http://::ffff:a.2.3.4]/", "", false},
//         {"http://::ffff:1.a.3.4]/", "", false},
//         {"http://[2001:db8:85a3:8d3:1319:8a2e:370:7348:0000]/", "", false},
//         {"http://[2001:db8:85a3:8d3:1319:8a2e:370:7348::1]/", "", false},
//         {"http://[2001:db8:85a3:8d3:1319:8a2e:370::1]/", "", false},
//         {"http://[2001:db8:85a3::8a2e:0:]/", "", false},
//         {"http://[2001:db8:85a3::8a2e::]/", "", false},
//         {"http://[]/", "", false},
//         {"http://[:]/", "", false},
//         {"http://[v]/", "", false},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         const bool parseResult = uri.parse(testVector.uriString);
//         ASSERT_EQ(testVector.isValid, parseResult) << index;
//         if (parseResult)
//         {
//             ASSERT_EQ(testVector.expectedHost, uri.getHost());
//         }
//         ++index;
//     }
// }
//
// TEST(UriTests, IPvFutureAddress)
// {
//     struct TestVector
//     {
//         std::string uriString;
//         std::string expectedHost;
//         bool isValid;
//     };
//     const std::vector<TestVector> testVectors{
//         // valid
//         {"http://[v1.x]/", "v1.x", true},
//         {"http://[vf.xy]/", "vf.xy", true},
//         {"http://[vf.x:y]/", "vf.x:y", true},
//
//         // invalid
//         {"http://[vx]/", "", false},
//         {"http://[v12]/", "", false},
//         {"http://[v1.?]/", "", false},
//         {"http://[v1.x?]/", "", false},
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         const bool parseResult = uri.parse(testVector.uriString);
//         ASSERT_EQ(testVector.isValid, parseResult) << index;
//         if (parseResult)
//         {
//             ASSERT_EQ(testVector.expectedHost, uri.getHost());
//         }
//         ++index;
//     }
// }
//
//
// TEST(UriTests, FragmentEmptyButPresent)
// {
//     Uri uri;
//     ASSERT_TRUE(uri.parse("http://example.com#"));
//     ASSERT_TRUE(uri.hasFragment());
//     ASSERT_EQ("", uri.getFragment());
//     ASSERT_EQ("http://example.com/#", uri.generateString());
//     uri.clearFragment();
//     ASSERT_EQ("http://example.com/", uri.generateString());
//     ASSERT_FALSE(uri.hasFragment());
//     ASSERT_TRUE(uri.parse("http://example.com"));
//     ASSERT_FALSE(uri.hasFragment());
//     uri.setFragment("");
//     ASSERT_TRUE(uri.hasFragment());
//     ASSERT_EQ("", uri.getFragment());
//     ASSERT_EQ("http://example.com/#", uri.generateString());
// }
//
// TEST(UriTests, QueryEmptyButPresent)
// {
//     Uri uri;
//     ASSERT_TRUE(uri.parse("http://example.com?"));
//     ASSERT_TRUE(uri.hasQuery());
//     ASSERT_EQ("", uri.getQuery());
//     ASSERT_EQ("http://example.com/?", uri.generateString());
//     uri.clearQuery();
//     ASSERT_EQ("http://example.com/", uri.generateString());
//     ASSERT_FALSE(uri.hasQuery());
//     ASSERT_TRUE(uri.parse("http://example.com"));
//     ASSERT_FALSE(uri.hasQuery());
//     uri.setQuery("");
//     ASSERT_TRUE(uri.hasQuery());
//     ASSERT_EQ("", uri.getQuery());
//     ASSERT_EQ("http://example.com/?", uri.generateString());
// }
//
// TEST(UriTests, MakeACopy)
// {
//     Uri uri1;
//     (void)uri1.parse("http://www.example.com/foo.txt");
//     Uri uri2(uri1);
//     uri1.setQuery("bar");
//     uri2.setFragment("page2");
//     uri2.setHost("example.com");
//     EXPECT_EQ("http://www.example.com/foo.txt?bar", uri1.generateString());
//     EXPECT_EQ("http://example.com/foo.txt#page2", uri2.generateString());
// }
//
// TEST(UriTests, AssignACopy)
// {
//     Uri uri1;
//     (void)uri1.parse("http://www.example.com/foo.txt");
//     Uri uri2;
//     uri2 = uri1;
//     uri1.setQuery("bar");
//     uri2.setFragment("page2");
//     uri2.setHost("example.com");
//     EXPECT_EQ("http://www.example.com/foo.txt?bar", uri1.generateString());
//     EXPECT_EQ("http://example.com/foo.txt#page2", uri2.generateString());
// }
//
// TEST(UriTests, ClearQuery)
// {
//     Uri uri;
//     (void)uri.parse("http://www.example.com/?foo=bar");
//     uri.clearQuery();
//     EXPECT_EQ("http://www.example.com/", uri.generateString());
//     EXPECT_FALSE(uri.hasQuery());
// }
//
// TEST(UriTests, PercentEncodePlusInQueries)
// {
//     // Although RFC 3986 doesn't say anything about '+', some web services
//     // treat it the same as ' ' due to how HTML originally defined how
//     // to encode the query portion of a URL
//     // (see https://stackoverflow.com/questions/2678551/when-to-encode-space-to-plus-or-20).
//     //
//     // To avoid issues with these web services, make sure '+' is
//     // percent-encoded in a URI when the URI is encoded.
//     Uri uri;
//     uri.setQuery("foo+bar");
//     EXPECT_EQ("?foo%2Bbar", uri.generateString());
// }
