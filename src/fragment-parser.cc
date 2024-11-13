#include "fragment-parser.h"

bool FragmentParser::parse(std::string &uri, std::string &fragment) {
    if (const size_t pos = uri.find('#'); pos != std::string::npos) {
        fragment = uri.substr(pos + 1);
        uri = uri.substr(0, pos);
    }
    
    return true;
}
