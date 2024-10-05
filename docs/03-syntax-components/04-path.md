# Path Component in URIs

The path component of a URI is crucial for identifying a resource within the scope of the URI’s scheme and naming authority. It is typically organized hierarchically and is terminated by a question mark (“?”), number sign (“#”), or the end of the URI.

## Key Points

### Path Structure
* The path component can be empty or start with a slash (“/”) if the URI contains an authority component.
* Without an authority component, the path cannot start with “//”.
* Relative-path references cannot have a colon (“:”) in the first segment.

### Path Grammar
* **path-abempty**: Begins with “/” or is empty.
* **path-absolute**: Begins with “/” but not “//”.
* **path-noscheme**: Begins with a non-colon segment.
* **path-rootless**: Begins with a segment.
* **path-empty**: Zero characters.

### Path Segments
* A path consists of segments separated by “/”.
* Segments can include characters like unreserved, percent-encoded, sub-delimiters, “:”, and “@”.

### Dot-Segments
* “.” and “..” are used for relative references within the path hierarchy, similar to file systems.
* These are removed during the resolution process.

### Reserved Characters
* Characters like “;”, “=”, and “,” are used to delimit parameters and values within segments.

## Practical Guide

### Including Paths in URIs
* Example: `http://example.com/path/to/resource`
* Relative path: `../path/to/resource`

### Handling Dot-Segments
* Example: `http://example.com/a/b/../c` resolves to `http://example.com/a/c`.

### Using Reserved Characters
* Example: `http://example.com/resource;v=1.1` or `http://example.com/resource,1.1`.

## Concrete Examples

### HTTP Example
* Absolute path: `http://example.com/path/to/resource`
* Relative path: `http://example.com/path/../resource` resolves to `http://example.com/resource`.

### Mailto Example
* `mailto:fred@example.com` has a path of `fred@example.com`.

### FTP Example
* `ftp://example.com/path/to/file` uses a hierarchical path.

## Implementation Tips

### URI Normalization
* Normalize paths by resolving dot-segments.
* Example: Convert `http://example.com/a/./b/../c` to `http://example.com/a/c`.

### Parsing URIs
* Ensure paths conform to the specified grammar.
* Handle reserved characters appropriately within segments.