# DWELL — 프로젝트 팩트시트 (사실 정리)

> 출처: 이 작업방에서 실제로 작성·확인한 코드(`lib/core`, `src/main.cpp`, `test/`)와 설정(`platformio.ini`, `diagram.json`), 프로젝트 문서(`CLAUDE.md`). 미수행/미확인 항목은 "해당 없음" 또는 "미정"으로 표기.
> 용도: LinkedIn About 문장 다듬기 + 웹 포트폴리오 케이스 작성 소스. 추측·미화 없이 사실만.

## 1. 한 줄 정의
DWELL은 Arduino Uno 기반 펌웨어/장치로, "확정(commit)" 버튼을 누르고 있어야 하는 **요구 홀드 시간(required dwell)** 을 상호작용 이력으로 계산해 부과하고, 각 시도를 시리얼 CSV로 로깅한다.

## 2. 핵심 컨셉 / 가설
- **문제의식:** AI가 디지털 결정을 매끄럽게 대행하면서, 사람이 반사적으로 위임하고 독자적 판단을 덜 쓰게 된다는 문제의식에서 출발.
- **설계 전제(premise):** 결정(확정) 순간에 의도된 시간 마찰을 걸되, 그 양을 사용자의 충동성에 비례시키면 충동적 확정을 줄이고 성찰의 여지를 만들 수 있다.
- **정식 검증 가설 / 통계적 검증:** 해당 없음. 이 방에서는 사용자 연구를 수행하지 않았고, 프로젝트는 "엔지니어링·디자인 시연(design probe)"으로 명시. impulsivity 모델과 상수는 휴리스틱.
- **"intentional friction"의 구체적 구현:**
  - 버튼을 누른 시점부터 요구 홀드 시간을 카운트. 그 시간을 끝까지 채워야 COMMITTED.
  - 요구 시간은 고정값이 아니라 `computeRequiredDwell(stake, impulsivity)` 로 산정: `required = base + stake·stake_gain + impulsivity·impulsivity_gain`, 하한/상한 클램프.
  - 기본 상수(코드값): base 800ms, 상한 6000ms, stake_gain 2000ms, impulsivity_gain 3000ms.
  - 즉 충동적 이력이 쌓일수록(impulsivity↑) 같은 결정에도 요구 홀드가 길어진다.

## 3. 기술 구조
**하드웨어 (Wokwi 가상 보드, `diagram.json`)**
- 보드: Arduino Uno (ATmega328P)
- 입력: 버튼 D2 (INPUT_PULLUP, 눌림=LOW), 포텐셔미터 A0 (stake 0..1로 정규화)
- 출력: LED D9 (PWM, 220Ω 경유), 시리얼 115200
- NeoPixel 16-링을 시도했으나 Wokwi 부품 미지원으로 단일 LED로 되돌림.

**소프트웨어 (PlatformIO, C++17, 동적할당·예외 미사용)**
- 보드 비의존 순수 코어 `lib/core` 4개 모듈:
  - `input_debounce` — raw 버튼 + now → 디바운스 상태/에지 (20ms)
  - `friction_policy` — 이력 → impulsivity 추정, (stake, impulsivity) → required dwell
  - `state_machine` — 상태 전이
  - `logger` — LogRow → CSV 문자열 (AVR의 `%f` 미지원 회피해 impulsivity는 수동 "d.ddd" 포맷)
- 상태기: `IDLE → ARMED → DWELLING → (COMMITTED | ABORTED) → COOLDOWN → IDLE`
  - ARMED: 의도 등록 + required dwell 산정. arm_grace 미만에 떼면 mis-tap → IDLE.
  - COOLDOWN 종료 후 재-ARM 하려면 새 누름 에지 필요.
  - 이력 버퍼 8개(`kHistory=8`)를 순환 저장해 impulsivity 계산에 사용.
