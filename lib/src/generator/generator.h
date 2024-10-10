#pragma once

#include <string>
#include <uri/uri.h>
class URIGenerator {
public:
	static std::string generate(const Uri& uri);
};