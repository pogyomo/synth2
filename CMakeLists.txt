cmake_minimum_required(VERSION 3.20)
project(synth2 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

add_subdirectory(libs/clap)
add_subdirectory(libs/googletest)
add_subdirectory(src)
add_subdirectory(test)
