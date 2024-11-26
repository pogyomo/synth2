// Copyright 2024 pogyomo
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <synth2/adsr.h>
#include <unity_fixture.h>

#define DELTA 1e-10

TEST_GROUP(adsr);
TEST_SETUP(adsr) {}
TEST_TEAR_DOWN(adsr) {}

TEST(adsr, normal) {
    synth2_adsr_t adsr;
    synth2_adsr_init(&adsr, 5, 1.0, 1.0, 0.5, 1.0);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.2, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.4, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.6, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.8, synth2_adsr_sample(&adsr));

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 1.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.9, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.8, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.7, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.6, synth2_adsr_sample(&adsr));

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));

    synth2_adsr_keyoff(&adsr);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.4, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.3, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.2, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.1, synth2_adsr_sample(&adsr));

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
}

TEST(adsr, stage_changes_between_sample) {
    synth2_adsr_t adsr;
    synth2_adsr_init(&adsr, 5, 0.5, 0.8, 0.5, 0.5);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.4, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.8, synth2_adsr_sample(&adsr));

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.9375, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.8125, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.6875, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5625, synth2_adsr_sample(&adsr));

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));

    synth2_adsr_keyoff(&adsr);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.3, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.1, synth2_adsr_sample(&adsr));

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
}

TEST(adsr, immediate_a) {
    synth2_adsr_t adsr;
    synth2_adsr_init(&adsr, 5, 0.0, 1.0, 0.5, 1.0);
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_D, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 1.0, synth2_adsr_sample(&adsr));
}

TEST(adsr, immediate_d) {
    synth2_adsr_t adsr;
    synth2_adsr_init(&adsr, 5, 1.0, 0.0, 0.5, 1.0);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.2, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.4, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.6, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.8, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
}

TEST(adsr, immediate_ad) {
    synth2_adsr_t adsr;
    synth2_adsr_init(&adsr, 5, 0.0, 0.0, 0.5, 1.0);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
}

TEST(adsr, immediate_adr) {
    synth2_adsr_t adsr;
    synth2_adsr_init(&adsr, 5, 0.0, 0.0, 0.5, 0.0);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    synth2_adsr_keyoff(&adsr);
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
}

TEST(adsr, multiple_keyoff) {
    synth2_adsr_t adsr;
    synth2_adsr_init(&adsr, 5, 0.0, 0.0, 0.5, 1.0);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_S, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));

    synth2_adsr_keyoff(&adsr);
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.5, synth2_adsr_sample(&adsr));
    synth2_adsr_keyoff(&adsr);
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.4, synth2_adsr_sample(&adsr));
    synth2_adsr_keyoff(&adsr);
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.3, synth2_adsr_sample(&adsr));
    synth2_adsr_keyoff(&adsr);
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.2, synth2_adsr_sample(&adsr));
    synth2_adsr_keyoff(&adsr);
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.1, synth2_adsr_sample(&adsr));
    synth2_adsr_keyoff(&adsr);
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    synth2_adsr_keyoff(&adsr);
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
}

TEST(adsr, keyoff_before_s) {
    synth2_adsr_t adsr;
    synth2_adsr_init(&adsr, 5, 1.0, 1.0, 0.5, 1.0);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.2, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.4, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_A, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.6, synth2_adsr_sample(&adsr));

    synth2_adsr_keyoff(&adsr);

    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.6, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.48, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.36, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.24, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_R, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.12, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
    TEST_ASSERT_EQUAL(SYNTH2_ADSR_STAGE_END, synth2_adsr_current_stage(&adsr));
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, synth2_adsr_sample(&adsr));
}

TEST_GROUP_RUNNER(adsr) {
    RUN_TEST_CASE(adsr, normal);
    RUN_TEST_CASE(adsr, stage_changes_between_sample);
    RUN_TEST_CASE(adsr, immediate_a);
    RUN_TEST_CASE(adsr, immediate_d);
    RUN_TEST_CASE(adsr, immediate_ad);
    RUN_TEST_CASE(adsr, immediate_adr);
    RUN_TEST_CASE(adsr, multiple_keyoff);
    RUN_TEST_CASE(adsr, keyoff_before_s)
}
