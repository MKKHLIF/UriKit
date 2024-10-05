## Unreserved Characters
- Unreserved Characters in URIs are those that do not have a reserved purpose and can be used freely without the need for percent-encoding. These characters include uppercase and lowercase letters, decimal digits, hyphen, period, underscore, and tilde.

###  Unreserved Characters:
```` 
Uppercase Letters: A-Z
Lowercase Letters: a-z
Decimal Digits: 0-9
Hyphen: -
Period: .
Underscore: _
Tilde: ~
````

### Equivalence:
- URIs that differ only in the replacement of an unreserved character with its percent-encoded form are considered equivalent.
- Example: ````example.com/path and example.com%2Fpath identify the same resource.````
### Normalization:
- URI comparison implementations may not always perform normalization before comparison.
- For consistency, percent-encoded octets corresponding to unreserved characters should not be created by URI producers.
- When found in a URI, these percent-encoded octets should be decoded to their corresponding unreserved characters by URI normalizers.

### Using Unreserved Characters:
- Use unreserved characters freely in URIs without the need for percent-encoding.
- Example: ````example.com/path/to/resource is valid without any percent-encoding for unreserved characters.````
### Encoding and Decoding:
- Avoid percent-encoding unreserved characters unless absolutely necessary.
- If you encounter percent-encoded unreserved characters, decode them to their original form for consistency.
  #### Example:
  ````
  Percent-Encoding: %41
  Hexadecimal: 41
  Character: A
  Handling Unreserved Characters in URI Components:
  Ensure that unreserved characters are used appropriately within URI components.
  Decode any percent-encoded unreserved characters to maintain URI consistency and equivalence.
  ````