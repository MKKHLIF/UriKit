#include "generator.h"

std::string URIGenerator::generate(const Uri& uri)
{
	std::string result;
	result += uri.getScheme();
	result += "://";
	result += uri.getHost();
	for (const auto& path : uri.getPath())
	{
		result += "/";
		result += path;
	}
	return result;
}
