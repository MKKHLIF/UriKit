set(This UriParser)

file(GLOB_RECURSE SRC_FILES "*.cpp" "*.cc")

add_executable(${This} ${SRC_FILES})

target_link_libraries(${This} PRIVATE UriLib)


