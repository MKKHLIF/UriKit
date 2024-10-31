# URI-RFC-3986

This library provides an implementation of the URI (Uniform Resource Identifier) specifications as defined
in [RFC 3986](https://tools.ietf.org/html/rfc3986). It offers comprehensive support for parsing, normalizing, and
resolving URIs, ensuring compliance with the standard.

## Main Features

- **URI Parsing**: Parse URIs into their components (scheme, user info, host, port, path, query, and fragment).
- **URI Normalization**: Normalize URIs to a standard form, including case normalization, percent-encoding
  normalization, and path segment normalization.
- **URI Resolution**: Resolve relative URIs against a base URI to produce an absolute URI.
- **IPv6 and IPvFuture Support**: Handle URIs with IPv6 addresses and IPvFuture addresses.
- **Percent-Encoding**: Correctly handle percent-encoded characters in various URI components.
- **Validation**: Validate URIs against the RFC 3986 syntax rules.
- **User Info Handling**: Parse and handle user information in URIs.
- **Query and Fragment Handling**: Parse and handle query and fragment components, including empty but present queries
  and fragments.

## Prerequisites

To Build this project, you need to have **vcpkg** installed and properly configured. Follow these steps (Windows):

1. **Install vcpkg:**

- Clone the vcpkg repository:
  ```bash
  git clone https://github.com/microsoft/vcpkg.git
  ```
- Navigate to the vcpkg directory:
  ```bash
  cd vcpkg
  ```
- Run the bootstrap script:
  ```bash
  .\bootstrap-vcpkg.bat
  ```

2. **Integrate vcpkg with Visual Studio:**
   Run the following command in the vcpkg directory:
   ```bash
   .\vcpkg integrate install

## Platforms and Compilers

The library is tested on the following platforms and compilers:

| Platform | Compiler    | Version |
|----------|-------------|---------|
| Windows  | MSVC        | 19.40 (Visual Studio 2022 v17.10)  |
| Linux    | GCC         | 14.2  |
| Linux    | Clang       | 14.0.0  |
| macOS    | Apple Clang | 14.0.0  |

## Documentation

The full API documentation is available here:
URL: [API Documentation](https://<your-username>.github.io/<repository-name>/)

## License

Licensed under the [MIT license](LICENSE.md).
