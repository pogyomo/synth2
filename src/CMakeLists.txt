add_library(synth2 MODULE
    entry.c
    ext/audio-ports.c
    ext/note-ports.c
    ext/params.c
    factory/plugin-factory.c
    helper.c
    plugin.c
    plugin/process-event.c
    plugin/render-audio.c
)

# Collect libraries for target_link_libraries.
list(APPEND SYNTH2_LINK_LIBRARIES clap synth2-osc synth2-adsr)
if (LINUX)
    list(APPEND SYNTH2_LINK_LIBRARIES m)
endif()

target_include_directories(synth2 PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(synth2 ${SYNTH2_LINK_LIBRARIES})

set_target_properties(synth2 PROPERTIES
    PREFIX ""
    SUFFIX ".clap"
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
