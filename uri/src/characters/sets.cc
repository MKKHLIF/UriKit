#include "character.h"
#include "sets.h"

const CharacterSet CharacterSets::ALPHA{
    CharacterSet('a', 'z'),
    CharacterSet('A', 'Z')
};
const CharacterSet CharacterSets::DIGIT('0', '9');
const CharacterSet CharacterSets::SCHEME_NOT_FIRST{
    ALPHA,
    DIGIT,
    '+', '-', '.',
};
const CharacterSet CharacterSets::HEXDIG{
    CharacterSet('0', '9'),
    CharacterSet('A', 'F'),
    CharacterSet('a', 'f')
};
const CharacterSet CharacterSets::UNRESERVED{
    ALPHA,
    DIGIT,
    '-', '.', '_', '~'
};
const CharacterSet CharacterSets::SUB_DELIMS{
    '!', '$', '&', '\'', '(', ')',
    '*', '+', ',', ';', '='
};
const CharacterSet CharacterSets::PCHAR_NOT_PCT_ENCODED{
    UNRESERVED,
    SUB_DELIMS,
    ':', '@'
};
const CharacterSet CharacterSets::QUERY_OR_FRAGMENT_NOT_PCT_ENCODED{
    PCHAR_NOT_PCT_ENCODED,
    '/', '?'
};
const CharacterSet CharacterSets::QUERY_NOT_PCT_ENCODED_WITHOUT_PLUS{
    UNRESERVED,
    '!', '$', '&', '\'', '(', ')',
    '*', ',', ';', '=',
    ':', '@',
    '/', '?'
};
const CharacterSet CharacterSets::USER_INFO_NOT_PCT_ENCODED{
    UNRESERVED,
    SUB_DELIMS,
    ':',
};
const CharacterSet CharacterSets::REG_NAME_NOT_PCT_ENCODED{
    UNRESERVED,
    SUB_DELIMS
};
const CharacterSet CharacterSets::IPV_FUTURE_LAST_PART{
    UNRESERVED,
    SUB_DELIMS,
    ':'
};
