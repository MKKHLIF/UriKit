set(This UriParser)


file(GLOB_RECURSE SRC_FILES "*.cpp" "*.cc")
file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")

add_executable(${This} ${SRC_FILES})

target_link_libraries(${This} PRIVATE UriLib)


