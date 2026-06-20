# friction-commit-device

버튼 "확정(commit)"에 **계산된 시간 마찰(required dwell)** 을 거는 임베디드 펌웨어.
충동적 확정을 줄이고, 상호작용 데이터를 시리얼 CSV로 로깅한다.

## 핵심 설계 원칙 (반드시 지킬 것)
- **판단 로직은 보드 비의존 순수 함수**로 분리한다: `FrictionPolicy`(dwell 계산), `StateMachine`(상태 전이).
  - `Arduino.h`, `millis()`, `digitalRead()`, `Serial` 를 **코어(lib/core)에서 직접 호출하지 않는다.** 시간·입력은 인자로 주입.
  - 그래야 노트북(native)에서 결정적 단위 테스트가 가능하다.
- 하드웨어는 I/O 어댑터일 뿐. 핀 읽기/쓰기, millis(), Serial 출력은 **Phase 3의 `src/main.cpp`** 에만 둔다.
- **작성 순서 엄수:**
  1. 모듈 4개 파일 분리 스캐폴드  ← 완료
  2. FrictionPolicy·상태 전이 순수 함수 + 호스트 단위 테스트 먼저  ← 완료(작성). 테스트 통과 확인 필요
  3. 테스트 통과 후에야 핀 I/O 연결 (`src/main.cpp`)  ← 미착수

## 모듈 (lib/core, 모두 보드 비의존)
| 모듈 | 파일 | 책임 |
|---|---|---|
| Input | `input_debounce.{h,cpp}` | raw 버튼 + now → 디바운스 상태/에지 (순수, 시간 주입) |
| FrictionPolicy | `friction_policy.{h,cpp}` | 이력→impulsivity, (stake,impulsivity)→required dwell (순수) |
| StateMachine | `state_machine.{h,cpp}` | IDLE/ARMED/DWELLING/COMMITTED/ABORTED/COOLDOWN 전이 |
| Logger | `logger.{h,cpp}` | LogRow→CSV 문자열 (순수, Serial 비의존; %f 미사용) |

## 상태 전이
```
IDLE --press--> ARMED --hold>=grace--> DWELLING --actual>=required--> COMMITTED
  ^               | release<grace          | release<required             |
  |               v (mis-tap)              v                             v
  +------------- IDLE                    ABORTED ----------------> COOLDOWN --timeout--> IDLE
```
- dwell 은 누름(의도) 시점부터 카운트. `arm_grace` 는 오터치(mis-tap) 걸러내기용.
- COOLDOWN 종료 후엔 **새 누름 에지**가 있어야 재-ARM (계속 누르고 있으면 ARM 안 됨).

## 출력 매핑 (Phase 3에서 구현)
- LED: DWELLING = progress(0..1)에 비례한 점진 점등, COMMITTED = 완전 점등, ABORTED/그외 = 소등.
- 진동모터: **선택적** 출력 모듈로만. 코어 로직은 모터 존재 여부에 의존하지 않는다.

## 실행/테스트
- **순수 함수 테스트(노트북, Wokwi 아님):** `pio test -e native`
- **핀 I/O 동작 확인:** Wokwi 가상 보드 (Phase 3 이후)
- **실물 보드:** 후속 사람 평가 단계에서만 도입

## 환경
- 보드: Arduino Uno (ATmega328P) · 툴체인: PlatformIO · 시리얼 115200
- 코어는 C++17, 동적할당/예외 미사용(임베디드 안전). Logger 는 `snprintf` 의 `%f` 미지원(AVR)을 피해 정수 스케일로 출력.

## 작업 지침
- 코어에 Arduino 의존을 새로 들이지 말 것. 새 로직은 순수 함수로 + 테스트 먼저.
- 상태 전이 의미를 바꾸면 `test_state_machine` 도 함께 갱신.
