list(APPEND SYNTH2_LINK_LIBRARIES clap)
if (LINUX)
    list(APPEND SYNTH2_LINK_LIBRARIES m)
endif()

add_library(synth2-core STATIC
    adsr.c
    filter.c
    helper.c
)
target_include_directories(synth2-core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(synth2-core PUBLIC ${SYNTH2_LINK_LIBRARIES})
set_target_properties(synth2-core PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
