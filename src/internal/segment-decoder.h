#pragma once
#include <string>

#include "character.h"

class SegmentDecoder {
public:
    static bool decode(std::string &segment, const CharacterSet &allowed);
};
