# web — Approval Gate 프로토타입 (두 버전, 개별 관리)

friction-commit-device의 **UX 트랙** 산출물. 두 버전을 따로 관리한다.

| 파일 | 정체 | 용도 |
|---|---|---|
| **index.html** | **C 단독 — 링 + 홀드** (핵심 히어로) | 집중형 시연. 유체 링을 꾹 눌러 단계 채움 → 확산. |
| **compare.html** | **A/B/C 3조건 비교** (상단 토글) | 연구 완결형. A 마찰없음(평범 버튼·즉시) / B 화면마찰(덩어리 블롭·마그네틱 호버·확인팝업) / C 물리마찰(링 홀드). |
| index-checkpoint-waterring.html | C 초기 승인본 백업 | 작업 꼬이면 복구용. |

## 여는 법
- 로컬 서버(권장): 프로젝트 루트에서 `.claude/launch.json`의 `web-prototype` 기동 → `http://localhost:3000/` (index) · `http://localhost:3000/compare.html`
- 또는 파일을 브라우저로 직접 열기 (file://). CDN(three.js) 로드를 위해 인터넷 필요.

## 기술
Three.js r165 (importmap, jsdelivr CDN) · MeshPhysicalMaterial transmission/iridescence · EffectComposer ripple 포스트프로세싱 · 정점 셰이더 wobble. 배경 밝은 아이보리블루.

## 메모
- 투과 유리 안의 내부 컬러 유체는 반드시 **불투명**이라야 비춰짐 (transparent면 안 보임) — 페이드는 scale로.
- 두 버전은 같은 3D 코어를 공유하되 인터랙션/폼만 다름. 한쪽 수정이 다른 쪽에 자동 반영되지 않음(별도 파일).
