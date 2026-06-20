#pragma once
#include <stdint.h>
#include <stddef.h>
#include "friction_policy.h"

// StateMachine — 보드 비의존 상호작용 상태기.
// 시간/입력을 주입받아(now_ms, debounced button, stake) 상태 전이를 수행하고,
// ARM 시점에 FrictionPolicy 로 required dwell 을 산정한다. millis()/digitalRead 등
// Arduino 호출이 전혀 없어 호스트에서 결정적으로 테스트 가능.
//
// 상태: IDLE -> ARMED -> DWELLING -> (COMMITTED | ABORTED) -> COOLDOWN -> IDLE
//   IDLE      : 대기. 버튼 누름 에지에서 ARM.
//   ARMED     : 의도 등록(required dwell 산정). arm_grace 전에 떼면 mis-tap → IDLE.
//   DWELLING  : 누르고 있는 동안 actual_dwell 누적. progress = actual/required.
//   COMMITTED : actual >= required 도달(계속 누름). LED 완전 점등.
//   ABORTED   : required 도달 전에 뗌. LED 소등.
//   COOLDOWN  : 종료 후 lockout. 끝나면 IDLE (단, 새 누름 에지가 있어야 재-ARM).

namespace fcd {

enum class State : uint8_t {
  IDLE, ARMED, DWELLING, COMMITTED, ABORTED, COOLDOWN
};

enum class Outcome : uint8_t { NONE, COMMITTED, ABORTED };

struct SmConfig {
  uint32_t arm_grace_ms;  // 이 시간 넘게 눌러야 의도로 인정(미만이면 mis-tap)
  uint32_t cooldown_ms;   // 종료 후 lockout 시간
};

SmConfig defaultSmConfig();

struct StepResult {
  State state;
  Outcome outcome;             // 시도가 '해소되는' 틱에만 NONE 이외
  uint32_t required_dwell_ms;  // 진행/방금 종료된 시도의 요구 dwell
  uint32_t actual_dwell_ms;    // 달성 dwell
  float progress;              // 0..1 (LED 램프용)
};

const char* stateName(State s);
const char* outcomeName(Outcome o);

class StateMachine {
 public:
  static const size_t kHistory = 8;

  StateMachine(FrictionConfig fcfg = defaultFrictionConfig(),
               SmConfig scfg = defaultSmConfig());

  // 한 틱 진행. button=디바운스된 버튼(true=눌림), stake=0..1(ARM 시 샘플), now_ms=단조시간.
  StepResult step(bool button, float stake, uint32_t now_ms);

  State state() const { return state_; }
  float impulsivity() const { return last_impulsivity_; }

 private:
  void recordOutcome(bool committed, uint32_t required, uint32_t actual);

  FrictionConfig fcfg_;
  SmConfig scfg_;
  State state_;

  uint32_t press_start_ms_;
  uint32_t dwell_start_ms_;
  uint32_t required_dwell_ms_;
  uint32_t cooldown_start_ms_;
  float stake_at_arm_;
  float last_impulsivity_;
  bool prev_button_;

  CommitRecord history_[kHistory];
  size_t history_count_;
  size_t history_head_;
};

}  // namespace fcd
