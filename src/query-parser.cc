#include "query-parser.h"

bool QueryParser::parse(const std::string &uri, std::string &query) {
    query.clear();
    if (!uri.empty()) {
        query = uri.substr(1);
    }
    return true;
}
