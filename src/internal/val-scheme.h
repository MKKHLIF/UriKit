#pragma once
#include <string>

class SyntaxValidator {
public:
	[[nodiscard]] static bool validateScheme(const std::string &scheme);
};
