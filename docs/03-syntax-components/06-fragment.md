# Fragment Identifier Component in URIs

The fragment identifier component of a URI allows for the indirect identification of a secondary resource by referencing a primary resource and additional identifying information. It is indicated by a number sign (“#”) and terminated by the end of the URI.

## Key Points

### Fragment Structure
* The fragment component is defined by the grammar:
    * `fragment = *( pchar / "/" / "?" )`
* This means the fragment can include any character allowed in a path character (pchar), as well as “/” and “?”.

### Semantics
* The meaning of a fragment identifier is determined by the media type of the primary resource’s representation.
* If no representation exists, the semantics of the fragment are unknown and unconstrained.

### Independence from URI Scheme
* Fragment identifier semantics are independent of the URI scheme and cannot be redefined by scheme specifications.
* Media types may define their own structures within the fragment identifier syntax.

### Consistency Across Representations
* If a primary resource has multiple representations, the fragment should consistently identify the same secondary resource across all representations.

### Client-Side Indirect Referencing
* Fragment identifiers are used for client-side indirect referencing, allowing authors to identify specific aspects of a resource.
* The fragment is separated from the rest of the URI before dereferencing and is processed solely by the user agent.

## Practical Guide

### Including Fragments in URIs
* Example: `http://example.com/resource#section2`
* Multiple fragments: `http://example.com/resource#section2?query=example`

### Handling Special Characters
* Use characters like “/” and “?” directly in the fragment for better readability.
* Example: `http://example.com/resource#path/to/section`

### Consistency Across Representations
* Ensure that fragments consistently identify the same secondary resource across different representations of the primary resource.
* Example: `http://example.com/resource#section2` should refer to the same section in both HTML and PDF representations.

## Concrete Examples

### HTML Example
* Fragment to a section: `http://example.com/page.html#section2`
* Fragment with query: `http://example.com/page.html#section2?query=example`

### PDF Example
* Fragment to a page: `http://example.com/document.pdf#page=2`

## Implementation Tips

### URI Normalization
* Ensure that the fragment component is correctly parsed and handled, especially when dealing with special characters.
* Example: Normalize `http://example.com/resource#path%2Fto%2Fsection` to `http://example.com/resource#path/to/section`.

### Parsing URIs
* When parsing URIs, correctly distinguish between the primary resource and the fragment component.
* Example: For `http://example.com/resource#section2`, ensure the fragment is parsed as `section2`.