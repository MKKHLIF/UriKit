#include <uri/uri.h>
#include "parser-engine.h"

#include "authority-parser.h"
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
        return true;
    }

    if (!content.empty()) {
        obj->setScheme(content);

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

        std::vector<std::string> components(3);
        status = AuthorityParser::parse(authority, components);
        if (status == false) {
            obj->reset();
            return false;
        }
        if (!components[0].empty()) {
            obj->setUserInfo(components[0]);
        }
        if (!components[1].empty()) {
            obj->setHost(components[1]);
        }
        if (!components[2].empty()) {
            obj->setPort(std::stoi(components[2]));
        }
        std::vector<std::string> path_components;
        status = PathParser::parse(path, path_components);
        if (status == false) {
            obj->reset();
            return false;
        }
        obj->setPath(path_components);
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

bool Parser::parse(std::string &uri, const Uri *obj) const {
    return imp->parse(uri, obj);
}
