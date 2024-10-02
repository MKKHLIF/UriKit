if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET uri PROPERTY CXX_STANDARD 20)
endif()

set(This UriTests)
file(GLOB_RECURSE SRC_FILES "*.cpp" "*.cc")

add_executable(${This} ${SRC_FILES})

find_package(GTest CONFIG REQUIRED) 
target_link_libraries(${This} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
