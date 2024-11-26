cmake_minimum_required(VERSION 3.20)
project(synth2 VERSION 0.1.0 LANGUAGES C)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

# Stuffs for unity
set(UNITY_EXTENSION_FIXTURE ON)
add_compile_definitions(UNITY_INCLUDE_DOUBLE)
if (MSVC)
    # Disable warnings from unity
    add_compile_options(/wd4820 /wd5045)
endif()

add_subdirectory(libs/clap)
add_subdirectory(libs/unity)
add_subdirectory(src)
add_subdirectory(test)
