add_library(${PROJECT_NAME} nuklear.c)
if (BUILD_SHARED_LIBS)
    message(STATUS "Build shared nuklear library")
else()
    message(STATUS "Build static nuklear library")
endif()

# For each flags provided by nuklear, checks if it enabled.
# If enabled, append it to NUKLEAR_ENABLED_FLAGS to use it to enable the flag.
set(NUKLEAR_ALL_FLAGS
    NK_INCLUDE_FIXED_TYPES
    NK_INCLUDE_DEFAULT_ALLOCATOR
    NK_INCLUDE_STANDARD_IO
    NK_INCLUDE_STANDARD_VARARGS
    NK_INCLUDE_STANDARD_BOOL
    NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    NK_INCLUDE_FONT_BAKING
    NK_INCLUDE_DEFAULT_FONT
    NK_INCLUDE_COMMAND_USERDATA
    NK_BUTTON_TRIGGER_ON_RELEASE
    NK_ZERO_COMMAND_MEMORY
    NK_UINT_DRAW_INDEX
    NK_KEYSTATE_BASED_INPUT
)
foreach(FLAG IN LISTS NUKLEAR_ALL_FLAGS)
    option(${FLAG} OFF)
    if (${FLAG})
        list(APPEND NUKLEAR_ENABLED_FLAGS ${FLAG})
        message(STATUS "${FLAG} enabled")
    endif()
endforeach()

target_include_directories(${PROJECT_NAME} PUBLIC ../include)
target_compile_definitions(${PROJECT_NAME} PUBLIC ${NUKLEAR_ENABLED_FLAGS})
