#pragma once

#include <string>
#include <vector>
#include <uri/uri.h>

template <typename T>
struct ParseResult
{
    bool error;
    T content;

    ParseResult(const bool s, T c) : error(s), content(std::move(c))
    {
    }
};

class Parser
{
public:
    static ParseResult<std::string> parseScheme(const std::string& uri, size_t cursor);
    static ParseResult<std::string> parseAuthority(const std::string& uri, size_t cursor);
    static ParseResult<std::vector<std::string>> parsePath(const std::string& uri, size_t cursor);
    static ParseResult<std::string> parseHost(const std::string& authority, size_t cursor);
    static ParseResult<std::string> parsePort(const std::string& authority, size_t cursor);
    static ParseResult<std::string> parseUserInfo(const std::string& authority, size_t cursor);
};
