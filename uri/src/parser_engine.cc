#include "parser_engine.h"

#include <iostream>

#include "string_extensions.h"
#include "syntax_validator.h"
#include <uri/uri.h>

class Parser::Imp
{
public:
    Imp(): cursor(0)
    {
    };
    ~Imp() = default;
    bool parse(const std::string& str, const Uri* obj);

private:
    size_t cursor;

    ParseResult<std::string> parseScheme(const std::string& str);
    [[nodiscard]] ParseResult<std::string> parseAuthority(const std::string& str);
    // [[nodiscard]] ParseResult<std::string> parseUserInfo(const std::string& authority);
    // [[nodiscard]] ParseResult<std::string> parseHost(const std::string& authority);
    // [[nodiscard]] ParseResult<std::string> parsePort(const std::string& authority);
    // [[nodiscard]] ParseResult<std::vector<std::string>> parsePath(const std::string& path);
};

bool Parser::Imp::parse(const std::string& str, const Uri* obj)
{
    
    auto result = parseScheme(str);
    if (result.error) return false;

    if (!result.content.empty()) {
        obj->setScheme(result.content);
        // skip // if exists
        if (cursor + 1 < str.length() && str[cursor] == '/' && str[cursor + 1] == '/')
        {
            cursor += 2;
        }
        // "www.google.com/search?q=uri"
        // "/C:/Users/Example/Documents/Projects/2024/Report.pdf"
        // "user@example.com"

        auto path_end = str.find_first_of("?#");
        if (path_end == std::string::npos) path_end = str.length();
        const auto authority_and_path = str.substr(cursor, path_end);

        // split authority from path
        auto authority_end = authority_and_path.find('/');
        if (authority_end == std::string::npos) {
            authority_end = authority_and_path.length();
        }

        auto authority = authority_and_path.substr(cursor, authority_end);
        auto path = authority_and_path.substr(authority_end);

        result = parseAuthority(authority);
        if (result.error) return false;

        result = parseAuthority(path);
        if (result.error) return false;

    }
    // relative uri
    else {

    }

    return true;
}

ParseResult<std::string> Parser::Imp::parseScheme(const std::string& str)
{
    // "https://www.google.com/search?q=uri"
    // "file:///C:/Users/Example/Documents/Projects/2024/Report.pdf"
    // "mailto:user@example.com"
    // "foo/bar"

    auto authority_or_path_start = str.find('/');

    if (authority_or_path_start == std::string::npos)
    {
        authority_or_path_start = str.length();
    }

    const auto scheme_end = str.substr(cursor, authority_or_path_start).find(':');

    if (scheme_end == std::string::npos) return {false, ""};


    std::string scheme = str.substr(cursor, scheme_end);

    scheme = StringExtensions::lowercase(scheme);

    if (!SyntaxValidator::validateScheme(scheme)) return {true, ""};

    ParseResult result = {false, scheme};

    cursor = scheme_end + 1;

    return result;
}

ParseResult<std::string> Parser::Imp::parseAuthority(const std::string& str)
{

    return {false, ""};
}

Parser::Parser(): imp(std::make_unique<Imp>())
{
}

Parser::~Parser() noexcept
{
}

Parser::Parser(const Parser&)
{
}

Parser::Parser(Parser&&) noexcept
{
}

// Parser& Parser::operator=(const Parser&)
// {
// }
//
// Parser& Parser::operator=(Parser&&) noexcept
// {
// }

bool Parser::parse(const std::string& uri, const Uri* obj) const
{
    return imp->parse(uri, obj);
}
