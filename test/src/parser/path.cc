#include <gtest/gtest.h>
#include <uri/uri.h>

TEST(UriTests, ParsePath) {
    // Test cases for path-abempty
    ASSERT_EQ(prism::Uri::parsePath("https://www.google.com/"), (std::vector< std::string >{"", }));
    ASSERT_EQ(prism::Uri::parsePath("https://www.google.com"), (std::vector< std::string >{}));

    // Test cases for path-absolute
    ASSERT_EQ(prism::Uri::parsePath("https://www.amazon.com/path/to/resource"),
        (std::vector< std::string >{"", "path", "to", "resource"}));

    ASSERT_EQ(prism::Uri::parsePath("https://www.google.com/foo/bar/"),
        (std::vector< std::string >{"", "foo", "bar", }));

    ASSERT_EQ(prism::Uri::parsePath("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf"),
        (std::vector< std::string >{"", "C:", "Users", "Example", "Documents", "Projects",
            "2024", "Report.pdf"}
            ));
    ASSERT_EQ(prism::Uri::parsePath("file://server/share/folder/file.txt"),
        (std::vector< std::string >{"", "share", "folder", "file.txt"}));

    // ASSERT_EQ(prism::Uri::parsePath("foo/bar"),
    //           (std::vector<std::string>{"foo","bar",}
    //           ));
}