#include "character.h"
#include "character_sets.h"

const CharacterSet CharacterSets::ALPHA{CharacterSet('a', 'z'), CharacterSet('A', 'Z')};
const CharacterSet CharacterSets::DIGIT('0', '9');
const CharacterSet CharacterSets::SCHEME_NOT_FIRST{ALPHA, DIGIT, '+', '-', '.',};
