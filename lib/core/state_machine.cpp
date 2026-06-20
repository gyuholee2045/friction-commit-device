#include "state_machine.h"

namespace fcd {

SmConfig defaultSmConfig() {
  SmConfig c;
  c.arm_grace_ms = 120;
  c.cooldown_ms = 1500;
  return c;
}

const char* stateName(State s) {
  switch (s) {
    case State::IDLE: return "IDLE";
    case State::ARMED: return "ARMED";
    case State::DWELLING: return "DWELLING";
    case State::COMMITTED: return "COMMITTED";
    case State::ABORTED: return "ABORTED";
    case State::COOLDOWN: return "COOLDOWN";
  }
  return "?";
}

const char* outcomeName(Outcome o) {
  switch (o) {
    case Outcome::NONE: return "NONE";
    case Outcome::COMMITTED: return "COMMITTED";
    case Outcome::ABORTED: return "ABORTED";
  }
  return "?";
}

StateMachine::StateMachine(FrictionConfig fcfg, SmConfig scfg)
    : fcfg_(fcfg),
      scfg_(scfg),
      state_(State::IDLE),
      press_start_ms_(0),
      dwell_start_ms_(0),
      required_dwell_ms_(0),
      cooldown_start_ms_(0),
      stake_at_arm_(0.0f),
      last_impulsivity_(0.0f),
      prev_button_(false),
      history_count_(0),
      history_head_(0) {
  for (size_t i = 0; i < kHistory; ++i) {
    history_[i] = CommitRecord{0, 0, false};
  }
}

void StateMachine::recordOutcome(bool committed, uint32_t required,
                                 uint32_t actual) {
  history_[history_head_] = CommitRecord{required, actual, committed};
  history_head_ = (history_head_ + 1) % kHistory;
  if (history_count_ < kHistory) history_count_++;
}

StepResult StateMachine::step(bool button, float stake, uint32_t now_ms) {
  StepResult res;
  res.state = state_;
  res.outcome = Outcome::NONE;
  res.required_dwell_ms = 0;
  res.actual_dwell_ms = 0;
  res.progress = 0.0f;

  const bool pressed_edge = (button && !prev_button_);

  switch (state_) {
    case State::COMMITTED:
    case State::ABORTED:
      // 표시 상태(직전 틱에 보고됨) → 다음 틱에 COOLDOWN 으로 진입.
      // cooldown_start_ms_ 는 해소 시점에 이미 설정됨.
      state_ = State::COOLDOWN;
      [[fallthrough]];

    case State::COOLDOWN:
      if ((uint32_t)(now_ms - cooldown_start_ms_) >= scfg_.cooldown_ms) {
        state_ = State::IDLE;  // 버튼을 누르고 있어도 자동 ARM 안 함(새 에지 필요)
      }
      break;

    case State::IDLE:
      if (pressed_edge) {
        last_impulsivity_ = computeImpulsivity(history_, history_count_);
        stake_at_arm_ = stake;
        required_dwell_ms_ =
            computeRequiredDwell(stake, last_impulsivity_, fcfg_);
        press_start_ms_ = now_ms;
        dwell_start_ms_ = now_ms;  // dwell 은 의도(누름) 시점부터 카운트
        state_ = State::ARMED;
        res.required_dwell_ms = required_dwell_ms_;  // ARM 즉시 required 보고
      }
      break;

    case State::ARMED: {
      if (!button) {
        state_ = State::IDLE;  // grace 전에 뗌 → mis-tap, 기록 없음
        break;
      }
      const uint32_t held = (uint32_t)(now_ms - press_start_ms_);
      if (held >= scfg_.arm_grace_ms) {
        state_ = State::DWELLING;
      }
      res.required_dwell_ms = required_dwell_ms_;
      res.actual_dwell_ms = held;
      res.progress =
          required_dwell_ms_ ? (float)held / (float)required_dwell_ms_ : 0.0f;
      if (res.progress > 1.0f) res.progress = 1.0f;
      break;
    }

    case State::DWELLING: {
      const uint32_t actual = (uint32_t)(now_ms - dwell_start_ms_);
      if (!button) {
        recordOutcome(false, required_dwell_ms_, actual);
        cooldown_start_ms_ = now_ms;
        state_ = State::ABORTED;
        res.outcome = Outcome::ABORTED;
        res.required_dwell_ms = required_dwell_ms_;
        res.actual_dwell_ms = actual;
        res.progress = 0.0f;
        break;
      }
      if (actual >= required_dwell_ms_) {
        recordOutcome(true, required_dwell_ms_, actual);
        cooldown_start_ms_ = now_ms;
        state_ = State::COMMITTED;
        res.outcome = Outcome::COMMITTED;
        res.required_dwell_ms = required_dwell_ms_;
        res.actual_dwell_ms = actual;
        res.progress = 1.0f;
        break;
      }
      res.required_dwell_ms = required_dwell_ms_;
      res.actual_dwell_ms = actual;
      res.progress = (float)actual / (float)required_dwell_ms_;
      if (res.progress > 1.0f) res.progress = 1.0f;
      break;
    }
  }

  res.state = state_;
  prev_button_ = button;
  return res;
}

}  // namespace fcd
