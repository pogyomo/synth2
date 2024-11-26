/// Just for test unity_fixture.
/// Should be removed in future.

#include <unity_fixture.h>

TEST_GROUP(stub);
TEST_SETUP(stub) {}
TEST_TEAR_DOWN(stub) {}

TEST(stub, success) {}

TEST_GROUP_RUNNER(stub) {
    RUN_TEST_CASE(stub, success);
}