- `src/main.cpp` = 얇은 I/O 어댑터(Phase 3): `millis()/digitalRead()/analogRead()/Serial` 호출은 이 파일에만. 코어는 시간·입력을 인자로 주입받음.

**작성한 코드의 성격 (단순 배선이 아님)**
- 디바운스(에지 검출), 충동성 추정 휴리스틱, 적응형 마찰 계산, 6상태 전이 로직, CSV 포맷팅이 모두 보드와 분리된 순수 함수로 구현됨.
- impulsivity 휴리스틱: 끝까지 기다려 COMMITTED 한 시도는 기여 0, required 대비 일찍 떼고 ABORTED 한 시도일수록 1에 가깝게 가중, 이력 평균을 [0,1]로 클램프.
- CSV 필드: timestamp_ms, event(상태명), required_dwell_ms, actual_dwell_ms, impulsivity, outcome.

## 4. 작업 과정
- **빌드 순서(엄수):** (1) 4개 모듈 스캐폴드 → (2) 순수 함수 + 호스트 단위 테스트 먼저 → (3) 테스트 통과 후 핀 I/O(`main.cpp`) → (4) 실물 보드.
- **현재 위치:** (1)(2) 완료, (3) 코드 완성·Uno 빌드 성공(Flash 약 23%), Wokwi 시각 확인만 남음. (4) 실물 보드 미착수.
- **바뀐 결정:** NeoPixel 링 → Wokwi 미지원으로 단일 LED 회귀. 하이브리드 결정 = 현재는 Wokwi가 확정 자산, 실물 보드는 후속 옵션.
- **막혔던 지점/수정:** `state_machine`에서 IDLE→ARMED 전환 틱이 required_dwell_ms를 0으로 반환하던 결함을 1줄 수정. 단위 테스트(`test_history_raises_required_after_aborts`)가 검출.

## 5. 결과물 / 평가
- **완성된 것:**
  - 보드 비의존 순수 코어 + 단위 테스트 20개 통과(input_debounce 3, logger 3, friction_policy 9, state_machine 5 / `pio test -e native`).
  - Phase 3 I/O 어댑터 코드 + Uno 빌드 성공.
  - Wokwi 회로 정의(`diagram.json`).
  - 별도 트랙으로 웹 프로토타입(Three.js): `web/index.html`(단일 조건), `web/compare.html`(A/B/C 비교). 아두이노 장치와는 분리된 UX 시연물.
- **평가(사용자 연구):** 해당 없음. 가설 검증·표본 크기(N)·인간 대상 측정 지표·결과 모두 미수행. 장치가 CSV를 로깅하도록 만들어졌으나, 이 방에서 실제 데이터 수집/분석은 하지 않음.
- **아직 안 된 부분:** Wokwi 시각 동작 확인, 실물 보드 제작, 사용자 평가. impulsivity 모델·타이밍 상수는 검증된 값이 아니라 design probe.

## 6. HCI / UX 관점에서의 의미
- **연구 방향과의 연결:** "알고리즘/AI 주도 환경에서의 의도된 마찰"을, 추상 주장이 아니라 충동성에 적응하는 마찰이라는 구체적 메커니즘으로 구현한 사례. 보드 비의존 + 테스트 가능한 코어 = 주장을 다시 돌려 확인할 수 있는 형태로 만든 것이 핵심.
- **화면이 아닌 물리 장치로 만든 이유(이 방에서 다룬 논거):** 세 조건 비교(마찰 없음 / 화면 마찰 / 물리 마찰)에서, 화면 다이얼로그형 마찰은 사용자가 그대로 눌러 지나치기 쉬운 반면, 물리적으로 "머물러 있어야 하는" 마찰은 자동조종으로 통과하기 어렵다는 설계 논거. 두 매체(화면=느낌, 하드웨어=검증 가능)로 같은 로직을 구현해 일반화와 엔지니어링 신뢰를 동시에 노린 것. (이는 설계 논거이며 사용자 검증된 결론은 아님.)
