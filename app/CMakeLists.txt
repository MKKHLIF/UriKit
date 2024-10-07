set(This app)
file(GLOB_RECURSE SRC_FILES "*.cpp" "*.cc")

add_executable(${This} ${SRC_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${This} PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${This} PRIVATE p_uri)