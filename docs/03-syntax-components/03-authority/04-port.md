# Port subcomponent in URIs

The port subcomponent of a URI’s authority section is an optional numeric value that follows the host, separated by a colon (`:`). 
The port is defined by the following grammar: `port = *DIGIT`

This means the port is a sequence of digits. Each URI scheme can define a default port. For instance, the `http` scheme uses `port 80` by default. The type of port (e.g., `TCP`, `UDP`, `SCTP`) is determined by the URI scheme.

### Practical Guide
* Including a Port in a URI:
  * When specifying a port in a URI, it follows the host and is separated by a colon.
  * Example: `http://example.com:8080/path`
  
* Default Ports:
  * If the port is the default for the scheme, it can be omitted.
  * Example: `http://example.com` is equivalent to `http://example.com:80` because 80 is the default port for HTTP.

* Omitting the Port:
  * If the port is empty or matches the scheme’s default port, it should be omitted along with the colon.
  * Example: For an HTTPS URL, `https://example.com` is preferred over `https://example.com:443` since 443 is the default port for HTTPS.

* Port Types:
The type of port (`TCP`, `UDP`, etc.) is defined by the URI scheme. For example, `HTTP` and `HTTPS` use `TCP` ports.

### Concrete Examples
* HTTP Example:
  * Default port: `http://example.com` (implicitly uses port `80`)
  * Non-default port: `http://example.com:8080`
* HTTPS Example:
  * Default port: `https://example.com` (implicitly uses port `443`)
  * Non-default port: `https://example.com:8443`
* FTP Example:
  * Default port: `ftp://example.com` (implicitly uses port `21`)
  * Non-default port: `ftp://example.com:2121`

### Implementation Tips
* URI Normalization:
  * When generating URIs, omit the port if it matches the default for the scheme to keep the URI concise.
  * Example: Normalize `http://example.com:80` to `http://example.com`.
* Parsing URIs:
  * When parsing URIs, check if the port is specified. If not, use the default port for the scheme.
  * Example: For `http://example.com`, assume port `80` if no port is specified.