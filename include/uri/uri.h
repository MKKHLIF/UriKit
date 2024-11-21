#pragma once

#include <memory>
#include <vector>
#include <string>

/**
 * @class Uri
 * @brief A class for representing and manipulating Uniform Resource Identifiers (URIs).
 *
 * The `Uri` class provides methods for parsing, manipulating, and resolving URIs. It supports schemes,
 * authorities, ports, queries, fragments, and path components. It can be used to handle URIs as both
 * absolute and relative references.
 */
class Uri {
public:
 /**
  * @brief Default constructor.
  *
  * Constructs an empty `Uri` object.
  */
 Uri();

 /**
  * @brief Destructor.
  *
  * Destroys the `Uri` object and releases any resources held by it.
  */
 ~Uri();

 /**
  * @brief Copy constructor.
  *
  * Creates a new `Uri` as a copy of another.
  *
  * @param other The `Uri` to copy from.
  */
 Uri(const Uri &other);

 /**
  * @brief Move constructor.
  *
  * Transfers ownership of resources from another `Uri` object.
  *
  * @param other The `Uri` to move from.
  */
 Uri(Uri &&other) noexcept;

 /**
  * @brief Copy assignment operator.
  *
  * Copies the contents of another `Uri` into this object.
  *
  * @param other The `Uri` to copy from.
  * @return A reference to this `Uri` object.
  */
 Uri &operator=(const Uri &other);

 /**
  * @brief Move assignment operator.
  *
  * Transfers ownership of resources from another `Uri` object.
  *
  * @param other The `Uri` to move from.
  * @return A reference to this `Uri` object.
  */
 Uri &operator=(Uri &&other) noexcept;

 /**
  * @brief Equality comparison operator.
  *
  * Compares two `Uri` objects for equality.
  *
  * @param other The `Uri` to compare with.
  * @return `true` if the `Uri` objects are equal, `false` otherwise.
  */
 bool operator==(const Uri &other) const;

 /**
  * @brief Inequality comparison operator.
  *
  * Compares two `Uri` objects for inequality.
  *
  * @param other The `Uri` to compare with.
  * @return `true` if the `Uri` objects are not equal, `false` otherwise.
  */
 bool operator!=(const Uri &other) const;

 /**
  * @brief Parse a URI string.
  *
  * Parses a URI string and sets the internal fields based on the parsed components.
  *
  * @param str The URI string to parse.
  * @return `true` if the URI was successfully parsed, `false` otherwise.
  */
 [[nodiscard]] bool parse(const std::string &str) const;

 /**
  * @brief Check if the URI has a scheme.
  *
  * @return `true` if the URI has a scheme, `false` otherwise.
  */
 [[nodiscard]] bool hasScheme() const;

 /**
  * @brief Check if the URI has an authority.
  *
  * @return `true` if the URI has an authority, `false` otherwise.
  */
 [[nodiscard]] bool hasAuthority() const;

 /**
  * @brief Check if the URI has a port.
  *
  * @return `true` if the URI has a port, `false` otherwise.
  */
 [[nodiscard]] bool hasPort() const;

 /**
  * @brief Check if the URI has a query.
  *
  * @return `true` if the URI has a query, `false` otherwise.
  */
 [[nodiscard]] bool hasQuery() const;

 /**
  * @brief Check if the URI has a fragment.
  *
  * @return `true` if the URI has a fragment, `false` otherwise.
  */
 [[nodiscard]] bool hasFragment() const;

 /**
  * @brief Get the authority component of the URI.
  *
  * @return A string representing the authority, or an empty string if not present.
  */
 [[nodiscard]] std::string getAuthority() const;

 /**
  * @brief Get the user info component of the URI.
  *
  * @return A string representing the user info, or an empty string if not present.
  */
 [[nodiscard]] std::string getUserInfo() const;

 /**
  * @brief Get the query component of the URI.
  *
  * @return A string representing the query, or an empty string if not present.
  */
 [[nodiscard]] std::string getQuery() const;

 /**
  * @brief Get the fragment component of the URI.
  *
  * @return A string representing the fragment, or an empty string if not present.
  */
 [[nodiscard]] std::string getFragment() const;

