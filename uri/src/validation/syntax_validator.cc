#include "syntax_validator.h"
#include <string>

#include "../characters/sets.h"


bool SyntaxValidator::validateScheme(const std::string &scheme) {
    if (scheme.empty()) return false;

    if (!CharacterSets::ALPHA.contains(scheme[0])) return false;

    for (size_t i = 1; i < scheme.size(); ++i) {
        if (!CharacterSets::SCHEME_NOT_FIRST.contains(scheme[i])) return false;
    }
    return true;
}
