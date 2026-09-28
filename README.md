# DWELL · friction-commit-device

A commit button that asks you to hold before an action you can't undo, and asks for a longer hold when you've been confirming on reflex.

**Live demo:** https://dwelldemo.vercel.app  
**Three conditions (A · B · C):** https://dwelldemo.vercel.app/compare.html  
**Case study:** https://gyuholeee.com/dwell

## What's in this repo

| Path | What it is |
|---|---|
| `lib/core/` | The decision logic, separate from any board or screen: input debounce, friction policy, state machine, CSV logger |
| `test/` | 20 host unit tests for the core |
| `src/main.cpp` | Arduino Uno I/O adapter: button (D2), LED (D9, PWM), stake potentiometer (A0), serial CSV at 115200 |
| `wokwi.toml`, `diagram.json`, `wokwi/` | The same firmware on a virtual Arduino (Wokwi), with a headless smoke test |
| `web/` | The browser demos (three.js) |

## Run the tests

```bash
pio test -e native
```

Runs on a laptop, no board needed. Expected: `20 test cases: 20 succeeded`.

## How the hold is set

```
required hold = 0.8 s + stake × 2.0 s + impulsivity × 3.0 s   (clamped to 0.8–6.0 s)
```

Stake comes from the potentiometer (0–1). Impulsivity is estimated from recent holds: the earlier you let go, the higher it gets. Hold until the required time and it commits; let go early and nothing is sent.

Every attempt is logged as one CSV row:

```
timestamp_ms,event,required_dwell_ms,actual_dwell_ms,impulsivity,outcome
```

## Status

- [x] Decision logic and host tests (20 passing)
- [x] Firmware on a virtual Arduino (Wokwi), with serial CSV logging
- [x] 5-person pilot in the Wokwi simulation (a design probe, not a controlled study)
- [ ] Physical board and a proper study

Built in pairing with an AI coding assistant. The system design, the decision logic and what the tests had to prove are mine.

---

## 개발 메모 (한국어)

버튼 확정(commit)에 **계산된 시간 마찰(required dwell)** 을 부과하는 인터랙션 장치 펌웨어.
누르고 있는 시간이 정책이 산정한 dwell 을 넘겨야 확정되며, 일찍 떼면 무효(abort)다.
요구 dwell 은 **상호작용 이력(impulsivity)** 과 **stake(포텐셔미터)** 에 따라 달라진다.

### 진행 단계
- [x] **Phase 1** — 모듈 4개 분리 스캐폴드
- [x] **Phase 2** — 순수 함수 + 호스트 단위 테스트 (20개 통과)
- [x] **Phase 3** — `src/main.cpp` 핀 I/O 연결, Wokwi 동작 확인
- [ ] **Phase 4** — 실물 보드, 사람 평가

### 설계 메모
- **왜 순수 함수 분리?** 판단 로직(dwell·전이)을 하드웨어에서 떼어내야 노트북에서 빠르고 결정적으로 테스트할 수 있다. 하드웨어는 입력·출력만 담당.
- **시간 주입:** 코어는 `millis()` 를 호출하지 않고 `now_ms` 를 인자로 받는다 → 테스트에서 시간을 임의로 흘려보낼 수 있다.
- 자세한 상태 전이/출력 매핑은 [CLAUDE.md](CLAUDE.md) 참고.
