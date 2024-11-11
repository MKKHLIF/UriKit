#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "path-parser.h"


TEST(StaticPathParser, AbsolutePath) {
    std::string path = "/foo/bar";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", "bar"}));
}

TEST(StaticPathParser, EmptyPath) {
    std::string path;
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, std::vector<std::string>{});
}

TEST(StaticPathParser, SingleComponentPath) {
    std::string path = "/foo";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo"}));
}

TEST(StaticPathParser, TrailingSlashInAbsolutePath) {
    std::string path = "/foo/";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", ""}));
}

TEST(StaticPathParser, AbsolutePathWithCurrentDirectory) {
    std::string path = "/foo/./bar";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", ".", "bar"}));
}

TEST(StaticPathParser, AbsolutePathWithParentDirectory) {
    std::string path = "/foo/../bar";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", "..", "bar"}));
}

TEST(StaticPathParser, MixedPathSeparators) {
    std::string path = "/foo\\bar/";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo\\bar", ""}));
}

// TEST(StaticPathParser, DoubleSlashes) {
//     std::string path = "/foo//bar";
//     std::vector<std::string> result;
//     const bool status = PathParser::parse(path, result);
//     ASSERT_TRUE(status);
//     ASSERT_EQ(result, (std::vector<std::string>{"", "foo", "bar"}));
// }

TEST(StaticPathParser, PathWithSpecialCharacters) {
    std::string path = "/foo/@@bar/";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", "@@bar", ""}));
}

TEST(StaticPathParser, RootPath) {
    std::string path = "/";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{""}));
}

TEST(StaticPathParser, EmptyComponentInPath) {
    std::string path = "/foo//bar";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo","", "bar"}));
}

TEST(StaticPathParser, RelativePath) {
    std::string path = "foo/bar";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"foo", "bar"}));
}

TEST(StaticPathParser, PathWithMultipleParentDirectory) {
    std::string path = "/foo/../bar/../../baz";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", "..", "bar", "..", "..", "baz"}));
}

TEST(StaticPathParser, PathWithTrailingSlashAfterParentDirectory) {
    std::string path = "/foo/../bar/";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", "..", "bar",""}));
}

TEST(StaticPathParser, PathWithSingleDot) {
    std::string path = "/foo/./bar";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", ".", "bar"}));
}

TEST(StaticPathParser, PathWithMultipleDots) {
    std::string path = "/foo/.././bar";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", "..", ".", "bar"}));
}

TEST(StaticPathParser, PathWithLeadingDot) {
    std::string path = "/./foo/bar";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", ".", "foo", "bar"}));
}

TEST(StaticPathParser, PathWithRootAsParent) {
    std::string path = "/foo/../../bar";
    std::vector<std::string> result;
    const bool status = PathParser::parse(path, result);
    ASSERT_TRUE(status);
    ASSERT_EQ(result, (std::vector<std::string>{"", "foo", "..", "..", "bar"}));
}
