add_executable(synth2-test main.c adsr.c)
target_link_libraries(synth2-test synth2-core unity)
add_test(NAME synth2-test COMMAND synth2-test)
