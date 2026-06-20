# SESSION HANDOFF — friction-commit-device

> 목적: 새 Claude Code 세션이 **이전 대화 없이도** 누락 없이 이어서 작업하도록 모든 컨텍스트를 전달한다.
> 새 세션을 이 폴더에서 열면 먼저 이 파일과 `CLAUDE.md` 를 읽어라.

---

## 1. 프로젝트 한 줄 요약
버튼 확정(commit)에 **계산된 시간 마찰(required dwell)** 을 거는 Arduino Uno 펌웨어. 충동적 확정을 줄이고 상호작용 데이터를 시리얼 CSV로 로깅하는 연구용 인터랙션 장치.

## 2. 아키텍처 + 철칙 (절대 어기지 말 것)
- 흐름: **Input(디바운스) → FrictionPolicy(이력→impulsivity→required dwell, 순수함수) → StateMachine(상태기) → Logger(CSV)**
- **판단 로직(FrictionPolicy, StateMachine)은 보드 비의존 순수 함수.** `lib/core` 에서 `Arduino.h`/`millis()`/`Serial`/`digitalRead/Write`/`analogRead` **직접 호출 금지.** 시간·입력은 인자로 주입(`now_ms`, `button`, `stake`).
- 하드웨어는 I/O 어댑터일 뿐 → 핀 읽기/쓰기·Serial 출력은 **Phase 3의 `src/main.cpp`** 에만.
- 코어는 C++17, 동적할당/예외 미사용. Logger 는 AVR `snprintf` 의 `%f` 미지원을 피해 impulsivity 를 정수 스케일("d.ddd")로 출력.

## 3. 빌드 순서 (엄수) + 현재 위치
1. ✅ **Phase 1** 모듈 4개 분리 스캐폴드 — 완료
2. ✅ **Phase 2** 순수함수 + 호스트(native) 단위 테스트 작성 — 완료 (단, **테스트 미실행**: 작성 환경에 컴파일러/PlatformIO 없었음)
3. ⬜ **Phase 3** `src/main.cpp` 핀 I/O 연결 + Wokwi 동작 확인 — **테스트 통과 확인 후 착수** (사용자 지시)
4. ⬜ **Phase 4** 실물 보드, 사람 평가

> **지금 당장 할 일: `pio test -e native` 실행해서 Phase 2 테스트 통과 확인.** 통과하면 Phase 3 진행, 실패하면 출력 보고 코어 수정.

## 4. 파일 구조 (이미 작성됨)
```
platformio.ini            env:native(테스트) / env:uno(Phase 3)
lib/core/
  input_debounce.{h,cpp}  Debouncer: raw+now_ms → 안정상태/에지 (순수)
  friction_policy.{h,cpp} computeImpulsivity(history), computeRequiredDwell(stake,impulsivity,cfg)
  state_machine.{h,cpp}   StateMachine.step(button,stake,now_ms)→StepResult
  logger.{h,cpp}          csvHeader(), formatCsv(LogRow) (Serial 비의존)
test/
  test_friction_policy/   9 cases
  test_state_machine/     5 cases
  test_input_debounce/    3 cases
  test_logger/            3 cases
README.md, CLAUDE.md, .gitignore
(src/ 는 아직 없음 — Phase 3에서 생성)
```

