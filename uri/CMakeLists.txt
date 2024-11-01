set(This p_uri)

file(GLOB_RECURSE SRC_FILES "*.cpp" "*.cc")
file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")

add_library(${This} STATIC ${SRC_FILES} ${HEADER_FILES}
        src/characters/character_sets.h
        src/characters/character_sets.cc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${This} PROPERTY CXX_STANDARD 20)
endif ()

target_include_directories(${This} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
