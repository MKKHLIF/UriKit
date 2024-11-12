#include <sstream>
#include "gen.h"

#include "encoder.h"
#include "sets.h"
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
			buffer << PercentEncoder::encode(uri.getUserInfo(), CharacterSets::USER_INFO_NOT_PCT_ENCODED) << '@';
		}
		if (!uri.getHost().empty()) {
			// case when host is an IPv6 address
			if (IPv6Validator::isValid(uri.getHost())) {
				buffer << '[' << StringExtensions::toLower(uri.getHost()) << ']';
			} else {
				buffer << PercentEncoder::encode(uri.getHost(), CharacterSets::REG_NAME_NOT_PCT_ENCODED);
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
		buffer << PercentEncoder::encode(segment, CharacterSets::PCHAR_NOT_PCT_ENCODED);
		if (i + 1 < uri.getPath().size()) {
			buffer << '/';
		}
		++i;
	}
	if (uri.hasQuery()) {
		buffer << '?' << PercentEncoder::encode(uri.getQuery(), CharacterSets::QUERY_NOT_PCT_ENCODED_WITHOUT_PLUS);
	}
	if (uri.hasFragment()) {
		buffer << '#' << PercentEncoder::encode(uri.getFragment(), CharacterSets::QUERY_OR_FRAGMENT_NOT_PCT_ENCODED);
	}
	return buffer.str();
}

