if(BUILD_SHARED_LIBS)
    message(STATUS "Build shared synth2-adsr")
else()
    message(STATUS "Build static synth2-adsr")
endif()
add_library(synth2-adsr adsr.c)

# Collect libraries for target_link_libraries.
if (LINUX)
    list(APPEND SYNTH2_ADSR_LINK_LIBRARIES m)
endif()

target_include_directories(synth2-adsr PUBLIC ../include)
target_link_libraries(synth2-adsr ${SYNTH2_OSC_ADSR_LIBRARIES})

set_target_properties(synth2-adsr PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
