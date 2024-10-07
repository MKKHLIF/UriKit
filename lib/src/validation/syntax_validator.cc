#include "syntax_validator.h"
#include <string>

const CharacterSet SyntaxValidator::ALPHA{CharacterSet('a', 'z'), CharacterSet('A', 'Z')};
const CharacterSet SyntaxValidator::DIGIT('0', '9');
const CharacterSet SyntaxValidator::SCHEME_NOT_FIRST{ALPHA, DIGIT, '+', '-', '.',};


bool SyntaxValidator::validateScheme(const std::string& scheme)
{
    if (scheme.empty()) return false;

    if (!ALPHA.contains(scheme[0])) return false;

    for (size_t i = 1; i < scheme.size(); ++i)
    {
        if (!SCHEME_NOT_FIRST.contains(scheme[i])) return false;
    }
    return true;
}
