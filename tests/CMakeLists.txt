set(This UriTests)
file(GLOB_RECURSE SRC_FILES "*.cpp" "*.cc")

add_executable(${This} ${SRC_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${This} PROPERTY CXX_STANDARD 20)
endif()

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${This} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(${This} PRIVATE UriLib)
target_include_directories(${This} PRIVATE ${CMAKE_SOURCE_DIR}/src/internal)

include(GoogleTest)
gtest_discover_tests(${This})