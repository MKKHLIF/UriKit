#include "authority-parser.h"

#include "decoder.h"
#include "sets.h"
#include "str.h"
#include "val-ipv6.h"
#include "val-port.h"

bool AuthorityParser::parse(const std::string &authority, std::vector<std::string> &components) {
    components.resize(3);

    // user:password@www.example.com:8080
    // www.example.com:8080
    // www.example.com
    // [2001:db8::1]:8080
    // [2001:db8::1]

    components[0].clear(); // userinfo
    components[1].clear(); // host
    components[2].clear(); // port

    // if (authority.empty()) return true;

    const auto user_info_delimiter = authority.find('@');
    std::string host_and_port;

    if (user_info_delimiter == std::string::npos) {
        host_and_port = authority;
    } else {
        // Extract user info and store it in components[0]
        const std::string user_info = authority.substr(0, user_info_delimiter);

        // if (!DecodeElement(user_info, USER_INFO_NOT_PCT_ENCODED)) {
        //     return false;
        // }

        components[0] = user_info;

        host_and_port = authority.substr(user_info_delimiter + 1);
    }

    std::string port;
    std::string host;
    bool host_is_reg_name = false;
    auto state = HostParsingState::FIRST_CHARACTER;

    PercentDecoder decoder;

    for (const auto c: host_and_port) {
        switch (state) {
            // first character of the host
            case HostParsingState::FIRST_CHARACTER: {
                if (c == '[') {
                    state = HostParsingState::IP_LITERAL;
                    break;
                }
                host_is_reg_name = true;
                state = HostParsingState::NOT_IP_LITERAL;
            }

            // not an IP literal
            case HostParsingState::NOT_IP_LITERAL: {
                if (c == '%') {
                    decoder = PercentDecoder();
                    state = HostParsingState::PERCENT_ENCODED_CHARACTER;
                } else if (c == ':') {
                    state = HostParsingState::PORT;
                } else {
                    if (CharacterSets::REG_NAME_NOT_PCT_ENCODED.contains(c)) {
                        host.push_back(c);
                    } else {
                        return false;
                    }
                }
            }
            break;

            case HostParsingState::PERCENT_ENCODED_CHARACTER: {
                if (!decoder.next(c)) {
                    return false;
                }
                if (decoder.done()) {
                    state = HostParsingState::NOT_IP_LITERAL;
                    host.push_back(decoder.getDecodedCharacter());
                }
            }
            break;

            case HostParsingState::IP_LITERAL: {
                if (c == 'v') {
                    host.push_back(c);
                    state = HostParsingState::IPV_FUTURE_NUMBER;
                    break;
                }
                state = HostParsingState::IPV6_ADDRESS;
            }

            case HostParsingState::IPV6_ADDRESS: {
                if (c == ']') {
                    if (!IPv6Validator::isValid(host)) {
                        return false;
                    }
                    state = HostParsingState::GARBAGE_CHECK;
                } else {
                    host.push_back(c);
                }
            }
            break;

            case HostParsingState::IPV_FUTURE_NUMBER: {
                if (c == '.') {
                    state = HostParsingState::IPV_FUTURE_BODY;
                } else if (!CharacterSets::HEXDIG.contains(c)) {
                    return false;
                }
                host.push_back(c);
            }
            break;

            case HostParsingState::IPV_FUTURE_BODY: {
                if (c == ']') {
                    state = HostParsingState::GARBAGE_CHECK;
                } else if (!CharacterSets::IPV_FUTURE_LAST_PART.contains(c)) {
                    return false;
                } else {
                    host.push_back(c);
                }
            }
            break;

            case HostParsingState::GARBAGE_CHECK: {
                // illegal to have anything else, unless it's a colon,
                // in which case it's a port delimiter
                if (c == ':') {
                    state = HostParsingState::PORT;
                } else {
                    return false;
                }
            }
            break;

            case HostParsingState::PORT: {
                port.push_back(c);
            }
            break;
        }
    }

    if (
        (state != HostParsingState::FIRST_CHARACTER)
        && (state != HostParsingState::NOT_IP_LITERAL)
        && (state != HostParsingState::GARBAGE_CHECK)
        && (state != HostParsingState::PORT)
    ) {
        // truncated or ended early
        return false;
    }

    if (host_is_reg_name) {
        host = StringExtensions::toLower(host);
    }

    if (!port.empty() && !PortValidator::isValid(port)) {
        return false;
    }

    components[1] = host;
    components[2] = port;

    return true;
}

