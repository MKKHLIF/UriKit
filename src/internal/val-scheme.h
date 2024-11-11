#pragma once
#include <string>

class SchemeValidator {
public:
	[[nodiscard]] static bool isValid(const std::string &scheme);
};
