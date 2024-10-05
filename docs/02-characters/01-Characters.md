### Character Encoding:
- Encoding Flexibility: URIs encode data as a sequence of characters, which are often encoded as octets for transport or presentation. The specific character encoding is not mandated by the URI specification but is defined by the protocol in which the URI appears.
- Protocol-Defined Encoding: When a URI appears in a protocol element, the character encoding is defined by that protocol. If no encoding is specified, the URI is assumed to be in the same encoding as the surrounding text.
- Example: In an HTTP header, the URI encoding would follow the HTTP protocol’s specifications.
### ABNF Notation and US-ASCII:
- ABNF Mapping: The ABNF notation uses non-negative integers (codepoints) based on the US-ASCII coded character set. These integers must be mapped back to their corresponding characters via US-ASCII to understand the URI syntax.
- Example: If the ABNF defines a value of 65, it maps to the character ‘A’ in US-ASCII.
### Character Set:
- Limited Set: URIs are composed of a limited set of characters, including digits, letters, and a few graphic symbols.
- Reserved and Unreserved Characters: A reserved subset of characters is used to delimit syntax components within a URI. The remaining characters, including both the unreserved set and reserved characters not acting as delimiters, define each component’s identifying data.
- Example: The characters “/”, “?”, and “#” are reserved for delimiting components, while letters, digits, and symbols like “-”, “.”, “_”, and “~” are unreserved and can be used freely.
### Reserved Characters:
- Delimiters: Reserved characters such as “/”, “?”, and “#” are used to delimit different components of a URI.
- Example: In the URI http://example.com/path?query#fragment, the characters “/”, “?”, and “#” are delimiters.
### Unreserved Characters:
- Usage: Unreserved characters, which include letters, digits, and a few symbols (e.g., “-”, “.”, “_”, “~”), can be used freely within a URI without encoding.
- Example: The URI http://example.com/path uses unreserved characters in the path component.
### Percent-Encoding:
- Encoding Special Characters: Characters outside the unreserved set must be percent-encoded. This involves converting the character to its corresponding octet value and representing it as a “%” followed by two hexadecimal digits.
- Example: The space character " " is percent-encoded as “%20”.