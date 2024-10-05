### Hierarchical Organization:
- Component Order: URIs are organized hierarchically, with components listed from most to least significant from left to right.
- Scheme Visibility: Some URI schemes treat everything after the scheme delimiter (“:”) as opaque, while others make the hierarchy explicit for parsing.
### Generic Syntax Delimiters:
- Delimiters: Use slash (“/”), question mark (“?”), and number sign (“#”) characters to delimit components in a URI. These characters aid in the hierarchical interpretation of the identifier.
- Uniform Representation: Consistent use of these delimiters across naming schemes enhances readability and allows for scheme-independent references.
### Relative Referencing:
- Document Trees: Relative referencing allows documents within a tree to be independent of their location and access scheme. This enables documents to be accessible via multiple schemes (e.g., “file”, “http”, “ftp”) without changing references.
- Mobility: Document trees can be moved without altering relative references, maintaining the integrity of internal links.
### Reference Resolution:
- Relative References: These describe the difference within a hierarchical namespace between the reference context and the target URI.
- Resolution Algorithm: The algorithm transforms relative references into target URIs, ensuring accurate resource identification.
### Design Considerations for New URI Schemes:
- Consistency with Generic Syntax: New URI schemes should use a syntax consistent with the hierarchical components of the generic syntax unless there are compelling reasons to forbid relative referencing.
- Avoiding Misunderstandings: Use clear terminology to avoid confusion. For example, refer to “relative references” instead of “partial URIs” or “relative URIs”.
### Opaque Identifiers:
- Absolute URIs: Hierarchical processing does not affect absolute URIs unless they contain dot-segments (e.g., “.”, “…”).
- Scheme Specifications: URI schemes can define opaque identifiers by disallowing certain characters (e.g., slash, question mark) and specific URIs (e.g., “scheme:.”, “scheme:…”).