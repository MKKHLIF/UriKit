#pragma once

#include <string>
#include <vector>
#include <uri/uri.h>

class Parser {
public:
    Parser();

    ~Parser() noexcept;

    Parser(const Parser &);

    Parser(Parser &&) noexcept;

    Parser &operator=(const Parser &);

    Parser &operator=(Parser &&) noexcept;

    [[nodiscard]] bool parse(std::string &uri, const Uri *obj) const;

private:
    class Imp;
    std::unique_ptr<Imp> imp;
};
