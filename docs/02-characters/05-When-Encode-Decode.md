## When to Encode or Decode

### Encoding During URI Production:
- Octets within a URI are percent-encoded only during the creation of the URI from its components.
- This process involves determining which reserved characters will be used as delimiters and which can be safely used as data.
- Once created, a URI remains in its percent-encoded form.
### Decoding During URI Dereferencing:
- When a URI is dereferenced, its components and subcomponents must be parsed and separated before decoding the percent-encoded octets.
- This ensures that data is not mistaken for component delimiters.
- Exception: Percent-encoded octets corresponding to characters in the unreserved set can be decoded at any time (e.g., “%7E” can be replaced by “~”).
### Special Handling of the Percent Character:
- The percent (“%”) character, which indicates percent-encoded octets, must itself be percent-encoded as “%25” to be used as data within a URI.
- Implementations must avoid double encoding or decoding to prevent misinterpretation of percent data octets.
### Practical Guide
### URI Creation:
- Identify Reserved Characters: Determine which reserved characters will act as subcomponent delimiters.
- Percent-Encoding: Encode octets that need to be represented as data within the URI.
- Final Form: Ensure the URI is in its percent-encoded form once created.
### URI Dereferencing:
- Parsing Components: Before decoding, parse and separate the URI components and subcomponents.
- Safe Decoding: Decode percent-encoded octets only after ensuring they are not mistaken for delimiters.
- Unreserved Characters: Decode percent-encoded octets for unreserved characters (e.g., “%7E” to “~”) at any time.
### Handling Percent Character:
- Encoding “%”: Always encode the percent character as “%25” when it is part of the data.
- Avoid Double Encoding/Decoding: Ensure that strings are not encoded or decoded more than once to prevent errors.