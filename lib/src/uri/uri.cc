#include <string>
#include <uri/uri.h>
#include <memory>
#include "../validation/syntax_validator.h"
#include "../parser/parser.h"
#include "../generator/generator.h"

struct Uri::UriImpl
{
    std::string scheme_;
    std::string authority_;
    std::string userInfo_;
    std::string host_;
    bool hasPort_ = false;
    uint16_t port_ = 0;
    std::vector<std::string> path_;
    bool hasQuery_ = false;
    std::string query_;
    bool hasFragment_ = false;
    std::string fragment_;

    size_t cursor = 0;

    UriImpl() = default;
    ~UriImpl() = default;

    [[nodiscard]] bool hasAuthority() const
    {
        return !authority_.empty();
    }
};

Uri::Uri() : pimpl_(std::make_unique<Uri::UriImpl>())
{
}

Uri::~Uri() = default;

bool Uri::parse(const std::string& uri) const
{
    const auto result = Parser::parseScheme(uri, pimpl_->cursor);
    if (result.error) return false;

    const std::string scheme = result.content;
    if (!SyntaxValidator::validateScheme(scheme)) return false;
    pimpl_->scheme_ = scheme;
    pimpl_->cursor += scheme.size();


    return true;
}

std::string Uri::getScheme() const
{
    return pimpl_->scheme_;
}

std::string Uri::getHost() const
{
    return pimpl_->host_;
}

std::vector<std::string> Uri::getPath() const
{
    return pimpl_->path_;
}

uint16_t Uri::getPort() const
{
    return pimpl_->port_;
}

bool Uri::hasAuthority() const
{
    return pimpl_->hasAuthority();
}

bool Uri::hasPort() const
{
    return pimpl_->hasPort_;
}

bool Uri::hasQuery() const
{
    return pimpl_->hasQuery_;
}

bool Uri::hasFragment() const
{
    return pimpl_->hasFragment_;
}

std::string Uri::getAuthority() const
{
    return pimpl_->authority_;
}

std::string Uri::getUserInfo() const
{
    return pimpl_->userInfo_;
}

std::string Uri::getQuery() const
{
    return pimpl_->query_;
}

std::string Uri::getFragment() const
{
    return pimpl_->fragment_;
}

void Uri::setScheme(const std::string& scheme)
{
}

void Uri::setUserInfo(const std::string& userinfo)
{
}

void Uri::setHost(const std::string& host)
{
}

void Uri::setPort(uint16_t port)
{
}

void Uri::clearPort()
{
}

void Uri::setPath(const std::vector<std::string>& path)
{
}

void Uri::clearQuery()
{
}

void Uri::setQuery(const std::string& query)
{
}

void Uri::clearFragment()
{
}

void Uri::setFragment(const std::string& fragment)
{
    pimpl_->fragment_ = fragment;
    pimpl_->hasFragment_ = true;
}

std::string Uri::generateString() const
{
	return URIGenerator::generate(*this);
}

bool Uri::isRelative() const
{
    return false;
}

bool Uri::containsRelativePath() const
{
}

void Uri::normalizePath()
{
}

Uri Uri::resolve(const Uri& relativeReference) const
{
}

