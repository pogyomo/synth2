add_library(${PROJECT_NAME} MODULE
    entry.c
    ext/audio-ports.c
    ext/note-ports.c
    factory/plugin-factory.c
    plugin.c
    plugin/process-event.c
    plugin/render-audio.c
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} clap)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".clap"
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
