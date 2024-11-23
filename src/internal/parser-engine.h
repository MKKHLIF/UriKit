#pragma once

#include <string>
#include <vector>
#include <uri/uri.h>

/**
 * @class Parser
 * @brief A class responsible for parsing URI strings into `Uri` objects.
 *
 * The `Parser` class provides functionality to parse a URI string and populate a `Uri` object with the extracted components.
 * It includes methods for managing the object lifecycle, including copying, moving, and parsing operations.
 */
class Parser {
public:
 /**
  * @brief Default constructor for the `Parser` class.
  *
  * This constructor initializes a new `Parser` object. The object is ready to be used for parsing URI strings.
  */
 Parser();

 /**
  * @brief Destructor for the `Parser` class.
  * @noexcept
  *
  * This destructor cleans up any resources used by the `Parser` object.
  */
 ~Parser() noexcept;

 /**
  * @brief Copy constructor for the `Parser` class.
  *
  * This constructor creates a new `Parser` object as a copy of another existing `Parser` object.
  * @param other The `Parser` object to copy.
  */
 Parser(const Parser &);

 /**
  * @brief Move constructor for the `Parser` class.
  * @noexcept
  *
  * This constructor transfers ownership of resources from another `Parser` object to the newly created object.
  * @param other The `Parser` object to move.
  */
 Parser(Parser &&) noexcept;

 /**
  * @brief Copy assignment operator for the `Parser` class.
  *
  * This operator assigns the state of one `Parser` object to another, creating a copy of the object.
  * @param other The `Parser` object to copy.
  * @return A reference to this `Parser` object after assignment.
  */
 Parser &operator=(const Parser &);

 /**
  * @brief Move assignment operator for the `Parser` class.
  * @noexcept
  *
  * This operator transfers ownership of resources from another `Parser` object to this one.
  * @param other The `Parser` object to move.
  * @return A reference to this `Parser` object after assignment.
  */
 Parser &operator=(Parser &&) noexcept;

 /**
  * @brief Parses a URI string into a `Uri` object.
  * @param uri The URI string to be parsed.
  * @param obj The `Uri` object that will hold the parsed components.
  * @return true if the URI was successfully parsed, false otherwise.
  * @details This method parses the provided URI string and fills the `Uri` object with its components. It processes
  *          different parts of the URI, such as the scheme, authority, path, query, and fragment. The parsing
  *          succeeds if all parts of the URI are valid and properly extracted.
  */
 [[nodiscard]] bool parse(std::string &uri, const Uri *obj) const;

private:
 /**
  * @brief Implementation class for the `Parser` class.
  *
  * The `Imp` class contains the implementation details of the `Parser` class. This allows for the use of the
  * *PImpl* idiom (pointer to implementation) to hide implementation details and reduce the size of the
  * public interface.
  */
 class Imp;

 /**
  * @brief Pointer to the implementation of the `Parser` class.
  *
  * The `imp` member holds a pointer to the `Imp` object, which manages the internal state and functionality
  * of the `Parser` class.
  */
 std::unique_ptr<Imp> imp;
};
