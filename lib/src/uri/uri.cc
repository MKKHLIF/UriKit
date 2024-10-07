#include <string>
#include <uri/uri.h>
#include <memory>
#include "../validation/syntax_validator.h"
#include "../parser/parser.h"

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

    UriImpl() = default;
    ~UriImpl() = default;

    bool HasAuthority() const
    {
        return !authority_.empty();
    }
};

Uri::Uri() : pimpl_(std::make_unique<Uri::UriImpl>())
{
}

Uri::~Uri() = default;

// To-do: call parser helper and fill the impl. and set other properties accordingly.
bool Uri::parse(const std::string& uri) const
{
    const auto result = Parser::parseScheme(uri);
    if (!result.status) return false;

    const std::string scheme = result.content;
    if (!SyntaxValidator::validateScheme(scheme)) return false;
    this->pimpl_->scheme_ = scheme;

    return true;
}

std::string Uri::getScheme() const
{
    return this->pimpl_->scheme_;
}

std::string Uri::getHost() const
{
    return this->pimpl_->host_;
}

std::vector<std::string> Uri::getPath() const
{
    return this->pimpl_->path_;
}

