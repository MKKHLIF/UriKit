## Reserved Characters:
- Reserved Characters in URIs are used to delimit components and subcomponents. These characters have special meanings and must be percent-encoded if they conflict with their role as delimiters.

### Reserved Characters:
- General Delimiters (gen-delims): :, /, ?, #, [, ], @
- Subcomponent Delimiters (sub-delims): !, $, &, ', (, ), *, +, ,, ;, =
### Purpose:
- Reserved characters distinguish different parts of a URI.
- They are protected from normalization to ensure they can be used reliably as delimiters.
### Equivalence:
URIs that differ only in the replacement of a reserved character with its percent-encoded form are not equivalent.
Percent-encoding or decoding reserved characters changes how the URI is interpreted.
### Practical Guide:
- When to Use Percent-Encoding:
- Percent-encode reserved characters if they conflict with their role as delimiters.
- Example: In a query string, & should be percent-encoded as %26 if it is part of the data rather than a delimiter.
### Encoding Process:
- Identify the reserved character to be encoded.
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
    ````
### Handling Reserved Characters in URI Components:
- Ensure that reserved characters are used appropriately within URI components.
If a reserved character is found in a URI component without a known delimiting role, interpret it as representing the data octet corresponding to its US-ASCII encoding.