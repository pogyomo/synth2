if(BUILD_SHARED_LIBS)
    message(STATUS "Build shared synth2-filter")
else()
    message(STATUS "Build static synth2-filter")
endif()
add_library(synth2-filter filter.c)

# Collect libraries for target_link_libraries.
if (LINUX)
    list(APPEND SYNTH2_FILTER_LINK_LIBRARIES m)
endif()

target_include_directories(synth2-filter PUBLIC ../include)
target_link_libraries(synth2-filter ${SYNTH2_FILTER_LINK_LIBRARIES})

set_target_properties(synth2-filter PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
