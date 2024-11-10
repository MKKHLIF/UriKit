
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${This} PROPERTY CXX_STANDARD 20)
endif ()

add_subdirectory("parsing")
