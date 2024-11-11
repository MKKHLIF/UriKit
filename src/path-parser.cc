#include "path-parser.h"

bool PathParser::parse(std::string &uri, std::vector<std::string> &path) {
    path.clear();

    // Special case of a path that is empty but needs a single
    // empty-string element to indicate that it is absolute.
    if (uri == "/") {
        path.emplace_back("");
        return true;
    }
    if (!uri.empty()) {
        for (;;) {
            const auto path_delimiter = uri.find('/');
            if (path_delimiter == std::string::npos) {
                path.push_back(uri);
                break;
            }
            path.emplace_back(
                uri.begin(),
                uri.begin() + static_cast<long long>(path_delimiter)
            );
            uri = uri.substr(path_delimiter + 1);
        }
        // for (auto& segment: path) {
        //     if (!DecodeElement(segment, PCHAR_NOT_PCT_ENCODED)) {
        //         return false;
        //     }
        // }
    }

    return true;
}
