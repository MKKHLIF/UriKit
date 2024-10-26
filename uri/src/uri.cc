#include <string>
#include <uri/uri.h>
#include <memory>
#include "parser_engine.h"
#include "generator.h"

struct Uri::UriImpl {
    std::string scheme_;
    std::string userInfo_;
    std::string host_;
    bool hasPort_ = false;
    uint16_t port_ = 0;
    std::vector<std::string> path_;
    bool hasQuery_ = false;
    std::string query_;
    bool hasFragment_ = false;
    std::string fragment_;

    UriImpl() = default;

    ~UriImpl() = default;

    [[nodiscard]] bool hasAuthority() const {
        return !userInfo_.empty() || !host_.empty();
    }
};

Uri::Uri() : pimpl_(std::make_unique<Uri::UriImpl>()) {
}


Uri::Uri(const Uri &other)
    : pimpl_(new UriImpl) {
    *this = other;
}

Uri::~Uri() = default;

Uri::Uri(Uri &&) noexcept = default;

Uri &Uri::operator=(const Uri &other) {
    if (this != &other) {
        *pimpl_ = *other.pimpl_;
    }
    return *this;
}

Uri &Uri::operator=(Uri &&) noexcept = default;


bool Uri::operator==(const Uri &other) const {
    return (
        (pimpl_->scheme_ == other.pimpl_->scheme_)
        && (pimpl_->userInfo_ == other.pimpl_->userInfo_)
        && (pimpl_->host_ == other.pimpl_->host_)
        && (
            (!pimpl_->hasPort_ && !other.pimpl_->hasPort_)
            || (
                (pimpl_->hasPort_ && other.pimpl_->hasPort_)
                && (pimpl_->port_ == other.pimpl_->port_)
            )
        )
        && (pimpl_->path_ == other.pimpl_->path_)
        && (
            (!pimpl_->hasQuery_ && !other.pimpl_->hasQuery_)
            || (
                (pimpl_->hasQuery_ && other.pimpl_->hasQuery_)
                && (pimpl_->query_ == other.pimpl_->query_)
            )
        )
        && (
            (!pimpl_->hasFragment_ && !other.pimpl_->hasFragment_)
            || (
                (pimpl_->hasFragment_ && other.pimpl_->hasFragment_)
                && (pimpl_->fragment_ == other.pimpl_->fragment_)
            )
        )
    );
}

bool Uri::operator!=(const Uri &other) const {
    return !(*this == other);
}

bool Uri::parse(const std::string &str) const {
    const Parser parser;
    return parser.parse(str, this);
}

std::string Uri::getScheme() const {
    return pimpl_->scheme_;
}

std::string Uri::getHost() const {
    return pimpl_->host_;
}

std::vector<std::string> Uri::getPath() const {
    return pimpl_->path_;
}

uint16_t Uri::getPort() const {
    return pimpl_->port_;
}

bool Uri::hasAuthority() const {
    return pimpl_->hasAuthority();
}

bool Uri::hasPort() const {
    return pimpl_->hasPort_;
}

bool Uri::hasQuery() const {
    return pimpl_->hasQuery_;
}

bool Uri::hasFragment() const {
    return pimpl_->hasFragment_;
}

std::string Uri::getAuthority() const {
    if (!hasAuthority()) {
        return "";
    }
    std::string authority;
    if (!pimpl_->userInfo_.empty()) {
        authority += pimpl_->userInfo_ + "@";
    }
}

std::string Uri::getUserInfo() const {
    return pimpl_->userInfo_;
}

std::string Uri::getQuery() const {
    return pimpl_->query_;
}

std::string Uri::getFragment() const {
    return pimpl_->fragment_;
}

void Uri::setScheme(const std::string &scheme) const {
    pimpl_->scheme_ = scheme;
}

void Uri::setUserInfo(const std::string &userinfo) const {
    pimpl_->userInfo_ = userinfo;
}

void Uri::setHost(const std::string &host) const {
    pimpl_->host_ = host;
}

void Uri::setPort(const uint16_t port) const {
    pimpl_->port_ = port;
    pimpl_->hasPort_ = true;
}

void Uri::clearPort() const {
    pimpl_->port_ = 0;
    pimpl_->hasPort_ = false;
}

void Uri::setPath(const std::vector<std::string> &path) const {
    pimpl_->path_ = path;
}

void Uri::clearQuery() const {
    pimpl_->query_.clear();
    pimpl_->hasQuery_ = false;
}

void Uri::setQuery(const std::string &query) const {
    pimpl_->query_ = query;
    pimpl_->hasQuery_ = true;
}

void Uri::clearFragment() const {
    pimpl_->fragment_.clear();
    pimpl_->hasFragment_ = false;
}

void Uri::clearPath() const {
    pimpl_->path_.clear();
}

void Uri::clearUserInfo() const {
    pimpl_->userInfo_.clear();
}

void Uri::clearHost() const {
    pimpl_->host_.clear();
}

void Uri::reset() const {
    pimpl_->scheme_.clear();
    pimpl_->userInfo_.clear();
    pimpl_->host_.clear();
    pimpl_->port_ = 0;
    pimpl_->path_.clear();
    pimpl_->query_.clear();
    pimpl_->fragment_.clear();
    pimpl_->hasPort_ = false;
    pimpl_->hasQuery_ = false;
    pimpl_->hasFragment_ = false;
}

void Uri::setFragment(const std::string &fragment) const {
    pimpl_->fragment_ = fragment;
    pimpl_->hasFragment_ = true;
}

std::string Uri::generateString() const {
    return URIGenerator::generate(*this);
}

bool Uri::isRelative() const {
    return false;
}

bool Uri::containsRelativePath() const {
    return false;
}

void Uri::normalizePath() {
}

Uri Uri::resolve(const Uri &relativeReference) const {
    return Uri();
}

