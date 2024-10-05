| **Concept**         | **Example**                        | **Validity**   | **Notes**                                                                 |
|---------------------|------------------------------------|----------------|---------------------------------------------------------------------------|
| `path-abempty`      | `http://example.com/path/to/resource` | Valid          | Path is absolute.                                                         |
| `path-abempty`      | `http://example.com/`              | Valid          | Path is empty.                                                            |
| `path-abempty`      | `http://example.com/path:to/resource` | Invalid        | Ambiguous due to `:` in the path.                                        |
| `path-noscheme`     | `folder/file.txt`                  | Valid          | Clear relative reference.                                                |
| `path-noscheme`     | `folder:file.txt`                  | Invalid        | Ambiguous; could be interpreted as a scheme.                             |
| `path-noscheme`     | `http://folder/file.txt`           | Valid          | Clear distinction; `folder` is part of the scheme.                      |
