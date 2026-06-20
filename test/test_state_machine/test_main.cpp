#include <unity.h>
#include "state_machine.h"

using namespace fcd;

void setUp() {}
void tearDown() {}

// stake=0, impulsivity=0 → required dwell = base (기본 800ms).
static const uint32_t kBaseDwell = 800;

void test_mistap_returns_idle() {
  StateMachine sm;
  uint32_t t = 0;
  TEST_ASSERT_EQUAL_INT((int)State::IDLE, (int)sm.step(false, 0.0f, t).state);
  t = 10;
  TEST_ASSERT_EQUAL_INT((int)State::ARMED, (int)sm.step(true, 0.0f, t).state);
  t = 60;  // arm_grace(120) 이전
  TEST_ASSERT_EQUAL_INT((int)State::ARMED, (int)sm.step(true, 0.0f, t).state);
  t = 70;  // grace 전에 뗌 → mis-tap
  StepResult r = sm.step(false, 0.0f, t);
  TEST_ASSERT_EQUAL_INT((int)State::IDLE, (int)r.state);
  TEST_ASSERT_EQUAL_INT((int)Outcome::NONE, (int)r.outcome);
}

void test_commit_success() {
  StateMachine sm;
  uint32_t t = 0;
  sm.step(false, 0.0f, t);
  t = 10;
  sm.step(true, 0.0f, t);  // ARMED, required=base(800)
  bool committed = false;
  for (t = 20; t <= 2000; t += 10) {
    StepResult r = sm.step(true, 0.0f, t);
    if (r.outcome == Outcome::COMMITTED) {
      committed = true;
      TEST_ASSERT_EQUAL_INT((int)State::COMMITTED, (int)r.state);
      TEST_ASSERT_TRUE(r.actual_dwell_ms >= r.required_dwell_ms);
      TEST_ASSERT_EQUAL_UINT32(kBaseDwell, r.required_dwell_ms);
      break;
    }
  }
  TEST_ASSERT_TRUE(committed);
}

void test_abort_releases_early() {
  StateMachine sm;
  uint32_t t = 0;
  sm.step(false, 0.0f, t);
  t = 10;
  sm.step(true, 0.0f, t);  // ARMED
  t = 200;
  TEST_ASSERT_EQUAL_INT((int)State::DWELLING,
                        (int)sm.step(true, 0.0f, t).state);  // grace 지남
  t = 400;  // actual ~390 < 800 → abort
  StepResult r = sm.step(false, 0.0f, t);
  TEST_ASSERT_EQUAL_INT((int)Outcome::ABORTED, (int)r.outcome);
  TEST_ASSERT_TRUE(r.actual_dwell_ms < r.required_dwell_ms);
}

void test_cooldown_blocks_then_idle() {
  StateMachine sm;
  uint32_t t = 0;
  sm.step(false, 0.0f, t);
  t = 10;
  sm.step(true, 0.0f, t);
  StepResult r;
  for (t = 20; t <= 2000; t += 10) {
    r = sm.step(true, 0.0f, t);
    if (r.outcome == Outcome::COMMITTED) break;
  }
  // commit 직후 다음 틱 → COOLDOWN
  t += 10;
  r = sm.step(false, 0.0f, t);
  TEST_ASSERT_EQUAL_INT((int)State::COOLDOWN, (int)r.state);
  // 쿨다운 중 누름 무시
  t += 10;
  r = sm.step(true, 0.0f, t);
  TEST_ASSERT_EQUAL_INT((int)State::COOLDOWN, (int)r.state);
  // 버튼 떼고 쿨다운(1500ms) 경과 → IDLE
  uint32_t cd_end = t + 1600;
  for (; t <= cd_end; t += 50) r = sm.step(false, 0.0f, t);
  TEST_ASSERT_EQUAL_INT((int)State::IDLE, (int)r.state);
  // 새 누름 에지 → 재-ARM
  t += 10;
  TEST_ASSERT_EQUAL_INT((int)State::ARMED, (int)sm.step(true, 0.0f, t).state);
}

void test_history_raises_required_after_aborts() {
  StateMachine sm;
  uint32_t t = 100;

  // 1회차 ARM 의 required (이력 없음 → base).
  uint32_t first_required = sm.step(true, 0.0f, t).required_dwell_ms;  // IDLE→ARMED
  t += 200;
  sm.step(true, 0.0f, t);   // ARMED→DWELLING (grace 지남)
  t += 10;
  sm.step(false, 0.0f, t);  // 곧바로 뗌 → ABORTED (이력에 abort 1건 기록)
  uint32_t cd_end = t + 1700;
  for (; t <= cd_end; t += 50) sm.step(false, 0.0f, t);  // 쿨다운 끝 → IDLE

  // 2회차 ARM 의 required (충동성 반영 → 더 커야 함).
  t += 50;
  uint32_t later_required = sm.step(true, 0.0f, t).required_dwell_ms;  // IDLE→ARMED

  TEST_ASSERT_EQUAL_UINT32(kBaseDwell, first_required);
  TEST_ASSERT_TRUE(later_required > first_required);
}

int main(int, char**) {
  UNITY_BEGIN();
  RUN_TEST(test_mistap_returns_idle);
  RUN_TEST(test_commit_success);
  RUN_TEST(test_abort_releases_early);
  RUN_TEST(test_cooldown_blocks_then_idle);
  RUN_TEST(test_history_raises_required_after_aborts);
  return UNITY_END();
}
