#include "scheme-parser.h"

#include "str.h"
#include "val-scheme.h"

bool SchemeParser::parse(std::string &uri, std::string &scheme) {
    // "https://www.google.com/search?q=uri"
    // "file:///C:/Users/Example/Documents/Projects/2024/Report.pdf"
    // "mailto:user@example.com"
    // "foo/bar"
    scheme.clear();

    auto authority_or_path_start = uri.find('/');

    if (authority_or_path_start == std::string::npos) {
        authority_or_path_start = uri.length();
    }

    const auto scheme_end = uri.substr(0, authority_or_path_start).find(':');

    if (scheme_end == std::string::npos) return true;

    scheme = uri.substr(0, scheme_end);

    scheme = StringExtensions::toLower(scheme);

    if (!SyntaxValidator::validateScheme(scheme)) {
        scheme.clear();
        return false;
    }
    //remove scheme from uri
    uri = uri.substr(scheme_end + 1);
    // skip // if exists
    if (uri.size() >= 2 && uri[0] == '/' && uri[1] == '/') {
        uri = uri.substr(2);
    }

    return true;
}
