#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(ParserTests, ParsePath) {
    // Test cases for path-abempty
    auto result = Parser::parsePath("https://www.google.com/");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, (std::vector<std::string>{""}));

    result = Parser::parsePath("https://www.google.com");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, (std::vector<std::string>{}));

    // Test cases for path-absolute
    result = Parser::parsePath("https://www.amazon.com/path/to/resource");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, (std::vector<std::string>{"", "path", "to", "resource"}));

    result = Parser::parsePath("https://www.google.com/foo/bar/");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, (std::vector<std::string>{"", "foo", "bar", ""}));

    result = Parser::parsePath("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, (std::vector<std::string>{"", "C:", "Users", "Example", "Documents", "Projects", "2024", "Report.pdf"}));

    result = Parser::parsePath("file://server/share/folder/file.txt");
    ASSERT_TRUE(result.status);
    ASSERT_EQ(result.content, (std::vector<std::string>{"", "share", "folder", "file.txt"}));

    // result = Parser::parsePath("foo/bar");
    // ASSERT_FALSE(result.status);
    // ASSERT_EQ(result.content, (std::vector<std::string>{}));
}