## 5. 상태기 사양 (구현된 규칙)
- 상태: `IDLE / ARMED / DWELLING / COMMITTED / ABORTED / COOLDOWN`
- `IDLE --누름에지--> ARMED`: 이 시점에 FrictionPolicy로 required dwell 산정(stake·impulsivity 기준). dwell 카운트 시작점 = 누름 시각.
- `ARMED`: `arm_grace_ms`(기본 120ms) 전에 떼면 **mis-tap → IDLE**(기록 없음). 넘으면 `DWELLING`.
- `DWELLING`: 누른 채 `actual >= required` → **COMMITTED**(LED 완전 점등). required 전에 떼면 → **ABORTED**(LED 소등). progress=actual/required.
- `COMMITTED/ABORTED`: 한 틱 표시 후 → `COOLDOWN`.
- `COOLDOWN`: `cooldown_ms`(기본 1500ms) lockout. 끝나면 IDLE, 단 **새 누름 에지** 필요(계속 누르고 있으면 재-ARM 안 됨).
- 기본 설정값: FrictionConfig{base 800, max 6000, stake_gain 2000, impulsivity_gain 3000} ms / SmConfig{arm_grace 120, cooldown 1500} ms.
- impulsivity: 이력 중 ABORTED 가 required 대비 일찍 떼였을수록 1에 가깝게(끝까지 기다린 COMMITTED는 0 기여). required는 impulsivity·stake 가 클수록 증가, max 클램프.
- 출력 매핑(Phase 3): LED — DWELLING=progress 비례 점진, COMMITTED=완전 점등, ABORTED/그외=소등. 진동모터는 **선택적** 출력 모듈로만(로직 비의존).
- CSV: `timestamp_ms,event,required_dwell_ms,actual_dwell_ms,impulsivity,outcome`

## 6. 테스트 실행
```bash
cd "C:\Users\USER\Desktop\클로드코드 관련\friction-commit-device"
pio test -e native        # Wokwi 아닌 호스트. PlatformIO 없으면 pip install platformio (정식 Python 필요)
```
순수 함수 테스트는 호스트 C++ 컴파일러로, 핀 I/O 동작은 Wokwi 가상보드로, 실물보드는 후속 사람평가 단계에서만.

## 7. 작업 방식 규칙 (사용자 피드백 — 반드시 지킬 것)
- **확인 없이 임의로 만들지 말 것.** 스펙이 모호하면 핵심 질문을 먼저 구성해 묻고, 답변 기반으로 만든다.
- 사용자가 **명시한 빌드 순서/스펙을 그대로** 따른다.
- AskUserQuestion 호출 시 `questions` 파라미터를 반드시 채운다.

## 8. 스킬/환경 현황 (이어서 스킬 설치할 때 참고)
- **스킬의 메인 파일 = `SKILL.md`** (폴더 안 YAML frontmatter `name`+`description`+본문). 설치 = 그 폴더를 `~/.claude/skills/`(전역) 또는 `<프로젝트>/.claude/skills/`(프로젝트)에 둠.
- **스킬 배치 정책**: 재사용 공용 도구는 **전역**(`~/.claude/skills`, `~/.claude/commands`), 프로젝트 고유만 프로젝트에. **플러그인 스킬(`design:*`,`figma:*`,`anthropic-skills:*`)은 이미 전역 작동 → 파일로 복사 금지(중복본 방지).** 범용성 있으면 전역 선호.
- **전역 스킬(9)**: ui-ux-pro-max, frontend-design, impeccable, ux-heuristics, web-design-guidelines, design-taste-frontend, brainstorming, browser-use, vercel-react-best-practices
- **전역 커맨드**: `/hook` (디자인 포트폴리오 후킹 문구)
- **claude_test1(샌드박스) 잔여 프로젝트 스킬**: docx, find-skills, improve-codebase-architecture + accessibility-agents(커맨드 16/에이전트 80, 자동 훅 제외)
- **21st.dev Magic MCP**: Claude Desktop config(`%APPDATA%\Claude\claude_desktop_config.json`)에 등록됨 → `/ui` 사용. (API 키는 노출됐으므로 재발급 권장)
- 기타: `claude_test1\remotion-project`(Remotion blank, strict TS) 존재.

## 9. 환경 주의
- 직전 작업 환경엔 g++/clang/MSVC/PlatformIO 없음, `python`은 Windows Store 스텁. → 테스트는 사용자 머신에서 실행하거나 PlatformIO 설치 후 진행.
