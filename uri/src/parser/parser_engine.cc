#include "parser_engine.h"

#include "../extensions/str.h"
#include "../validation/syntax_validator.h"
#include <uri/uri.h>

class Parser::Imp {
public:
    Imp(): cursor(0) {
    };

    ~Imp() = default;

    bool parse(const std::string &str, const Uri *obj);

private:
    size_t cursor;

    ParseResult<std::string> parseScheme(const std::string &str);

    [[nodiscard]] static bool parseAuthority(const std::string &authority, const Uri *obj);

    [[nodiscard]] static ParseResult<std::vector<std::string> > parsePath(std::string path);
};

bool Parser::Imp::parse(const std::string &str, const Uri *obj) {
    auto result = parseScheme(str);
    if (result.error) {
        obj->reset();
        return false;
    }

    if (!result.content.empty()) {
        obj->setScheme(result.content);
        // skip // if exists
        if (cursor + 1 < str.length() && str[cursor] == '/' && str[cursor + 1] == '/') {
            cursor += 2;
        }

        auto path_end = str.find_first_of("?#");
        if (path_end == std::string::npos) path_end = str.length();
        const auto authority_and_path = str.substr(cursor, path_end - cursor);

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

        const auto error = parseAuthority(authority, obj);
        if (error) {
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
    // relative uri
    else {
        obj->reset();
        const auto parse_path_result = parsePath(str);
        if (parse_path_result.error) {
            obj->reset();
            return false;
        }
        obj->setPath(parse_path_result.content);
    }

    return true;
}

ParseResult<std::string> Parser::Imp::parseScheme(const std::string &str) {
    // "https://www.google.com/search?q=uri"
    // "file:///C:/Users/Example/Documents/Projects/2024/Report.pdf"
    // "mailto:user@example.com"
    // "foo/bar"

    auto authority_or_path_start = str.find('/');

    if (authority_or_path_start == std::string::npos) {
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

bool Parser::Imp::parseAuthority(const std::string &authority, const Uri *obj) {
    //accepts empty authority
    if (authority.empty()) return false;

    // Check if there is a UserInfo, and if so, extract it.
    const auto user_info_delimiter = authority.find('@');
    std::string host_port;
    obj->clearUserInfo();
    if (user_info_delimiter == std::string::npos) {
        host_port = authority;
    } else {
        auto user_info = authority.substr(0, user_info_delimiter);
        obj->setUserInfo(user_info);
        host_port = authority.substr(user_info_delimiter + 1);
    }

    // Next, parsing host and port

    obj->clearHost();
    obj->clearPort();
    auto port_delimiter = host_port.find_last_of(':');
    if (port_delimiter == std::string::npos) {
        obj->setHost(host_port);
        return false;
    }
    // if found "]" then the : belongs to the host
    for (size_t i = port_delimiter; i < host_port.length(); i++) {
        if (host_port[i] == ']') {
            obj->setHost(host_port);
            return false;
        }
    }
    obj->setHost(host_port.substr(0, port_delimiter));
    const std::string port_string = host_port.substr(port_delimiter + 1);

    obj->setPort(std::stoi(port_string));

    return false;
}

ParseResult<std::vector<std::string> > Parser::Imp::parsePath(std::string path) {
    std::vector<std::string> result;
    if (path == "/") {
        // Special case of a path that is empty but needs a single
        // empty-string element to indicate that it is absolute.
        result.push_back("");
    } else if (!path.empty()) {
        for (;;) {
            auto path_delimiter = path.find('/');
            if (path_delimiter == std::string::npos) {
                result.push_back(path);
                break;
            }
            result.emplace_back(
                path.begin(),
                path.begin() + path_delimiter
            );
            path = path.substr(path_delimiter + 1);
        }
        // for (auto& segment: path) {
        //     if (!DecodeElement(segment, PCHAR_NOT_PCT_ENCODED)) {
        //         return {true, result};
        //     }
        // }
    }

    return {false, result};
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
