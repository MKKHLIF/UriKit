#include <uri/uri.h>
#include "parser-engine.h"

#include "path-parser.h"
#include "scheme-parser.h"

class Parser::Imp {
public:
    Imp() = default;

    ~Imp() = default;

    static bool parse(std::string &uri, const Uri *obj);
};

bool Parser::Imp::parse(std::string &uri, const Uri *obj) {
    std::string content;
    bool status = SchemeParser::parse(uri, content);

    // failed to parse scheme
    if (status == false) {
        obj->reset();
        return false;
    }

    // if scheme is empty, then it is a relative reference
    if (content.empty()) {
        obj->reset();
        std::vector<std::string> path;
        status = PathParser::parse(uri, path);
        if (status == false) {
            obj->reset();
            return false;
        }
        obj->setPath(path);
    }

    if (!content.empty()) {
        obj->setScheme(content);
        // skip // if exists
        if (uri.size() >= 2 && uri[0] == '/' && uri[1] == '/') {
            uri = uri.substr(2);
        }

        auto path_end = uri.find_first_of("?#");
        if (path_end == std::string::npos) path_end = uri.length();
        const auto authority_and_path = uri.substr(0, path_end);

        // split authority from path
        auto authority_end = authority_and_path.find('/');
        if (authority_end == std::string::npos) {
            authority_end = authority_and_path.length();
        }

        auto authority = authority_and_path.substr(0, authority_end);
        auto path = authority_and_path.substr(authority_end);

        if (obj->getScheme() == "mailto") {
            path = authority;
            authority.clear();
        }

        status = parseAuthority(authority, obj);
        if (status == false) {
            obj->reset();
            return false;
        }

        const auto parse_path_result = parsePath(path);
        if (parse_path_result.error) {
            obj->reset();
            return false;
        }
        obj->clearPath();
        obj->setPath(parse_path_result.content);
    }


    return true;
}

Parser::Parser(): imp(std::make_unique<Imp>()) {
}

Parser::~Parser() noexcept {
}

Parser::Parser(const Parser &) {
}

Parser::Parser(Parser &&) noexcept {
}

// Parser& Parser::operator=(const Parser&)
// {
// }
//
// Parser& Parser::operator=(Parser&&) noexcept
// {
// }

bool Parser::parse(const std::string &uri, const Uri *obj) const {
    return imp->parse(uri, obj);
}
