#pragma once

#include <string>
#include <vector>
#include <optional>
#include <uri/uri.h>

class Parser {
public:

	static std::optional<std::string> parseScheme(const std::string& uri);

	static std::optional<std::string> parseAuthority(const std::string& uri);

	static std::optional<std::vector<std::string>> parsePath(const std::string& uri);

	static std::optional<std::string> parseHost(const std::string& authority);

	static std::optional<std::string> parsePort(const std::string& authority);

	static std::optional<std::string> parseUserInfo(const std::string& authority);
};