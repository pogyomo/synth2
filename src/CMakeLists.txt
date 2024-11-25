add_library(synth2 MODULE
    entry.c
    ext/audio-ports.c
    ext/note-ports.c
    ext/params.c
    factory/plugin-factory.c
    helper.c
    params.c
    plugin.c
    process-event.c
    render-audio.c
    voice.c
)

# Collect libraries for target_link_libraries.
list(APPEND SYNTH2_LINK_LIBRARIES clap synth2-osc synth2-adsr)
if (LINUX)
    list(APPEND SYNTH2_LINK_LIBRARIES m)
endif()

target_include_directories(synth2 PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(synth2 ${SYNTH2_LINK_LIBRARIES})

# Clangd can't recognize voice.h is on this project without correspond source file.
# So create a empty source file corresponds to it at configure time to solve the problem.
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/voice.c" "")

set_target_properties(synth2 PROPERTIES
    PREFIX ""
    SUFFIX ".clap"
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
