# Add source to this project's executable.
add_executable (uri "uri.cpp" "uri.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET uri PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
