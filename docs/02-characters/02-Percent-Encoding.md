## Percent-Encoding
- Percent-Encoding is a mechanism used to represent data octets in a URI component when the corresponding character is outside the allowed set or is used as a delimiter. This encoding is crucial for ensuring that URIs can be correctly interpreted and transmitted.

### Encoding Mechanism:
- A percent-encoded octet is represented as a triplet: % followed by two hexadecimal digits.
-Example: %20 represents the binary octet 00100000, which corresponds to the space character (SP) in US-ASCII.
### Hexadecimal Digits:
- Both uppercase (A-F) and lowercase (a-f) hexadecimal digits are equivalent.
- For consistency, URI producers should use uppercase hexadecimal digits.
### Equivalence:
- URIs differing only in the case of hexadecimal digits in percent-encoded octets are considered equivalent.
### When to Use Percent-Encoding:
- Use percent-encoding for characters outside the allowed set or when characters are used as delimiters within a URI component.
- Example: In a URL, spaces should be encoded as %20.
### Encoding Process:
- Identify the character to be encoded.
- Convert the character to its binary octet.
- Represent the binary octet as a hexadecimal value.
- Precede the hexadecimal value with %.
#### Example:
````
Character: #
Binary Octet: 00100011
Hexadecimal: 23
Percent-Encoding: %23
````

### Decoding Process:
- Identify the percent-encoded triplet.
- Remove the % character.
- Convert the hexadecimal digits back to their binary form.
- Map the binary value to the corresponding character.
#### Example:
````
Percent-Encoding: %2F
Hexadecimal: 2F
Binary Octet: 00101111
Character: /
Consistency in Encoding:
Always use uppercase hexadecimal digits for encoding.
Ensure that all percent-encoded characters are correctly interpreted by normalizing URIs.
````
