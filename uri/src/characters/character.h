#pragma once

#include <initializer_list>
#include <memory>

class CharacterSet {
public:

    // Life cycle
    ~CharacterSet() noexcept;
    CharacterSet(const CharacterSet&);
    CharacterSet(CharacterSet&&) noexcept;
    CharacterSet& operator=(const CharacterSet&);
    CharacterSet& operator=(CharacterSet&&) noexcept;

    // Constructors
    CharacterSet();
    CharacterSet(char c);
    CharacterSet(char start, char end);
    CharacterSet(std::initializer_list< const CharacterSet > characterSets);
    // Methods
    bool contains(char c) const;


private:
    struct Impl;
    std::unique_ptr< Impl > impl_;

};