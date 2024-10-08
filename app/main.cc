#include <iostream>
#include <uri/uri.h>

std::string scheme;

bool ParseScheme(const std::string& uriString, std::string& rest)
{
	// Limit our search so we don't scan into the authority
	// or path elements, because these may have the colon
	// character as well, which we might misinterpret
	// as the scheme delimiter.
	auto authorityOrPathDelimiterStart = uriString.find('/');
	if (authorityOrPathDelimiterStart == std::string::npos)
	{
		authorityOrPathDelimiterStart = uriString.length();
	}
	const auto schemeEnd = uriString.substr(0, authorityOrPathDelimiterStart).find(':');
	if (schemeEnd == std::string::npos)
	{
		scheme.clear();
		rest = uriString;
	}
	else
	{
		scheme = uriString.substr(0, schemeEnd);

		rest = uriString.substr(schemeEnd + 1);
	}
	return true;
}

int main()
{
	std::string uri = "htt++ps://www.google.com/search?q=cpp+uri+parser";
	std::string rest;
	ParseScheme(uri, rest);

	const auto pathEnd = rest.find_first_of("?#");
	const auto authorityAndPathString = rest.substr(0, pathEnd);

	std::cout << "Scheme: " << scheme << std::endl;
	std::cout << "Rest: " << rest << std::endl;
	std::cout << "Authority and Path: " << authorityAndPathString << std::endl;

	return 0;
}
