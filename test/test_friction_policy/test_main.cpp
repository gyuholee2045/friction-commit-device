#include <unity.h>
#include "friction_policy.h"

using namespace fcd;

void setUp() {}
void tearDown() {}

void test_base_when_no_pressure() {
  FrictionConfig c = defaultFrictionConfig();
  TEST_ASSERT_EQUAL_UINT32(c.base_dwell_ms, computeRequiredDwell(0.0f, 0.0f, c));
}

void test_increases_with_stake() {
  FrictionConfig c = defaultFrictionConfig();
  TEST_ASSERT_TRUE(computeRequiredDwell(1.0f, 0.0f, c) >
                   computeRequiredDwell(0.0f, 0.0f, c));
}

void test_increases_with_impulsivity() {
  FrictionConfig c = defaultFrictionConfig();
  TEST_ASSERT_TRUE(computeRequiredDwell(0.0f, 1.0f, c) >
                   computeRequiredDwell(0.0f, 0.0f, c));
}

void test_monotonic_combined() {
  FrictionConfig c = defaultFrictionConfig();
  TEST_ASSERT_TRUE(computeRequiredDwell(1.0f, 1.0f, c) >=
                   computeRequiredDwell(0.5f, 0.5f, c));
}

void test_clamped_to_max() {
  FrictionConfig c = defaultFrictionConfig();
  TEST_ASSERT_TRUE(computeRequiredDwell(1.0f, 1.0f, c) <= c.max_dwell_ms);
  // 입력이 범위를 벗어나도 클램프.
  TEST_ASSERT_TRUE(computeRequiredDwell(5.0f, 5.0f, c) <= c.max_dwell_ms);
}

void test_impulsivity_empty_is_zero() {
  TEST_ASSERT_EQUAL_FLOAT(0.0f, computeImpulsivity(nullptr, 0));
}

void test_impulsivity_all_committed_zero() {
  CommitRecord h[3] = {{1000, 1000, true}, {2000, 2500, true}, {1500, 1500, true}};
  TEST_ASSERT_EQUAL_FLOAT(0.0f, computeImpulsivity(h, 3));
}

void test_impulsivity_immediate_aborts_high() {
  CommitRecord h[2] = {{2000, 0, false}, {2000, 100, false}};
  TEST_ASSERT_TRUE(computeImpulsivity(h, 2) > 0.9f);
}

void test_impulsivity_mixed_midrange() {
  // 절반은 끝까지 기다려 commit, 절반은 즉시 abort → 대략 0.5 부근.
  CommitRecord h[2] = {{2000, 2000, true}, {2000, 0, false}};
  float imp = computeImpulsivity(h, 2);
  TEST_ASSERT_TRUE(imp > 0.4f && imp < 0.6f);
}

int main(int, char**) {
  UNITY_BEGIN();
  RUN_TEST(test_base_when_no_pressure);
  RUN_TEST(test_increases_with_stake);
  RUN_TEST(test_increases_with_impulsivity);
  RUN_TEST(test_monotonic_combined);
  RUN_TEST(test_clamped_to_max);
  RUN_TEST(test_impulsivity_empty_is_zero);
  RUN_TEST(test_impulsivity_all_committed_zero);
  RUN_TEST(test_impulsivity_immediate_aborts_high);
  RUN_TEST(test_impulsivity_mixed_midrange);
  return UNITY_END();
}
