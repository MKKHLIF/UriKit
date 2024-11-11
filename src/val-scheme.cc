#include "val-scheme.h"
#include <string>

#include "sets.h"


bool SchemeValidator::isValid(const std::string &scheme) {
    if (scheme.empty()) return false;

    if (!CharacterSets::ALPHA.contains(scheme[0])) return false;

    for (size_t i = 1; i < scheme.size(); ++i) {
        if (!CharacterSets::SCHEME_NOT_FIRST.contains(scheme[i])) return false;
    }
    return true;
}
