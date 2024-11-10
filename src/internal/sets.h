#pragma once
#include "character.h"

class CharacterSets {
public:
    static const CharacterSet ALPHA;
    static const CharacterSet DIGIT;
    static const CharacterSet SCHEME_NOT_FIRST;

    static const CharacterSet HEXDIG;
    static const CharacterSet UNRESERVED;
    static const CharacterSet SUB_DELIMS;

    static const CharacterSet PCHAR_NOT_PCT_ENCODED;
    static const CharacterSet QUERY_OR_FRAGMENT_NOT_PCT_ENCODED;
    static const CharacterSet QUERY_NOT_PCT_ENCODED_WITHOUT_PLUS;
    static const CharacterSet USER_INFO_NOT_PCT_ENCODED;
    static const CharacterSet REG_NAME_NOT_PCT_ENCODED;

    static const CharacterSet IPV_FUTURE_LAST_PART;
};

