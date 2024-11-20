add_library(${PROJECT_NAME} raygui.c)
if (BUILD_SHARED_LIBS)
    message(STATUS "Build raygui shared library")
else()
    message(STATUS "Build raygui static library")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ../include)
target_link_libraries(${PROJECT_NAME} raylib)
