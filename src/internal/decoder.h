#pragma once
#include <memory>

/**
 * @class PercentDecoder
 * @brief A class for decoding percent-encoded characters (URL encoding).
 *
 * The `PercentDecoder` class facilitates the decoding of percent-encoded characters (e.g., `%20` for a space)
 * in a stream. It processes one character at a time, accumulates the value of the decoded character, and
 * provides methods to check if the decoding is complete and retrieve the decoded character.
 */
class PercentDecoder {
public:
 /**
  * @brief Destructor
  * @details Cleans up the internal resources used by the `PercentDecoder` instance.
  */
 ~PercentDecoder() noexcept;

 /**
  * @brief Deleted copy constructor
  * @details Copying of `PercentDecoder` instances is not allowed.
  */
 PercentDecoder(const PercentDecoder &) = delete;

 /**
  * @brief Move constructor
  * @param other The `PercentDecoder` instance to move.
  * @details Transfers ownership of resources from another `PercentDecoder` instance.
  */
 PercentDecoder(PercentDecoder &&) noexcept;

 /**
  * @brief Deleted copy assignment operator
  * @details Copy assignment of `PercentDecoder` instances is not allowed.
  */
 PercentDecoder &operator=(const PercentDecoder &) = delete;

 /**
  * @brief Move assignment operator
  * @param other The `PercentDecoder` instance to move.
  * @return Reference to the current `PercentDecoder` instance.
  * @details Transfers the resources from one `PercentDecoder` to another.
  */
 PercentDecoder &operator=(PercentDecoder &&) noexcept;

 /**
  * @brief Default constructor
  * @details Initializes a `PercentDecoder` instance ready for decoding.
  */
 PercentDecoder();

 /**
  * @brief Processes the next character in the percent-encoded sequence.
  * @param c The character to process.
  * @return true if the character was successfully processed, false if an invalid character was encountered.
  */
 [[nodiscard]] bool next(char c) const;

 /**
  * @brief Checks if the decoding process is complete.
  * @return true if the full character has been decoded, false otherwise.
  */
 [[nodiscard]] bool done() const;

 /**
  * @brief Retrieves the decoded character.
  * @return The decoded character.
  * @details This method can only be called after `done()` returns true.
  */
 [[nodiscard]] char getDecodedCharacter() const;

private:
 /**
  * @struct Impl
  * @brief Internal implementation of the `PercentDecoder` class.
  *
  * The `Impl` structure encapsulates the state required for percent-decoding, such as the decoded character
  * and the remaining digits to process.
  */
 struct Impl;

 std::unique_ptr<Impl> impl_;
};
