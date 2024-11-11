#include "val-port.h"
#include <stdexcept>

bool PortValidator::isValid(const std::string &port) {
    try {
        const auto portNumber = static_cast<uint16_t>(std::stoul(port));
        return portNumber >= 1 && portNumber <= 65535;
    } catch (const std::invalid_argument &) {
        return false;
    } catch (const std::out_of_range &) {
        return false;
    } catch (const std::exception &e) {
        return false;
    }
}
