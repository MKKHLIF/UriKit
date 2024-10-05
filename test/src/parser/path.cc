#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParsePath) {
    // Test cases for path-abempty
    ASSERT_EQ(Parser::parsePath("https://www.google.com/"), (std::vector< std::string >{"", }));
    ASSERT_EQ(Parser::parsePath("https://www.google.com"), (std::vector< std::string >{}));

    // Test cases for path-absolute
    ASSERT_EQ(Parser::parsePath("https://www.amazon.com/path/to/resource"),
        (std::vector< std::string >{"", "path", "to", "resource"}));

    ASSERT_EQ(Parser::parsePath("https://www.google.com/foo/bar/"),
        (std::vector< std::string >{"", "foo", "bar", }));

    ASSERT_EQ(Parser::parsePath("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf"),
        (std::vector< std::string >{"", "C:", "Users", "Example", "Documents", "Projects",
            "2024", "Report.pdf"}
            ));
    ASSERT_EQ(Parser::parsePath("file://server/share/folder/file.txt"),
        (std::vector< std::string >{"", "share", "folder", "file.txt"}));

    // ASSERT_EQ(Parser::parsePath("foo/bar"),
    //           (std::vector<std::string>{"foo","bar",}
    //           ));
}