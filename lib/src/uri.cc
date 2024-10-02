#include <string>
#include <uri/uri.h>

struct prism::Uri::UriImpl {
    std::string scheme;
    std::string host;
    std::vector<std::string> path;

    UriImpl() = default;

    ~UriImpl() = default;
};

prism::Uri::Uri() : pimpl_(std::make_unique<UriImpl>()) {
}

prism::Uri::~Uri() = default;

bool prism::Uri::parseString(const std::string &uri) {
    const std::string scheme = parseScheme(uri);
    if (scheme.empty()) {
        return false;
    }
    this->pimpl_->scheme = scheme;


    return true;
}

std::string prism::Uri::getScheme() const {
    return this->pimpl_->scheme;
}

std::string prism::Uri::getHost() const {
    return this->pimpl_->host;
}

std::vector<std::string> prism::Uri::getPath() const {
    return this->pimpl_->path;
}

std::string prism::Uri::parseScheme(const std::string &uri) {
    std::string scheme;
    const auto pos = uri.find(':');
    if (pos != std::string::npos) {
        scheme = uri.substr(0, pos);
    }
    return scheme;
}


std::string prism::Uri::parseAuthority(const std::string &uri) {
    std::string authority;
    const auto pos = uri.find("://");
    if (pos == std::string::npos) return authority;
    const auto start = pos + 3;
    if (start >= uri.size()) return authority;
    const auto end = uri.find_first_of("/?#", start);
    if (end == std::string::npos) {
        authority = uri.substr(start);
    } else {
        authority = uri.substr(start, end - start);
    }
    return authority;
}

std::vector<std::string> prism::Uri::parsePath(const std::string &uri) {
    std::vector<std::string> path; // Vector to store the path segments

    // Find the position of "://", which indicates the end of the scheme
    auto schemeEnd = uri.find("://");
    if (schemeEnd == std::string::npos) return path; // Return empty path if scheme is not found

    // Start position after the scheme
    auto start = schemeEnd + 3;
    if (start >= uri.size()) return path; // Return empty path if URI ends after the scheme

    // Find the start of the path
    auto pathStart = uri.find('/', start);
    if (pathStart == std::string::npos) return path; // Return empty path if no '/' is found

    // Find the end of the path, which could be indicated by '?' or '#'
    auto pathEnd = uri.find_first_of("?#", pathStart);
    if (pathEnd == std::string::npos) {
        pathEnd = uri.size(); // If no '?' or '#' is found, the path ends at the end of the URI
    }

    // Extract the path string
    const auto pathStr = uri.substr(pathStart, pathEnd - pathStart);
    size_t segmentStart = 0;

    // Loop to split the path into segments
    while (segmentStart < pathStr.size()) {
        auto segmentEnd = pathStr.find('/', segmentStart);
        if (segmentEnd == std::string::npos) {
            path.push_back(pathStr.substr(segmentStart)); // Add the last segment
            break;
        }
        path.push_back(pathStr.substr(segmentStart, segmentEnd - segmentStart)); // Add the segment
        segmentStart = segmentEnd + 1; // Move to the next segment
    }

    return path; // Return the vector of path segments
}


std::string prism::Uri::parseUserInfo(const std::string &authority) {
    // authority = [ userinfo "@" ] host [ ":" port ]
    // user:password@www.example.com:8080
    // www.example.com:8080
    std::string userInfo;
    const auto at_pos = authority.find('@');
    if (at_pos == std::string::npos) return userInfo;
    userInfo = authority.substr(0, at_pos);
    return userInfo;
}


std::string prism::Uri::parseHost(const std::string &authority) {
    std::string host;
    const auto at_pos = authority.find('@');
    const auto colon_pos = authority.find_last_of(':');

    const auto hostStart = at_pos == std::string::npos ? 0 : at_pos + 1;
    auto hostEnd = colon_pos == std::string::npos ? authority.size() : colon_pos;

    if (authority[hostStart] == '[') {
        hostEnd = authority.find(']', hostStart);
        if (hostEnd == std::string::npos) return host;
        hostEnd++;
    }
    return authority.substr(hostStart, hostEnd - hostStart);
}

std::string prism::Uri::parsePort(const std::string &authority) {
    // temp dummy default port
    std::string port = "80";
    const auto at_pos = authority.find('@');
    auto startSearch = at_pos == std::string::npos ? 0 : at_pos + 1;
    if (authority[startSearch] == '[') {
        startSearch = authority.find(']', startSearch);
        if (startSearch == std::string::npos) return port;
    }

    const auto colon_pos = authority.find(':', startSearch);

    if (colon_pos == std::string::npos) return port;
    return authority.substr(colon_pos + 1);
}