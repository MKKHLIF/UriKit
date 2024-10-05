
### Role of URI Characters:
- URI characters identify data for each URI component, acting as an interface for system identification.
- The URI production interface is hidden from clients, often causing confusion and errors.
### Multiple Character Encodings:
- Various encodings are involved in URI production and transmission: local name encoding, public interface encoding, URI character encoding, data format encoding, and protocol encoding.
- Local names (e.g., file system names) use local character encoding.
### Transformation Process:
- URI-producing applications transform local encoding to a public interface encoding, then to URI characters (reserved, unreserved, percent-encoded).
- These characters are encoded as octets for use in data formats, which are then encoded for Internet transmission.
### Unreserved Characters:
- Unreserved characters in a URI component are interpreted as data octets corresponding to their US-ASCII encoding.
- For example, ````“X” is assumed to correspond to the octet “01011000”````.
### Character Translation:
- Systems using different encodings (e.g., EBCDIC) translate textual identifiers to UTF-8 at an internal interface for meaningful identifiers.
- Example: ````An HTTP server providing data from an EBCDIC file system should transcode “Laguna Beach” to “Laguna%20Beach” instead of “%D3%81%87%A4%95%81@%C2%85%81%83%88”.````
### Proper Interpretation:
- Incoming URIs must decode percent-encoded octets (e.g., “%20” to space) before reverse transcoding to obtain the local name.
### Complex Interfaces:
- Some URI components may represent non-ASCII data or numeric coordinates.
- New URI schemes should encode textual data as UTF-8 octets, percent-encoding only non-unreserved characters.
### Practical Guide
### URI Production:
- Identify Local Encoding: Determine the local character encoding used for names (e.g., file system names).
- Transform to Public Interface Encoding: Convert local encoding to a suitable public interface encoding.
- Encode URI Characters: Transform the public interface encoding to URI characters (reserved, unreserved, percent-encoded).
### Handling Unreserved Characters:
- Interpretation: Ensure unreserved characters are interpreted as their US-ASCII octet equivalents.
- Example: ```` “X” should be interpreted as “01011000”.````
### Character Translation:
- Transcoding: Translate textual identifiers from local encoding (e.g., EBCDIC) to UTF-8.
- Example: ````Convert “Laguna Beach” to “Laguna%20Beach” for HTTP URIs.````
#### Decoding Incoming URIs:
- Decode Percent-Encoding: Decode percent-encoded octets (e.g., “%20” to space) before reverse transcoding.
- Example: ````Decode “%20” to space before converting to the local name.````
### Complex URI Components:
- Non-ASCII Data: Handle URI components representing non-ASCII data or numeric coordinates appropriately.
- New URI Schemes: Encode textual data as UTF-8 octets, percent-encoding non-unreserved characters.