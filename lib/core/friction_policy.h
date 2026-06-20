#pragma once
#include <stdint.h>
#include <stddef.h>

// FrictionPolicy — 보드 비의존 순수 함수.
// 상호작용 이력으로 impulsivity 를 추정하고, stake + impulsivity 로
// "버튼 확정에 걸 required dwell(ms)"을 계산한다. Arduino 의존 없음 → 호스트 테스트 가능.

namespace fcd {

// 과거 한 번의 확정 시도 결과(impulsivity 추정용).
struct CommitRecord {
  uint32_t required_dwell_ms;
  uint32_t actual_dwell_ms;
  bool committed;  // true=COMMITTED, false=ABORTED
};

struct FrictionConfig {
  uint32_t base_dwell_ms;        // 최소 마찰 (stake=0, impulsivity=0)
  uint32_t max_dwell_ms;         // 상한 클램프
  uint32_t stake_gain_ms;        // stake=1.0 일 때 가산량
  uint32_t impulsivity_gain_ms;  // impulsivity=1.0 일 때 가산량
};

FrictionConfig defaultFrictionConfig();

// [0,1] 클램프 (테스트 노출용 헬퍼).
float clamp01(float v);

// 순수: 최근 이력에서 impulsivity[0,1] 추정.
// 휴리스틱 — required 대비 한참 못 미치고 ABORTED 된 시도일수록 충동적(rush)으로 본다.
// COMMITTED(끝까지 기다림)는 충동성 0 으로 기여.
float computeImpulsivity(const CommitRecord* history, size_t count);

// 순수: stake[0,1], impulsivity[0,1] 에 대한 required dwell(ms).
uint32_t computeRequiredDwell(float stake, float impulsivity,
                              const FrictionConfig& cfg);

}  // namespace fcd
