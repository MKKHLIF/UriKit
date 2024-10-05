# Host Subcomponent in URIs

## Part I: Host Subcomponent

### Overview
The host subcomponent of a URI’s authority can be an IP literal (IPv6 or future versions), an IPv4 address, or a registered name. This component is case-insensitive and does not necessarily imply internet access.

### Syntax
* Host Syntax: host = IP-literal / IPv4address / reg-name
* IP-literal: Enclosed in square brackets, e.g., `[2001:db8::1]`
* IPv4address: Dotted-decimal form, e.g., `192.0.2.1`
* Reg-name: A registered name, e.g., `example.com`

### Disambiguation
To distinguish between an IPv4 address and a registered name, the “first-match-wins” algorithm is applied:

* If the host matches the IPv4 address rule, it is treated as an IPv4 address.
* Otherwise, it is treated as a registered name.

### Case Sensitivity
* Host names are case-insensitive.
* Use lowercase for registered names and hexadecimal addresses.
* Use uppercase only for percent-encodings.

### IP Literals
* IPv6: Enclosed in square brackets without a version flag, e.g., `[2001:db8::1]`.
* IPvFuture: Future versions indicated by a version flag, e.g., `[v1.unreserved:sub-delims]`.

### Practical Examples
* IPv4 Address: `http://192.0.2.1/resource` Here, `192.0.2.1` is an IPv4 address.
* IPv6 Address: `http://[2001:db8::1]/resource` Here, `[2001:db8::1]` is an IPv6 address.
* Registered Name: `http://example.com/resource` Here, example.com is a registered name.
* IPvFuture Address: `http://[v1.unreserved:sub-delims]/resource` Here, `[v1.unreserved:sub-delims]` is an IPvFuture address.

### Considerations
* Domain Name Changes: Domain ownership can change, affecting the URI’s validity.
* Uniformity: Use lowercase for consistency in registered names and hexadecimal addresses.
* Error Handling: Applications should return an error if they encounter an unsupported version flag in an IP-literal.

## Part II: IPv6 and IPv4 Address Representation

### IPv6 Address Representation
An IPv6 address is a 128-bit identifier divided into eight 16-bit segments. Each segment is represented in hexadecimal (case-insensitive), using one to four digits. Segments are separated by colons (:).

#### Key Points:

* Hexadecimal Digits: Leading zeroes are allowed.
* Colon Separation: Segments are separated by colons.
* IPv4 Representation: The last two segments can be represented as an IPv4 address.
* Zero Compression: Consecutive zero segments can be compressed using ::.

#### Syntax:

````
IPv6address = 6( h16 ":" ) ls32
            / "::" 5( h16 ":" ) ls32
            / [ h16 ] "::" 4( h16 ":" ) ls32
            / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
            / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
            / [ *3( h16 ":" ) h16 ] "::" h16 ":" ls32
            / [ *4( h16 ":" ) h16 ] "::" ls32
            / [ *5( h16 ":" ) h16 ] "::" h16
            / [ *6( h16 ":" ) h16 ] "::"
ls32 = ( h16 ":" h16 ) / IPv4address
h16 = 1*4HEXDIG
````

* Examples:
    * Full IPv6 Address: `2001:0db8:85a3:0000:0000:8a2e:0370:7334` Can be compressed to: `2001:db8:85a3::8a2e:370:7334`
    * IPv6 with IPv4 Representation: `::ffff:192.0.2.128`

### IPv4 Address Representation
An IPv4 address is a 32-bit identifier represented in dotted-decimal notation, consisting of four decimal numbers (0-255) separated by dots (.).

#### Syntax:

````
IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet
dec-octet = DIGIT              ; 0-9
          / %x31-39 DIGIT      ; 10-99
          / "1" 2DIGIT         ; 100-199
          / "2" %x30-34 DIGIT  ; 200-249
          / "25" %x30-35       ; 250-255
````

* Examples:
    * Standard IPv4 Address: `192.0.2.1`


## Part III: Registered Names in URIs

### Overview
A registered name in a URI is a sequence of characters used for lookup within a host or service name registry, commonly the Domain Name System (DNS). The syntax and rules for these names are defined in RFC1034 and RFC1123.

### Syntax
* Registered Name Syntax: `reg-name = *( unreserved / pct-encoded / sub-delims )`
* Domain Labels: Separated by dots (`.`), starting and ending with an alphanumeric character, and may contain hyphens (`-`).
* Example: `example.com`

### Default Host
* File URI Scheme: No authority, an empty host, and “localhost” all refer to the end-user’s machine.
* HTTP URI Scheme: A missing authority or empty host is invalid.
### Name Lookup Technologies
* DNS: The most common mechanism.
* Others: Host tables, yellow pages, NetInfo, WINS, etc.
### Global Scope
For URIs intended to have global scope, a globally scoped naming system like DNS is necessary. Names should conform to DNS syntax and be limited to 255 characters.

### Percent-Encoding
* Non-ASCII Names: Encode using UTF-8, then percent-encode each octet.
* Internationalized Domain Names (IDN): Transform to IDNA encoding before lookup.
* Example:
    * Percent-Encoding: `xn--exmple-cua.com`, Represents a non-ASCII domain name.
    * IDNA Encoding: `xn--bcher-kva.com`, Represents the domain name “bücher.com”.

### Practical Examples
* Standard Registered Name: `http://example.com/resource`, Here, example.com is a registered name.
* Percent-Encoded Registered Name: `http://xn--exmple-cua.com/resource`, Represents a non-ASCII domain name.
* IDNA Encoded Registered Name: `http://xn--bcher-kva.com/resource`, Represents the domain name “bücher.com”.
