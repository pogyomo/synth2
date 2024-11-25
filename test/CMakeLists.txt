add_executable(test-sample test-sample.cc)
target_link_libraries(test-sample GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test-sample)
