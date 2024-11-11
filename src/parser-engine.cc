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

private:
    static void splitPathAndAuthority(const Uri *obj, const std::string &uri, std::string &authority,
                                      std::string &path);
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

    obj->setScheme(content);

    std::string authority;
    std::string path;

    splitPathAndAuthority(obj, uri, authority, path);

    std::vector<std::string> authority_components(3);
    status = AuthorityParser::parse(authority, authority_components);
    if (status == false) {
        obj->reset();
        return false;
    }
    if (!authority_components[0].empty()) {
        obj->setUserInfo(authority_components[0]);
    }
    if (!authority_components[1].empty()) {
        obj->setHost(authority_components[1]);
    }
    if (!authority_components[2].empty()) {
        obj->setPort(std::stoi(authority_components[2]));
    }

    std::vector<std::string> path_components;
    status = PathParser::parse(path, path_components);
    if (status == false) {
        obj->reset();
        return false;
    }
    obj->setPath(path_components);


    return true;
}

void Parser::Imp::splitPathAndAuthority(const Uri *obj, const std::string &uri, std::string &authority,
                                        std::string &path) {
    auto path_end = uri.find_first_of("?#");
    if (path_end == std::string::npos) path_end = uri.length();

    const auto authority_and_path = uri.substr(0, path_end);

    // split authority from path
    auto authority_end = authority_and_path.find('/');
    if (authority_end == std::string::npos) {
        authority_end = authority_and_path.length();
    }

    authority = authority_and_path.substr(0, authority_end);
    path = authority_and_path.substr(authority_end);

    // Edge case for mailto
    if (obj->getScheme() == "mailto") {
        path = authority;
        authority.clear();
    }
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
