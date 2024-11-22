if(BUILD_SHARED_LIBS)
    message(STATUS "Build shared synth2-osc")
else()
    message(STATUS "Build static synth2-osc")
endif()
add_library(synth2-osc
    osc.c
    wave-generator.c
)

# Collect libraries for target_link_libraries.
if (LINUX)
    list(APPEND SYNTH2_OSC_LINK_LIBRARIES m)
endif()

target_include_directories(synth2-osc PUBLIC ../include)
target_link_libraries(synth2-osc ${SYNTH2_OSC_LINK_LIBRARIES})

set_target_properties(synth2-osc PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
