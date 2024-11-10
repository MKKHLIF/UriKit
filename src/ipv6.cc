#include "ipv6.h"
#include <regex>
#include "ipv4.h"
#include "sets.h"

bool IPv6Validator::isValid(const std::string &address)  {
    ValidationContext ctx;

    for (const char c : address) {
        bool valid = false;
        
        switch (ctx.state) {
            case ValidationState::NoGroupsYet:
                valid = handleNoGroupsYet(c, ctx);
            break;
            case ValidationState::ColonButNoGroupsYet:
                valid = handleColonButNoGroupsYet(c, ctx);
            break;
            case ValidationState::AfterDoubleColon:
                valid = handleAfterDoubleColon(c, ctx);
            break;
            case ValidationState::InGroupNotIPv4:
                valid = handleInGroupNotIPv4(c, ctx);
            break;
            case ValidationState::InGroupCouldBeIPv4:
                valid = handleInGroupCouldBeIPv4(c, ctx);
            break;
            case ValidationState::ColonAfterGroup:
                valid = handleColonAfterGroup(c, ctx);
            break;
        }

        if (!valid) return false;

        if (ctx.ipv4Found) break;
        ctx.position++;
    }

    return finalizeValidation(ctx, address);
}

bool IPv6Validator::handleNoGroupsYet(const char c, ValidationContext& ctx) {
    if (c == ':') {
        ctx.state = ValidationState::ColonButNoGroupsYet;
        return true;
    }

    if (CharacterSets::DIGIT.contains(c)) {
        ctx.ipv4Start = ctx.position;
        ctx.numDigits = 1;
        ctx.state = ValidationState::InGroupCouldBeIPv4;
        return true;
    }

    if (CharacterSets::HEXDIG.contains(c)) {
        ctx.numDigits = 1;
        ctx.state = ValidationState::InGroupNotIPv4;
        return true;
    }

    return false;
}

bool IPv6Validator::handleColonButNoGroupsYet(const char c, ValidationContext& ctx) {
    if (c == ':') {
        ctx.doubleColonFound = true;
        ctx.state = ValidationState::AfterDoubleColon;
        return true;
    }
    return false;
}

bool IPv6Validator::handleAfterDoubleColon(char c, ValidationContext& ctx) {
    if (CharacterSets::DIGIT.contains(c)) {
        ctx.ipv4Start = ctx.position;
        ctx.numDigits++;
        ctx.state = ValidationState::InGroupCouldBeIPv4;
        return ctx.numDigits <= 4;
    }

    if (CharacterSets::HEXDIG.contains(c)) {
        ctx.numDigits++;
        ctx.state = ValidationState::InGroupNotIPv4;
        return ctx.numDigits <= 4;
    }

    return false;
}

bool IPv6Validator::handleInGroupNotIPv4(const char c, ValidationContext& ctx) {
    if (c == ':') {
        ctx.numDigits = 0;
        ctx.numGroups++;
        ctx.state = ValidationState::ColonAfterGroup;
        return true;
    }

    if (CharacterSets::HEXDIG.contains(c)) {
        ctx.numDigits++;
        return ctx.numDigits <= 4;
    }

    return false;
}

bool IPv6Validator::handleInGroupCouldBeIPv4(const char c, ValidationContext& ctx) {
    if (c == ':') {
        ctx.numDigits = 0;
        ctx.numGroups++;
        ctx.state = ValidationState::ColonAfterGroup;
        return true;
    }

    if (c == '.') {
        ctx.ipv4Found = true;
        return true;
    }

    if (CharacterSets::DIGIT.contains(c)) {
        ctx.numDigits++;
        return ctx.numDigits <= 4;
    }

    if (CharacterSets::HEXDIG.contains(c)) {
        ctx.numDigits++;
        ctx.state = ValidationState::InGroupNotIPv4;
        return ctx.numDigits <= 4;
    }

    return false;
}

bool IPv6Validator::handleColonAfterGroup(const char c, ValidationContext& ctx) {
    if (c == ':') {
        if (ctx.doubleColonFound) {
            return false;
        }
        ctx.doubleColonFound = true;
        ctx.state = ValidationState::AfterDoubleColon;
        return true;
    }
    
    if (CharacterSets::DIGIT.contains(c)) {
        ctx.ipv4Start = ctx.position;
        ctx.numDigits = 1;
        ctx.state = ValidationState::InGroupCouldBeIPv4;
        return true;
    }
    
    if (CharacterSets::HEXDIG.contains(c)) {
        ctx.numDigits = 1;
        ctx.state = ValidationState::InGroupNotIPv4;
        return true;
    }
    
    return false;
}

bool IPv6Validator::finalizeValidation(const ValidationContext& ctx, const std::string& address) {
    // Handle trailing single colon
    if (ctx.position == address.length() &&
        (ctx.state == ValidationState::ColonButNoGroupsYet || 
         ctx.state == ValidationState::ColonAfterGroup)) {
        return false;
    }

    size_t finalGroups = ctx.numGroups;

    // Count the last group if we were in the middle of one
    if (ctx.state == ValidationState::InGroupNotIPv4 || 
        ctx.state == ValidationState::InGroupCouldBeIPv4) {
        finalGroups++;
    }

    // Handle IPv4 address if found
    if (ctx.ipv4Found) {
        if (!IPv4Validator::isValid(address.substr(ctx.ipv4Start))) {
            return false;
        }
        finalGroups += 2;
    }

    // Validate total number of groups
    if (ctx.doubleColonFound) {
        return finalGroups <= 7;
    }
    return finalGroups == 8;
}