 /**
  * @brief Get the scheme component of the URI.
  *
  * @return A string representing the scheme, or an empty string if not present.
  */
 [[nodiscard]] std::string getScheme() const;

 /**
  * @brief Get the host component of the URI.
  *
  * @return A string representing the host, or an empty string if not present.
  */
 [[nodiscard]] std::string getHost() const;

 /**
  * @brief Get the path components of the URI.
  *
  * @return A vector of strings representing the path components.
  */
 [[nodiscard]] std::vector<std::string> getPath() const;

 /**
  * @brief Get the port component of the URI.
  *
  * @return The port as a 16-bit unsigned integer, or 0 if not present.
  */
 [[nodiscard]] uint16_t getPort() const;

 /**
  * @brief Set the scheme component of the URI.
  *
  * @param scheme The scheme to set.
  */
 void setScheme(const std::string &scheme) const;

 /**
  * @brief Set the user info component of the URI.
  *
  * @param userinfo The user info to set.
  */
 void setUserInfo(const std::string &userinfo) const;

 /**
  * @brief Set the host component of the URI.
  *
  * @param host The host to set.
  */
 void setHost(const std::string &host) const;

 /**
  * @brief Set the port component of the URI.
  *
  * @param port The port to set.
  */
 void setPort(uint16_t port) const;

 /**
  * @brief Set the path component of the URI.
  *
  * @param path A vector of path components to set.
  */
 void setPath(const std::vector<std::string> &path) const;

 /**
  * @brief Set the query component of the URI.
  *
  * @param query The query to set.
  */
 void setQuery(const std::string &query) const;

 /**
  * @brief Set the fragment component of the URI.
  *
  * @param fragment The fragment to set.
  */
 void setFragment(const std::string &fragment) const;

 /**
  * @brief Clear the port component of the URI.
  *
  * Clears the port if it is set.
  */
 void clearPort() const;

 /**
  * @brief Clear the query component of the URI.
  *
  * Clears the query if it is set.
  */
 void clearQuery() const;

 /**
  * @brief Clear the fragment component of the URI.
  *
  * Clears the fragment if it is set.
  */
 void clearFragment() const;

 /**
  * @brief Clear the path component of the URI.
  *
  * Clears the path if it is set.
  */
 void clearPath() const;

 /**
  * @brief Clear the user info component of the URI.
  *
  * Clears the user info if it is set.
  */
 void clearUserInfo() const;

 /**
  * @brief Clear the host component of the URI.
  *
  * Clears the host if it is set.
  */
 void clearHost() const;

 /**
  * @brief Reset the URI to an empty state.
  *
  * Resets all components of the URI to their default empty state.
  */
 void reset() const;

 /**
  * @brief Generate a URI string from the current components.
  *
  * @return A string representing the URI based on the current components.
  */
 [[nodiscard]] std::string generateString() const;

 /**
  * @brief Check if the URI is relative.
  *
  * @return `true` if the URI is relative, `false` if it is absolute.
  */
 [[nodiscard]] bool isRelative() const;

 /**
  * @brief Check if the path is absolute.
  *
  * @return `true` if the URI path is absolute, `false` otherwise.
  */
 [[nodiscard]] bool isPathAbsolute() const;

 /**
  * @brief Check if the URI contains a relative path.
  *
  * @return `true` if the URI contains a relative path, `false` otherwise.
  */
 [[nodiscard]] bool containsRelativePath() const;

 /**
  * @brief Normalize the URI path.
  *
  * This method modifies the URI path to ensure it is in a canonical form (e.g., removing redundant segments).
  */
 void normalizePath();

 /**
  * @brief Resolve a relative URI against this URI.
  *
  * Resolves a relative URI reference against this base URI to form an absolute URI.
  *
  * @param relativeReference The relative URI to resolve.
  * @return The resolved absolute URI.
  */
 [[nodiscard]] Uri resolve(const Uri &relativeReference) const;

private:
 struct UriImpl;
 // Exclusively owns the pimpl object it points to.
 std::unique_ptr<UriImpl> pimpl_;
};
