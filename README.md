# friction-commit-device

버튼 확정(commit)에 **계산된 시간 마찰(required dwell)** 을 부과하는 인터랙션 장치 펌웨어.
누르고 있는 시간이 정책이 산정한 dwell 을 넘겨야 확정되며, 일찍 떼면 무효(abort)다.
요구 dwell 은 **상호작용 이력(impulsivity)** 과 **stake(포텐셔미터)** 에 따라 달라진다.

> 연구용 장치: 충동적 확정에 마찰을 주었을 때의 행동 변화를 관찰하고, 시리얼 CSV 로 데이터를 남긴다.

## 구조
```
friction-commit-device/
├─ platformio.ini          # env:native(테스트), env:uno(Phase 3)
├─ lib/core/               # 보드 비의존 순수 로직 (테스트 대상)
│  ├─ input_debounce.*     # 디바운서 (시간 주입)
│  ├─ friction_policy.*    # impulsivity / required dwell 계산
│  ├─ state_machine.*      # 상태기 (FrictionPolicy 사용)
│  └─ logger.*             # CSV 포맷터 (Serial 비의존)
├─ test/                   # 호스트(native) 단위 테스트
│  ├─ test_friction_policy/
│  ├─ test_state_machine/
│  ├─ test_input_debounce/
│  └─ test_logger/
└─ src/                    # (Phase 3) main.cpp — Arduino I/O 어댑터
```

## 진행 단계
- [x] **Phase 1** — 모듈 4개 분리 스캐폴드
- [x] **Phase 2** — 순수 함수 + 호스트 단위 테스트 작성 *(아래 명령으로 통과 확인 필요)*
- [ ] **Phase 3** — `src/main.cpp` 핀 I/O 연결 → **Wokwi** 동작 확인
- [ ] **Phase 4** — 실물 보드, 사람 평가

## 호스트 단위 테스트 실행 (Wokwi 아님)
PlatformIO 설치 후 프로젝트 폴더에서:
```bash
pio test -e native
```
> PlatformIO 가 없으면: `pip install platformio` (Python 필요) 또는 VS Code PlatformIO 확장.
> 순수 모듈만 별도로 g++ 로 빠르게 돌릴 수도 있다(헤더에 Arduino 의존이 없으므로).

## CSV 로그 형식
```
timestamp_ms,event,required_dwell_ms,actual_dwell_ms,impulsivity,outcome
```
예: `820,COMMITTED,800,812,0.000,COMMITTED`

## 설계 메모
- **왜 순수 함수 분리?** 판단 로직(dwell·전이)을 하드웨어에서 떼어내야 노트북에서 빠르고 결정적으로 테스트할 수 있다. 하드웨어는 입력·출력만 담당.
- **시간 주입:** 코어는 `millis()` 를 호출하지 않고 `now_ms` 를 인자로 받는다 → 테스트에서 시간을 임의로 흘려보낼 수 있다.
- 자세한 상태 전이/출력 매핑은 [CLAUDE.md](CLAUDE.md) 참고.
