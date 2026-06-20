#include "logger.h"
#include <stdio.h>

namespace fcd {

size_t csvHeader(char* out, size_t cap) {
  int n = snprintf(
      out, cap,
      "timestamp_ms,event,required_dwell_ms,actual_dwell_ms,impulsivity,outcome");
  if (n < 0 || (size_t)n >= cap) return 0;
  return (size_t)n;
}

size_t formatCsv(char* out, size_t cap, const LogRow& row) {
  // impulsivity[0,1] → 0..1000 정수로 스케일 후 "d.ddd" 로 출력(%f 회피).
  int milli = (int)(row.impulsivity * 1000.0f + 0.5f);
  if (milli < 0) milli = 0;
  if (milli > 1000) milli = 1000;

  int n = snprintf(out, cap, "%lu,%s,%lu,%lu,%d.%03d,%s",
                   (unsigned long)row.timestamp_ms,
                   row.event ? row.event : "",
                   (unsigned long)row.required_dwell_ms,
                   (unsigned long)row.actual_dwell_ms,
                   milli / 1000, milli % 1000,
                   row.outcome ? row.outcome : "");
  if (n < 0 || (size_t)n >= cap) return 0;
  return (size_t)n;
}

}  // namespace fcd
