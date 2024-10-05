#include <uri/uri.h>

class Uri::Impl {
public:
    std::string scheme_;
    std::string userInfo_;
    std::string host_;
    bool hasPort_ = false;
    uint16_t port_ = 0;
    std::vector< std::string > path_;
    bool hasQuery_ = false;
    std::string query_;
    bool hasFragment_ = false;
    std::string fragment_;

    UriImpl() = default;

    ~UriImpl() = default;
};
