#include <string>
#include <uri/uri.h>

Uri::Uri() : pimpl_(std::make_unique<UriImpl>()) {
}

Uri::~Uri() = default;

bool Uri::parseString(const std::string &uri) {
   // To-do: call parser helper and fill the impl. and set other properties accordingly.

    return true;
}

std::string Uri::getScheme() const {
    return this->pimpl_->scheme;
}

std::string Uri::getHost() const {
    return this->pimpl_->host;
}

std::vector<std::string> Uri::getPath() const {
    return this->pimpl_->path;
}

