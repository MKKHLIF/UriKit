### Understanding URI Identification:
- Identification vs. Access: Recognize that a URI is primarily for identification, not guaranteed access. The presence of a URI does not imply that the resource is accessible.
- Protocol Independence: The operations associated with a URI are defined by the protocol or context in which it appears, not by the URI itself.
### Operations on URIs:
- Common Operations: Be familiar with terms like “resolution” (determining access mechanisms) and “dereference” (using the access mechanism to interact with the resource).
- Protocol-Specific Actions: Understand that actions such as “access”, “update”, “replace”, or “find attributes” are defined by the protocols using the URIs.
### URI Resolution and Dereferencing:
- Resolution Process: The process of URI resolution may involve multiple steps to determine the appropriate access mechanism and parameters.
- Dereferencing: Using the resolved access mechanism to perform actions on the resource, such as retrieval.
## Information Retrieval Systems:
- Retrieval: The most common form of dereferencing in information retrieval systems is retrieving a representation of the resource.
- Representation: A representation is a sequence of octets and metadata that records the state of the resource at a specific time.
### Late-Binding References:
- Dynamic Results: URI references are designed to be late-binding, meaning the result of accessing a URI can vary over time.
- Future Use: URIs are intended for future use, identifying characteristics expected to be true for future results.
### Multiple Protocols:
- Protocol Flexibility: The resolution of some URIs may require multiple protocols (e.g., DNS and HTTP for an “http” URI).
- Intermediaries: Access to resources via URIs might involve gateways, proxies, caches, and name resolution services independent of the protocol associated with the URI scheme.