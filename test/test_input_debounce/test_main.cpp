#include <unity.h>
#include "input_debounce.h"

using namespace fcd;

void setUp() {}
void tearDown() {}

void test_ignores_short_bounce() {
  Debouncer d(20, false);
  TEST_ASSERT_FALSE(d.update(true, 0));    // 막 눌림, 아직 불안정
  TEST_ASSERT_FALSE(d.update(false, 5));   // 5ms 만에 튐
  TEST_ASSERT_FALSE(d.state());
}

void test_stable_after_threshold() {
  Debouncer d(20, false);
  d.update(true, 0);
  TEST_ASSERT_FALSE(d.update(true, 10));   // 10ms < 20
  TEST_ASSERT_TRUE(d.update(true, 25));    // >= 20 → 안정 true
  TEST_ASSERT_TRUE(d.rose());
}

void test_fell_edge() {
  Debouncer d(20, true);
  d.update(false, 0);
  TEST_ASSERT_TRUE(d.update(false, 10));   // 아직 true 유지
  TEST_ASSERT_FALSE(d.update(false, 30));  // 임계 넘겨 false
  TEST_ASSERT_TRUE(d.fell());
}

int main(int, char**) {
  UNITY_BEGIN();
  RUN_TEST(test_ignores_short_bounce);
  RUN_TEST(test_stable_after_threshold);
  RUN_TEST(test_fell_edge);
  return UNITY_END();
}
