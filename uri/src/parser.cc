#include "parser.h"

#include <iostream>

#include "string_extensions.h"
#include "syntax_validator.h"

ParseResult<std::string> Parser::parseScheme(const std::string& uri, size_t cursor)
{
    auto authorityOrPathDelimiterStart = uri.find('/');
    if (authorityOrPathDelimiterStart == std::string::npos)
    {
        authorityOrPathDelimiterStart = uri.length();
    }
    const auto schemeEnd = uri.substr(0, authorityOrPathDelimiterStart).find(':');

    if (schemeEnd == std::string::npos) return {false, ""};

    std::string scheme = uri.substr(0, schemeEnd);
    scheme = StringExtensions::lowercase(scheme);

    if (!SyntaxValidator::validateScheme(scheme)) return {true, ""};
    return {false, scheme};
}

ParseResult<std::string> Parser::parseAuthority(const std::string& uri, size_t cursor)
{
    const auto pos = uri.find("://");
    if (pos == std::string::npos) return {false, ""};
    const auto start = pos + 3;
    if (start >= uri.size()) return {false, ""};
    const auto end = uri.find_first_of("/?#", start);
    if (end == std::string::npos)
    {
        return {true, uri.substr(start)};
    }
    return {true, uri.substr(start, end - start)};
}

ParseResult<std::vector<std::string>> Parser::parsePath(const std::string& uri, size_t cursor)
{
    std::vector<std::string> path;

    auto schemeEnd = uri.find("://");
    if (schemeEnd == std::string::npos) return {false, path};

    auto start = schemeEnd + 3;
    if (start >= uri.size()) return {false, path};

    auto pathStart = uri.find('/', start);
    if (pathStart == std::string::npos) return {false, path};

    auto pathEnd = uri.find_first_of("?#", pathStart);
    if (pathEnd == std::string::npos)
    {
        pathEnd = uri.size();
    }

    const auto pathStr = uri.substr(pathStart, pathEnd - pathStart);
    size_t segmentStart = 0;

    while (segmentStart < pathStr.size())
    {
        auto segmentEnd = pathStr.find('/', segmentStart);
        if (segmentEnd == std::string::npos)
        {
            path.push_back(pathStr.substr(segmentStart));
            break;
        }
        path.push_back(pathStr.substr(segmentStart, segmentEnd - segmentStart));
        segmentStart = segmentEnd + 1;
    }

    return {true, path};
}

ParseResult<std::string> Parser::parseUserInfo(const std::string& authority, size_t cursor)
{
    const auto at_pos = authority.find('@');
    if (at_pos == std::string::npos) return {false, ""};
    return {true, authority.substr(0, at_pos)};
}

ParseResult<std::string> Parser::parseHost(const std::string& authority, size_t cursor)
{
    const auto at_pos = authority.find('@');
    const auto colon_pos = authority.find_last_of(':');

    const auto hostStart = at_pos == std::string::npos ? 0 : at_pos + 1;
    auto hostEnd = colon_pos == std::string::npos ? authority.size() : colon_pos;

    if (authority[hostStart] == '[')
    {
        hostEnd = authority.find(']', hostStart);
        if (hostEnd == std::string::npos) return {false, ""};
        hostEnd++;
    }
    return {true, authority.substr(hostStart, hostEnd - hostStart)};
}

ParseResult<std::string> Parser::parsePort(const std::string& authority, size_t cursor)
{
    const auto at_pos = authority.find('@');
    auto startSearch = at_pos == std::string::npos ? 0 : at_pos + 1;
    if (authority[startSearch] == '[')
    {
        startSearch = authority.find(']', startSearch);
        if (startSearch == std::string::npos) return {false, ""};
    }

    const auto colon_pos = authority.find(':', startSearch);

    if (colon_pos == std::string::npos) return {false, "80"}; // Default port
    return {true, authority.substr(colon_pos + 1)};
}
