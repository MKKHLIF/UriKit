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
    bool parse(const std::string& str_rep, const Uri* obj);

private:
    size_t cursor;

    ParseResult<std::string> parseScheme(const std::string& str_rep);
    [[nodiscard]] ParseResult<std::string> parseAuthority(const std::string& str_rep);
    // [[nodiscard]] ParseResult<std::string> parseUserInfo(const std::string& str_rep);
    // [[nodiscard]] ParseResult<std::string> parseHost(const std::string& str_rep);
    // [[nodiscard]] ParseResult<std::string> parsePort(const std::string& str_rep);
    // [[nodiscard]] ParseResult<std::vector<std::string>> parsePath(const std::string& str_rep);
};

bool Parser::Imp::parse(const std::string& str_rep, const Uri* obj)
{
    auto result = parseScheme(str_rep);
    if (result.error) return false;

    // To-do: check if the scheme is valid
    obj->setScheme(result.content);


    result = parseAuthority(str_rep);

    return true;
}

ParseResult<std::string> Parser::Imp::parseScheme(const std::string& str_rep)
{
    // "https://www.google.com/search?q=uri"
    // "file:///C:/Users/Example/Documents/Projects/2024/Report.pdf"
    // "mailto:user@example.com"
    // "foo/bar"

    auto authority_or_path_start = str_rep.find('/');

    if (authority_or_path_start == std::string::npos)
    {
        authority_or_path_start = str_rep.length();
    }

    const auto scheme_end = str_rep.substr(cursor, authority_or_path_start).find(':');

    if (scheme_end == std::string::npos) return {false, ""};


    std::string scheme = str_rep.substr(cursor, scheme_end);

    scheme = StringExtensions::lowercase(scheme);

    if (!SyntaxValidator::validateScheme(scheme)) return {true, ""};

    ParseResult result = {false, scheme};

    cursor = scheme_end + 1;

    return result;
}

ParseResult<std::string> Parser::Imp::parseAuthority(const std::string& str_rep)
{
    // "//www.google.com/search?q=uri"
    // "///C:/Users/Example/Documents/Projects/2024/Report.pdf"
    // "user@example.com"
    // "foo/bar"

    if (str_rep[cursor] != ':') return {false, ""};
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
