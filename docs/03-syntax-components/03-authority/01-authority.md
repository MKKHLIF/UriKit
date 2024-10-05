## URI Authority Component

### Overview:
Many URI schemes include a hierarchical element for a naming authority, which governs the namespace defined by the remainder of the URI. This authority can be further delegated. The generic syntax provides a common means for distinguishing an authority based on a registered name or server address, along with optional port and user information.

### Syntax:
The authority component is preceded by a double slash `(//)` and is terminated by the next slash `(/)`, question mark `(?)`, or number sign `(#)` character, or by the end of the URI.

`authority = [ userinfo "@" ] host [ ":" port ]`

### Components:
* `userinfo`: Optional user information (e.g., username and password).
* `host`: The registered name or server address.
* `port`: Optional port number.

Example: `http://user:password@www.example.com:8080/path?query#fragment`

* `userinfo`: user:password
* `host:` www.example.com
* `port:` 8080

### Guidelines:
* Omitting Empty Port: URI producers and normalizers should omit the : delimiter if the port component is empty.
* Path Component: If a URI contains an authority component, the path component must either be empty or begin with a slash (/).
* Non-Validating Parsers: Parsers that merely separate a URI reference into its major components often treat the authority as an opaque string from the double-slash to the first terminating delimiter until the URI is dereferenced.

### Practical Guide:
* Constructing URIs:
  * Ensure the authority component is correctly formatted with optional userinfo and port.
  * Example: http://username:password@host:port/path.
  
* Parsing URIs:
  * Use regular expressions or URI parsing libraries to extract components.
  * Example in Python:
    ```python
    from urllib.parse import urlparse
    url = 'http://user:password@www.example.com:8080/path?query#fragment'
    parsed_url = urlparse(url)
    print(parsed_url)
    ```

* Normalizing URIs:
  * Remove empty port delimiters.
  * Ensure the path starts with a slash if an authority is present.
  
* Handling Authority as Opaque String:
  * For non-validating parsers, treat the authority component as a single string until further processing is required.