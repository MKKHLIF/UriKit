#pragma once
#include <string>

class IPv6Validator {
public:
    static bool isValid(const std::string &address);

private:
    enum class ValidationState {
        NoGroupsYet,
        ColonButNoGroupsYet,
        AfterDoubleColon,
        InGroupNotIPv4,
        InGroupCouldBeIPv4,
        ColonAfterGroup
    };
    struct ValidationContext {
        ValidationState state = ValidationState::NoGroupsYet;
        size_t numGroups = 0;
        size_t numDigits = 0;
        bool doubleColonFound = false;
        size_t ipv4Start = 0;
        size_t position = 0;
        bool ipv4Found = false;
    };

    static bool handleNoGroupsYet(char c, ValidationContext& ctx);
    static bool handleColonButNoGroupsYet(char c, ValidationContext& ctx);
    static bool handleAfterDoubleColon(char c, ValidationContext& ctx);
    static bool handleInGroupNotIPv4(char c, ValidationContext& ctx);
    static bool handleInGroupCouldBeIPv4(char c, ValidationContext& ctx);
    static bool handleColonAfterGroup(char c, ValidationContext& ctx);
    static bool finalizeValidation(const ValidationContext& ctx, const std::string& address);

};


