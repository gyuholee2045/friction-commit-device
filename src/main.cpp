// friction-commit-device — Arduino Uno I/O 어댑터 (Phase 3, 단일 LED)
//
// 코어(lib/core)는 그대로. 핀 입력을 코어에 주입하고, 결과를 LED/Serial 로 내보내는
// 얇은 어댑터. millis()/digitalRead()/analogRead()/Serial 호출은 이 파일에만.
//
// 출력 매핑 (CLAUDE.md):
//   DWELLING  = progress(0..1)에 비례한 LED 밝기 (점진 점등)
//   COMMITTED = 완전 점등 (+ kCommitFlashMs 유지해 눈에 보이게)
//   그 외      = 소등
//
// 회로 (Wokwi Uno):
//   D2  버튼        — INPUT_PULLUP, 눌림 = LOW
//   D9  LED(PWM)    — 220Ω 저항 경유
//   A0  포텐셔미터   — stake 0..1
//   Serial 115200   — LogRow CSV
//
// (NeoPixel 16-링 버전은 실물 보드 단계에서 도입 예정 — Wokwi 부품 미지원으로 단일 LED 유지)

#include <Arduino.h>
#include "input_debounce.h"
#include "friction_policy.h"
#include "state_machine.h"
#include "logger.h"

using namespace fcd;

static const uint8_t  PIN_BTN = 2;
static const uint8_t  PIN_LED = 9;   // PWM
static const uint8_t  PIN_POT = A0;
static const uint32_t kCommitFlashMs = 700;

static Debouncer button(20, false);
static StateMachine sm;
static uint32_t commit_flash_until = 0;
static char csv[96];

void setup() {
  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  if (csvHeader(csv, sizeof(csv)) > 0) Serial.println(csv);
}

void loop() {
  const uint32_t now = millis();

  const bool raw = (digitalRead(PIN_BTN) == LOW);
  const bool pressed = button.update(raw, now);
  const float stake = (float)analogRead(PIN_POT) / 1023.0f;

  const StepResult r = sm.step(pressed, stake, now);

  uint8_t level;
  if (now < commit_flash_until) {
    level = 255;
  } else if (r.state == State::COMMITTED) {
    level = 255;
    commit_flash_until = now + kCommitFlashMs;
  } else if (r.state == State::DWELLING) {
    level = (uint8_t)(r.progress * 255.0f + 0.5f);
  } else {
    level = 0;
  }
  analogWrite(PIN_LED, level);

  if (r.outcome != Outcome::NONE) {
    LogRow row{now, stateName(r.state), r.required_dwell_ms, r.actual_dwell_ms,
               sm.impulsivity(), outcomeName(r.outcome)};
    if (formatCsv(csv, sizeof(csv), row) > 0) Serial.println(csv);
  }
}
