#pragma once
#include <string>
#include "character.h"

class PercentEncoder {
public:
    static std::string encode(const std::string &segment, const CharacterSet &allowed);
};
