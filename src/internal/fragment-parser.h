#pragma once
#include <string>

class FragmentParser {
public:
     [[nodiscard]] static bool parse(std::string &uri, std::string &fragment);
};
