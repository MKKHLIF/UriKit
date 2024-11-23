#pragma once

#include <initializer_list>
#include <memory>

/**
 * @class CharacterSet
 * @brief A class representing a collection of characters and providing operations to manage them.
 *
 * The `CharacterSet` class provides a flexible way to represent sets of characters. It supports various
 * initialization methods, including single characters, ranges of characters, and combinations of other
 * `CharacterSet` instances. It offers a method to check if a specific character is contained within the set.
 */
class CharacterSet {
public:
 /**
  * @brief Destructor
  * @details Cleans up the internal resources used by the `CharacterSet` instance.
  */
 ~CharacterSet() noexcept;

 /**
  * @brief Copy constructor
  * @param other The `CharacterSet` instance to copy.
  * @details Creates a new `CharacterSet` as a copy of another one.
  */
 CharacterSet(const CharacterSet &);

 /**
  * @brief Move constructor
  * @param other The `CharacterSet` instance to move.
  * @details Transfers ownership of resources from another `CharacterSet` instance.
  */
 CharacterSet(CharacterSet &&) noexcept;

 /**
  * @brief Copy assignment operator
  * @param other The `CharacterSet` instance to copy.
  * @return Reference to the current `CharacterSet` instance.
  * @details Assigns the values of one `CharacterSet` to another.
  */
 CharacterSet &operator=(const CharacterSet &);

 /**
  * @brief Move assignment operator
  * @param other The `CharacterSet` instance to move.
  * @return Reference to the current `CharacterSet` instance.
  * @details Transfers the resources from one `CharacterSet` to another.
  */
 CharacterSet &operator=(CharacterSet &&) noexcept;

 /**
  * @brief Default constructor
  * @details Initializes an empty `CharacterSet`.
  */
 CharacterSet();

 /**
  * @brief Constructor with a single character
  * @param c The character to insert into the set.
  * @details Initializes the `CharacterSet` with a single character.
  */
 CharacterSet(char c);

 /**
  * @brief Constructor with a character range
  * @param start The first character of the range (inclusive).
  * @param end The last character of the range (inclusive).
  * @details Initializes the `CharacterSet` with all characters in the specified range.
  */
 CharacterSet(char start, char end);

 /**
  * @brief Constructor with a list of `CharacterSet` instances
  * @param characterSets The list of `CharacterSet` instances to combine.
  * @details Initializes the `CharacterSet` by combining the characters from the provided list of `CharacterSet` instances.
  */
 CharacterSet(std::initializer_list<const CharacterSet> characterSets);

 /**
  * @brief Checks if the `CharacterSet` contains a specific character.
  * @param c The character to check.
  * @return true if the character is contained in the set, false otherwise.
  */
 [[nodiscard]] bool contains(char c) const;

private:
 /**
  * @struct Impl
  * @brief Internal implementation of the `CharacterSet` class.
  *
  * The `Impl` structure holds the actual character set, which is an unordered set of characters.
  */
 struct Impl;

 std::unique_ptr<Impl> impl_;
};
