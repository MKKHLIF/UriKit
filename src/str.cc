#include "str.h"

std::string StringExtensions::lowercase(const std::string& str)
{
	std::string result;
	result.reserve(str.size());
	for (const auto& c : str) {
		result.push_back(std::tolower(c));
	}
	return result;
}

