list(APPEND SYNTH2_LINK_LIBRARIES clap)
if (LINUX)
    list(APPEND SYNTH2_LINK_LIBRARIES m)
endif()

# Generate dummy source file for header-only files
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/voice.c" "")

add_library(synth2-core STATIC
    adsr.c
    ext/audio-ports.c
    ext/note-ports.c
    ext/params.c
    factory/plugin-factory.c
    filter.c
    helper.c
    osc.c
    osc/wave-generator.c
    params.c
    plugin.c
    process-event.c
    random.c
    render-audio.c
    voice.c
)
target_include_directories(synth2-core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(synth2-core PUBLIC ${SYNTH2_LINK_LIBRARIES})
set_target_properties(synth2-core PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

add_library(synth2 MODULE entry.c)
target_link_libraries(synth2 PUBLIC synth2-core)
set_target_properties(synth2 PROPERTIES
    PREFIX ""
    SUFFIX ".clap"
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
