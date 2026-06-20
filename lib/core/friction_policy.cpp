#include "friction_policy.h"

namespace fcd {

FrictionConfig defaultFrictionConfig() {
  FrictionConfig c;
  c.base_dwell_ms = 800;
  c.max_dwell_ms = 6000;
  c.stake_gain_ms = 2000;
  c.impulsivity_gain_ms = 3000;
  return c;
}

float clamp01(float v) {
  if (v < 0.0f) return 0.0f;
  if (v > 1.0f) return 1.0f;
  return v;
}

float computeImpulsivity(const CommitRecord* history, size_t count) {
  if (history == nullptr || count == 0) return 0.0f;
  float sum = 0.0f;
  for (size_t i = 0; i < count; ++i) {
    const CommitRecord& r = history[i];
    if (r.committed || r.required_dwell_ms == 0) {
      continue;  // 끝까지 기다림 → 충동성 기여 없음
    }
    float waited = (float)r.actual_dwell_ms / (float)r.required_dwell_ms;
    sum += (1.0f - clamp01(waited));  // 일찍 놓을수록 1 에 가까움
  }
  return clamp01(sum / (float)count);
}

uint32_t computeRequiredDwell(float stake, float impulsivity,
                              const FrictionConfig& cfg) {
  stake = clamp01(stake);
  impulsivity = clamp01(impulsivity);
  float d = (float)cfg.base_dwell_ms +
            stake * (float)cfg.stake_gain_ms +
            impulsivity * (float)cfg.impulsivity_gain_ms;
  if (d < (float)cfg.base_dwell_ms) d = (float)cfg.base_dwell_ms;
  if (d > (float)cfg.max_dwell_ms) d = (float)cfg.max_dwell_ms;
  return (uint32_t)(d + 0.5f);
}

}  // namespace fcd
