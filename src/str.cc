#include "str.h"

#include <algorithm>

std::string StringExtensions::toLower(const std::string &str) {
	std::string result = str;
	std::ranges::transform(result, result.begin(), [](const unsigned char c) {
		return std::tolower(c);
	});
	return result;
}


