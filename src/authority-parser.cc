#include "authority-parser.h"

bool AuthorityParser::parse(std::string &authority, std::vector<std::string> &components) {
    // Make sure components has a size of 3, pre-allocate space
    components.resize(3);

    // Clear the vector first to ensure we're starting with fresh values
    components[0].clear(); // userinfo
    components[1].clear(); // host
    components[2].clear(); // port

    if (authority.empty()) return true;

    // Check if there is a UserInfo, and if so, extract it
    const auto user_info_delimiter = authority.find('@');
    std::string host_port;

    if (user_info_delimiter == std::string::npos) {
        // No user info, the entire authority is host and port
        host_port = authority;
    } else {
        // Extract user info and store it in components[0]
        components[0] = authority.substr(0, user_info_delimiter);
        host_port = authority.substr(user_info_delimiter + 1);
    }

    // Now parse host and port
    auto port_delimiter = host_port.find_last_of(':');

    if (port_delimiter == std::string::npos) {
        // No port specified, just the host
        components[1] = host_port; // Add host to components[1]
        components[2] = ""; // No port, so empty string for port
    } else {
        // Check if there is "]", which would indicate it's part of the host
        bool is_ipv6_host = false;
        for (size_t i = port_delimiter; i < host_port.length(); i++) {
            if (host_port[i] == ']') {
                is_ipv6_host = true;
                break;
            }
        }

        if (is_ipv6_host) {
            // The ":" is part of the host, so no port present
            components[1] = host_port; // Add host to components[1]
            components[2] = ""; // No port
        } else {
            // Extract the host part and the port part
            components[1] = host_port.substr(0, port_delimiter); // host
            components[2] = host_port.substr(port_delimiter + 1); // port
        }
    }

    return true;
}

