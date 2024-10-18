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
    Parser();
    ~Parser() noexcept;
    Parser(const Parser&);
    Parser(Parser&&) noexcept;
    Parser& operator=(const Parser&);
    Parser& operator=(Parser&&) noexcept;

    [[nodiscard]] bool parse(const std::string& uri, const Uri* obj) const;

private:
    class Imp;
    std::unique_ptr<Imp> imp;
};
