#include "input_debounce.h"

namespace fcd {

Debouncer::Debouncer(uint32_t stable_ms, bool initial)
    : stable_ms_(stable_ms),
      stable_(initial),
      last_raw_(initial),
      last_change_ms_(0),
      rose_(false),
      fell_(false) {}

bool Debouncer::update(bool raw, uint32_t now_ms) {
  rose_ = false;
  fell_ = false;
  if (raw != last_raw_) {
    last_raw_ = raw;
    last_change_ms_ = now_ms;  // 원시값이 바뀐 시점 기록
  }
  // 원시값이 stable_ms 이상 유지되면 안정 상태로 채택
  if ((uint32_t)(now_ms - last_change_ms_) >= stable_ms_ && raw != stable_) {
    bool prev = stable_;
    stable_ = raw;
    if (!prev && stable_) rose_ = true;
    if (prev && !stable_) fell_ = true;
  }
  return stable_;
}

}  // namespace fcd
