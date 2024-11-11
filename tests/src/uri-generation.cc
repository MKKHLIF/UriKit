// #include <gtest/gtest.h>
// #include <uri/uri.h>

// TEST(UriTests, GenerateString)
// {
//     struct TestVector
//     {
//         std::string scheme;
//         std::string userinfo;
//         std::string host;
//         bool hasPort;
//         uint16_t port;
//         std::vector<std::string> path;
//         bool hasQuery;
//         std::string query;
//         bool hasFragment;
//         std::string fragment;
//         std::string expectedUriString;
//     };
//     const std::vector<TestVector> testVectors{
//         // general test vectors
//         {
//             "http", "bob", "www.example.com", true, 8080, {"", "abc", "def"}, true, "foobar", true, "ch2",
//             "http://bob@www.example.com:8080/abc/def?foobar#ch2"
//         },
//         {
//             "http", "bob", "www.example.com", true, 0, {}, true, "foobar", true, "ch2",
//             "http://bob@www.example.com:0?foobar#ch2"
//         },
//         {
//             "http", "bob", "www.example.com", true, 0, {}, true, "foobar", true, "",
//             "http://bob@www.example.com:0?foobar#"
//         },
//         {"", "", "example.com", false, 0, {}, true, "bar", false, "", "//example.com?bar"},
//         {"", "", "example.com", false, 0, {}, true, "", false, "", "//example.com?"},
//         {"", "", "example.com", false, 0, {}, false, "", false, "", "//example.com"},
//         {"", "", "example.com", false, 0, {""}, false, "", false, "", "//example.com/"},
//         {"", "", "example.com", false, 0, {"", "xyz"}, false, "", false, "", "//example.com/xyz"},
//         {"", "", "example.com", false, 0, {"", "xyz", ""}, false, "", false, "", "//example.com/xyz/"},
//         {"", "", "", false, 0, {""}, false, "", false, "", "/"},
//         {"", "", "", false, 0, {"", "xyz"}, false, "", false, "", "/xyz"},
//         {"", "", "", false, 0, {"", "xyz", ""}, false, "", false, "", "/xyz/"},
//         {"", "", "", false, 0, {}, false, "", false, "", ""},
//         {"", "", "", false, 0, {"xyz"}, false, "", false, "", "xyz"},
//         {"", "", "", false, 0, {"xyz", ""}, false, "", false, "", "xyz/"},
//         {"", "", "", false, 0, {}, true, "bar", false, "", "?bar"},
//         {"http", "", "", false, 0, {}, true, "bar", false, "", "http:?bar"},
//         {"http", "", "", false, 0, {}, false, "", false, "", "http:"},
//         {"http", "", "::1", false, 0, {}, false, "", false, "", "http://[::1]"},
//         {"http", "", "::1.2.3.4", false, 0, {}, false, "", false, "", "http://[::1.2.3.4]"},
//         {"http", "", "1.2.3.4", false, 0, {}, false, "", false, "", "http://1.2.3.4"},
//         {"", "", "", false, 0, {}, false, "", false, "", ""},
//         {"http", "bob", "", false, 0, {}, true, "foobar", false, "", "http://bob@?foobar"},
//         {"", "bob", "", false, 0, {}, true, "foobar", false, "", "//bob@?foobar"},
//         {"", "bob", "", false, 0, {}, false, "", false, "", "//bob@"},
//
//         // percent-encoded character test vectors
//         {
//             "http", "b b", "www.example.com", true, 8080, {"", "abc", "def"}, true, "foobar", true, "ch2",
//             "http://b%20b@www.example.com:8080/abc/def?foobar#ch2"
//         },
//         {
//             "http", "bob", "www.e ample.com", true, 8080, {"", "abc", "def"}, true, "foobar", true, "ch2",
//             "http://bob@www.e%20ample.com:8080/abc/def?foobar#ch2"
//         },
//         {
//             "http", "bob", "www.example.com", true, 8080, {"", "a c", "def"}, true, "foobar", true, "ch2",
//             "http://bob@www.example.com:8080/a%20c/def?foobar#ch2"
//         },
//         {
//             "http", "bob", "www.example.com", true, 8080, {"", "abc", "def"}, true, "foo ar", true, "ch2",
//             "http://bob@www.example.com:8080/abc/def?foo%20ar#ch2"
//         },
//         {
//             "http", "bob", "www.example.com", true, 8080, {"", "abc", "def"}, true, "foobar", true, "c 2",
//             "http://bob@www.example.com:8080/abc/def?foobar#c%202"
//         },
//         {
//             "http", "bob", "ሴ.example.com", true, 8080, {"", "abc", "def"}, true, "foobar", false, "",
//             "http://bob@%E1%88%B4.example.com:8080/abc/def?foobar"
//         },
//
//         // normalization of IPv6 address hex digits
//         {
//             "http", "bob", "fFfF::1", true, 8080, {"", "abc", "def"}, true, "foobar", true, "c 2",
//             "http://bob@[ffff::1]:8080/abc/def?foobar#c%202"
//         },
//     };
//     size_t index = 0;
//     for (const auto& testVector : testVectors)
//     {
//         Uri uri;
//         uri.setScheme(testVector.scheme);
//         uri.setUserInfo(testVector.userinfo);
//         uri.setHost(testVector.host);
//         if (testVector.hasPort)
//         {
//             uri.setPort(testVector.port);
//         }
//         else
//         {
//             uri.clearPort();
//         }
//         uri.setPath(testVector.path);
//         if (testVector.hasQuery)
//         {
//             uri.setQuery(testVector.query);
//         }
//         else
//         {
//             uri.clearQuery();
//         }
//         if (testVector.hasFragment)
//         {
//             uri.setFragment(testVector.fragment);
//         }
//         else
//         {
//             uri.clearFragment();
//         }
//         const auto actualUriString = uri.generateString();
//         ASSERT_EQ(testVector.expectedUriString, actualUriString) << index;
//         ++index;
//     }
// }
