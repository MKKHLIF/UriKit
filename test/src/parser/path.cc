#include <gtest/gtest.h>
#include <parser/parser.h>

TEST(StaticParseHelpers, ParsePath)
{
    constexpr size_t cursor = 0;

    // Test cases for path-abempty
    auto result = Parser::parsePath("https://www.google.com/", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, (std::vector<std::string>{""}));

    result = Parser::parsePath("https://www.google.com", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, (std::vector<std::string>{}));

    // Test cases for path-absolute
    result = Parser::parsePath("https://www.amazon.com/path/to/resource", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, (std::vector<std::string>{"", "path", "to", "resource"}));

    result = Parser::parsePath("https://www.google.com/foo/bar/", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, (std::vector<std::string>{"", "foo", "bar", ""}));

    result = Parser::parsePath("file:///C:/Users/Example/Documents/Projects/2024/Report.pdf", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content,
              (std::vector<std::string>{"", "C:", "Users", "Example", "Documents", "Projects", "2024", "Report.pdf"}));

    result = Parser::parsePath("file://server/share/folder/file.txt", cursor);
    ASSERT_TRUE(result.error);
    ASSERT_EQ(result.content, (std::vector<std::string>{"", "share", "folder", "file.txt"}));

    // result = Parser::parsePath("foo/bar");
    // ASSERT_FALSE(result.status);
    // ASSERT_EQ(result.content, (std::vector<std::string>{}));
}
