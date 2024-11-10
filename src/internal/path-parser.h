#pragma once
#include <string>
#include <vector>

class PathParser {
public:
     [[nodiscard]] static bool parse(std::string &uri, std::vector<std::string> &path);
};
