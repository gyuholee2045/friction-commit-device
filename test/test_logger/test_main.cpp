#include <unity.h>
#include <string.h>
#include "logger.h"

using namespace fcd;

void setUp() {}
void tearDown() {}

void test_header_has_columns() {
  char buf[128];
  size_t n = csvHeader(buf, sizeof(buf));
  TEST_ASSERT_TRUE(n > 0);
  TEST_ASSERT_NOT_NULL(strstr(buf, "timestamp_ms"));
  TEST_ASSERT_NOT_NULL(strstr(buf, "impulsivity"));
  TEST_ASSERT_NOT_NULL(strstr(buf, "outcome"));
}

void test_format_row() {
  char buf[128];
  LogRow row{1234, "COMMITTED", 800, 810, 0.75f, "COMMITTED"};
  size_t n = formatCsv(buf, sizeof(buf), row);
  TEST_ASSERT_TRUE(n > 0);
  TEST_ASSERT_EQUAL_STRING("1234,COMMITTED,800,810,0.750,COMMITTED", buf);
}

void test_truncation_returns_zero() {
  char buf[8];  // 너무 작음
  LogRow row{1234, "COMMITTED", 800, 810, 0.75f, "COMMITTED"};
  TEST_ASSERT_EQUAL_UINT(0, formatCsv(buf, sizeof(buf), row));
}

int main(int, char**) {
  UNITY_BEGIN();
  RUN_TEST(test_header_has_columns);
  RUN_TEST(test_format_row);
  RUN_TEST(test_truncation_returns_zero);
  return UNITY_END();
}
