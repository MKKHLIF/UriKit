#include <sstream>
#include "gen.h"
#include "str.h"
#include "val-ipv6.h"

std::string URIGenerator::generate(const Uri &uri) {
	std::ostringstream buffer;
	if (uri.hasScheme()) {
		buffer << uri.getScheme() << ':';
	}
	if (uri.hasAuthority()) {
		buffer << "//";
		if (!uri.getUserInfo().empty()) {
			// buffer << EncodeElement(impl_->userInfo, USER_INFO_NOT_PCT_ENCODED) << '@';
		}
		if (!uri.getHost().empty()) {
			// case when host is an IPv6 address
			if (IPv6Validator::isValid(uri.getHost())) {
				buffer << '[' << StringExtensions::toLower(uri.getHost()) << ']';
			} else {
				// buffer << EncodeElement(uri.getHost(), CharacterSets::REG_NAME_NOT_PCT_ENCODED);
			}
		}
		if (uri.hasPort()) {
			buffer << ':' << uri.getPort();
		}
	}
	// Special case: absolute but otherwise empty path.
	if (uri.isPathAbsolute() && uri.getPath().size() == 1) {
		buffer << '/';
	}

	size_t i = 0;
	for (const auto &segment: uri.getPath()) {
		// buffer << EncodeElement(segment, CharacterSets::PCHAR_NOT_PCT_ENCODED);
		if (i + 1 < uri.getPath().size()) {
			buffer << '/';
		}
		++i;
	}
	if (uri.hasQuery()) {
		// buffer << '?' << EncodeElement(uri.getQuery(), CharacterSets::QUERY_NOT_PCT_ENCODED_WITHOUT_PLUS);
	}
	if (uri.hasFragment()) {
		// buffer << '#' << EncodeElement(uri.getFragment(), CharacterSets::QUERY_OR_FRAGMENT_NOT_PCT_ENCODED);
	}
	return buffer.str();
}

