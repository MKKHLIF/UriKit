#include "character.h"
#include <unordered_set>

struct CharacterSet::Impl
{
    std::unordered_set<char> characters;
};

CharacterSet::~CharacterSet() noexcept = default;

CharacterSet::CharacterSet(const CharacterSet& other) : impl_(new Impl(*other.impl_))
{
}

CharacterSet::CharacterSet(CharacterSet&& other) noexcept = default;

CharacterSet& CharacterSet::operator=(const CharacterSet& other)
{
    if (this != &other)
    {
        *impl_ = *other.impl_;
    }
    return *this;
}

CharacterSet& CharacterSet::operator=(CharacterSet&& other) noexcept = default;

CharacterSet::CharacterSet()
    : impl_(new Impl)
{
}

CharacterSet::CharacterSet(const char c)
    : impl_(new Impl)
{
    (void)impl_->characters.insert(c);
}

CharacterSet::CharacterSet(char first, char last)
    : impl_(new Impl)
{
    if (first > last)
    {
        std::swap(first, last);
    }
    for (char c = first; c < last + 1; ++c)
    {
        (void)impl_->characters.insert(c);
    }
}

CharacterSet::CharacterSet(const std::initializer_list<const CharacterSet> characterSets): impl_(new Impl)
{
    for (
        auto characterSet = characterSets.begin();
        characterSet != characterSets.end();
        ++characterSet
    )
    {
        impl_->characters.insert(
            characterSet->impl_->characters.begin(),
            characterSet->impl_->characters.end()
        );
    }
}

bool CharacterSet::contains(char c) const
{
    return impl_->characters.find(c) != impl_->characters.end();
}
