cmake_minimum_required(VERSION 3.20)
project(synth2 VERSION 0.1.0 LANGUAGES C)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

set(UNITY_EXTENSION_FIXTURE ON)

add_subdirectory(libs/clap)
add_subdirectory(libs/unity)
add_subdirectory(src)
add_subdirectory(test)
