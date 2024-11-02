#pragma once
#include <string>

class IPv6Validator {
public:
    static bool isValid(const std::string &address);

private:
    enum class ValidationState {
        NO_GROUPS_YET,
        COLON_BUT_NO_GROUPS_YET,
        AFTER_DOUBLE_COLON,
        IN_GROUP_NOT_IPV4,
        IN_GROUP_COULD_BE_IPV4,
        COLON_AFTER_GROUP,
    };
};


