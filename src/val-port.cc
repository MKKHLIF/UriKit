#include "val-port.h"
#include <stdexcept>

#include <limits>  // for std::numeric_limits

bool PortValidator::isValid(const std::string &port) {
    // handle empty string and non-numeric characters
    if (port.empty() || port.find_first_not_of("0123456789") != std::string::npos) {
        return false;
    }

    if (port.length() > 1 && port[0] == '0') {
        return false; // Leading zero detected
    }

    try {
        // Convert string to unsigned long
        const unsigned long portNumber = std::stoul(port);

        // Check if the number is within valid range (1 to 65535)
        if (portNumber < 1 || portNumber > 65535) {
            return false;
        }

        return true;
    } catch (const std::invalid_argument &) {
        // The string was not a valid number
        return false;
    } catch (const std::out_of_range &) {
        // The number was too large to fit in unsigned long
        return false;
    } catch (...) {
        // Any other exception
        return false;
    }
}
