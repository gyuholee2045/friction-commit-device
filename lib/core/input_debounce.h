#pragma once
#include <stdint.h>

// Input — 보드 비의존 디바운서. Arduino 호출 없이 raw 입력 + now_ms 를 주입받아
// 안정화된 상태/에지를 계산한다. 호스트 테스트 가능.

namespace fcd {

class Debouncer {
 public:
  explicit Debouncer(uint32_t stable_ms = 20, bool initial = false);

  // raw(튀는 원시값)와 now_ms 를 받아 디바운스된 상태를 갱신·반환.
  bool update(bool raw, uint32_t now_ms);

  bool state() const { return stable_; }
  bool rose() const { return rose_; }  // 이번 update 에서 false->true
  bool fell() const { return fell_; }  // 이번 update 에서 true->false

 private:
  uint32_t stable_ms_;
  bool stable_;
  bool last_raw_;
  uint32_t last_change_ms_;
  bool rose_;
  bool fell_;
};

}  // namespace fcd
