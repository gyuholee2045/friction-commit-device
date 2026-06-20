#pragma once
#include <stdint.h>
#include <stddef.h>

// Logger — 순수 CSV 포맷터. Serial/Arduino 의존 없음(문자 버퍼에만 기록).
// 실제 출력(Serial.print)은 보드 어댑터(Phase 3)가 담당한다.
// impulsivity 는 AVR snprintf 의 %f 미지원 문제를 피하려고 "d.ddd" 형태로 수동 포맷.

namespace fcd {

struct LogRow {
  uint32_t timestamp_ms;
  const char* event;            // 보통 상태명
  uint32_t required_dwell_ms;
  uint32_t actual_dwell_ms;
  float impulsivity;            // 0..1
  const char* outcome;          // outcome 명
};

// CSV 헤더(줄바꿈 제외). 기록된 문자 수 반환(NUL 제외), 버퍼 부족 시 0.
size_t csvHeader(char* out, size_t cap);

// 한 행을 CSV 로 포맷. 기록 문자 수 반환(NUL 제외), 버퍼 부족 시 0.
size_t formatCsv(char* out, size_t cap, const LogRow& row);

}  // namespace fcd
