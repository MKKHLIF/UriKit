#pragma once
#include <string>
#include "character.h"

class SyntaxValidator {
public: 
	static bool validateScheme(const std::string& scheme);

private:
	static const CharacterSet ALPHA;
	static const CharacterSet DIGIT;
	static const CharacterSet SCHEME_NOT_FIRST;

};
