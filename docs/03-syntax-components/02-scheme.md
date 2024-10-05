Each URI begins with a **scheme** name, which specifies the protocol used to access the resource. The scheme is a key part of the URI's federated and extensible naming system, allowing each scheme to define its own syntax and semantics.

### Scheme Name Rules
- **Starts with a letter**: Followed by letters, digits, `+`, `.`, or `-`.
- **Case-insensitive**: Canonical form is lowercase, but implementations should accept uppercase.
- **Syntax**: scheme = ALPHA *( ALPHA / DIGIT / “+” / “-” / “.” )

### Practical Guide

1. **Defining a New Scheme**:
- Follow the registration process defined by BCP35.
- Ensure the scheme's syntax matches the `<absolute-URI>` grammar.

2. **Implementation Tips**:
- **Case Handling**: Convert scheme names to lowercase for consistency.
- **Validation**: Flag URIs that violate scheme-specific restrictions to prevent misuse.

### Example

**HTTP URI**: `http://example.com`

- **Scheme**: `http`
- **Authority**: `example.com`

**Custom Scheme**: `myapp://user:password@host:port/path?query#fragment`

- **Scheme**: `myapp`
- **Authority**: `user:password@host:port`
- **Path**: `/path`
- **Query**: `query`
- **Fragment**: `fragment`
