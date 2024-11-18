if (BUILD_SHARED_LIBS)
    message(STATUS "Build raygui shared library")
else()
    message(STATUS "Build raygui static library")
endif()

configure_file(raygui.h raygui.c COPYONLY)
message(STATUS "Copy raygui.h to raygui.c")

add_library(${PROJECT_NAME} raygui.c)
target_compile_definitions(${PROJECT_NAME} PRIVATE RAYGUI_IMPLEMENTATION)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} raylib)
