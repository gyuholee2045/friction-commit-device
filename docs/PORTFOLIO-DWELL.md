# DWELL — Web Portfolio Case Study (Framer) · Structure & Content Brief

> 이 문서 = **구조 + 섹션별 내용 브리프 + 톤 가이드.** 영문 최종 카피는 이걸 잠근 뒤 섹션별로 작성.
> 목표: 평범한 결과 소개 ❌ → **디자인 결정·과정 + 강력한 스토리텔링**으로 *사로잡는 스크롤 경험*.

---

## 0. 기본
- **프로젝트명:** `DWELL` (머무는 시간 = required dwell. 짧고 개성 있고 연구 용어와 직결.)
- **톤 레퍼런스:** Toss(편안·명료·흥미 유지) + toan.framer.website/anz(개성 있는 문구).
- **언어:** 영문.

### Hero hook (썸네일 클릭 후 첫 한 문구 — 후보)
1. *"Some things shouldn't be one tap away."*
2. *"I taught a button to make you wait."*
3. *"Friction, on purpose."*
4. *"What if 'send' asked you to stay a second?"*

### Intro (프로젝트명 우측, 핵심 1–2문장 — 후보)
- *"DWELL is a study in deliberate friction: a control that asks you to stay a moment before an AI acts for you. One idea, built twice, on screen and in hardware."*

---

## 톤 원칙 (모든 카피에 적용)
- **짧고 따뜻하고 자신 있게.** 한 스크롤 비트 = 한 생각. 시각이 말하게 둔다.
- **판단을 보여준다:** "I chose X because Y" > 기능 나열.
- **금지:** AI 상투어(seamless, elevate, delve, game-changer, unlock, "in today's world"), 방어적 헤징, 주니어식 과잉설명.
- **리드한다:** 독자를 다음 줄로 끌고 간다. 질문 → 전환 → 보상.
- **정직 = 신뢰:** 과정·시행착오·범위를 솔직히. (가장 강한 차별점.)

---

## 스크롤 아키텍처 (10 섹션)

### 0 · HERO
- **목적:** 스크롤 정지. 톤 세팅. 한 줄 약속.
- **내용:** 프로젝트명 `DWELL`(좌) + hook 한 문구 + intro(우).
- **미디어:** 살아있는 유체 루프(index.html 임베드 또는 영상). 배경에서 잔잔히 일렁임.
- **voice 샘플:** (hook 후보 중 택1)

### 1 · THE TENSION — *"We stopped deciding."*
- **목적:** 문제의 *날카로운* 제기 (왜 이게 존재하나).
- **내용:** AI가 디지털을 매끄럽게 만들수록 의존↑·독자적 이성 판단↓. 수면·소비·학업·디지털 신뢰 전반. AI 판단은 아직 인간을 못 넘는데 우린 반사적으로 위임.
- **미디어:** 타이포 모션 한 방 / 미니멀.
- **voice 샘플:** *"AI makes every choice easier to skip. So we skip them."*

### 2 · FRICTION AS FEATURE — *"What if resistance was the point?"*
- **목적:** 논지 뒤집기.
- **내용:** 마찰을 *장애물이 아니라 지원*으로. 결정 순간에 의도적 저항 → 성찰·trust calibration. HCI 연구의 '의도적 마찰' 계보 가볍게 1줄.
- **미디어:** 강한 단일 메타포 비주얼.

### 3 · THE APPROVAL GATE — *"One click. 340 people."*
- **목적:** 추상 → 구체 시나리오.
- **내용:** AI 에이전트가 340명에게 메일 보내기 직전, 사람이 승인 게이트. 비가역의 순간.
- **미디어:** 시나리오 셋업 비주얼 / 스택.

### 4 · THREE WAYS TO MEET IT — *"Three ways to meet the moment."*
- **목적:** 연구 *논증* (왜 C가 우월한가).
- **내용:** A 마찰없음(즉시) / B 화면마찰(클릭으로 지나침) / C 물리마찰(머물러야 함). 체감 대비.
- **미디어:** **compare.html 인터랙티브 임베드** 또는 3조건 GIF 나란히.

### 5 · THE HELD MOMENT — *"Hold, and it's yours again."* (핵심)
- **목적:** 핵심 인터랙션 + **디자인 결정** 심화.
- **내용:** 유체 링·홀드. **적응형 dwell**(충동적일수록 요구 시간↑ = trust calibration을 손으로). 대기 시간을 *성찰*로 전환(누르는 동안 결과가 드러남). 왜 유체/왜 링/왜 이 모션인지 결정 근거.
- **미디어:** 인터랙션 GIF + **CSV 데이터(impulsivity 따라 required 치솟는 escalation)**.
- **voice 샘플:** *"Rush it, and the device makes you wait longer. Pause, and it eases. The friction reads you."*

### 6 · TWO EMBODIMENTS — *"The same idea, in two bodies."*
- **목적:** 웹↔하드웨어 = *개념의 일반화* + 엔지니어링 신뢰.
- **내용:** 같은 마찰 로직이 화면(감정)과 하드웨어(증명)로. 보드 비의존 순수 코어 + **20/20 unit test** + Wokwi 재현 + CSV 로깅. *"애니메이션이 아니라 작동·검증되는 시스템."*
- **미디어:** Wokwi 클립 + 코드/테스트 스니펫 + CSV. (실물 영상은 후속 시 교체/추가.)
- **정직:** 방법·엔지니어링 시연이지 사용자 연구 아님 (명시).

### 7 · THE MAKING — *"Six versions deep."*
- **목적:** 과정·시행착오 = *진정성·감각·판단*. (최강 차별점.)
- **내용:** 유체 R&D 여정(2D→실패→3D 글래스→유체 볼→링 복귀), 막다른 길과 그때의 결정, "왜 버렸나/왜 돌아왔나". 표면 자기교차 버그 같은 솔직한 디테일.
- **미디어:** 이터레이션 샷·GIF 타임라인.

### 8 · REFLECTION / SCOPE — *"What it is, and isn't."*
- **목적:** 자신감 있되 겸손한 마무리.
- **내용:** 무엇을 증명했고(방법·구현), 무엇이 아닌지(검증된 사용자연구 아님). 휴리스틱·상수는 design-probe. 다음 단계(실물 평가).
- **미디어:** 차분한 타이포.

### 9 · OUTRO
- **내용:** 리캡 한 줄 + 라이브 데모·repo 링크 + 크레딧.
- **voice 샘플:** *"Stay a second. It's the whole idea."*

---

## 다음 단계
1. 위 구조·후보 문구에서 hook/intro/타이틀 **택1 + 미세 수정.**
2. 섹션별 **영문 본문 카피** 작성 (Toss/toan 톤, 한 섹션씩 — 톤 확인하며).
3. 각 섹션 **미디어 소스 목록**(어떤 GIF/영상/임베드) 확정 → Framer 제작.

---

## 최종 카피 (EN + KR) — 폴리시본 · em-dash·AI상투어 없음 · 강조와 생략(섹션별 길이·톤 차등)

> 리듬 메모(중요): 전부 후킹·단문이면 역으로 피로하다. **압축 ↔ 서술 교차**로 호흡을 만든다. Hero·Outro=압축 / Tension·Friction=후킹+차분한 본문 / Gate=장면 서술 / Three ways=대비 리스트 / The held moment·The making=길게(판단·과정 서술로 호흡 유지) / Reflection=짧고 정직. 긴 단락엔 굵은 스캔 앵커 한 줄로 눈쉼터. 압축할 때 핵심 의미가 묻히지 않는지 섹션마다 점검.

### 0 · HERO  ‹압축›
**EN** — DWELL / **I taught a button to make you wait.**
> Before an AI sends, buys, or commits for you, one second of resistance.
> I built it twice. One you feel on a screen, one that runs as tested hardware.

**KR** — DWELL / **버튼에게, 당신을 기다리게 하는 법을 가르쳤다.**
> AI가 당신 대신 보내고 사고 확정하기 전에, 1초의 저항.
> 두 번 만들었다. 하나는 화면에서 느끼는 것, 하나는 테스트를 통과한 하드웨어로 도는 것.

**미디어:** 풀스크린 유체 루프(index.html 임베드 또는 4~6초 무한 루프 영상, 무음). 이름·후킹은 좌, 인트로는 우.

### 1 · THE TENSION — "We stopped deciding." / "우리는 결정하기를 멈췄다."  ‹중간›
**EN**
> AI made every choice easy to skip, so we skip them. It drafts the email, fills the form, picks the plan, and most of the time we just wave it through.
> The screen keeps getting smoother while our judgment gets less practice. Quietly, that adds up. The machine still isn't better than us where it counts, and yet we've stopped showing up for the decision.
> By now it touches almost everything. What we buy, when we sleep, who we trust.

**KR**
> AI는 모든 선택을 건너뛰기 쉽게 만들었고, 그래서 우리는 건너뛴다. 메일 초안을 쓰고 양식을 채우고 플랜을 골라주면, 대개는 그냥 통과시켜 버린다.
> 화면이 매끄러워지는 동안 판단력은 점점 덜 쓰인다. 조용히, 그게 쌓인다. 정작 중요한 곳에서 기계는 아직 우리보다 낫지 않은데, 우리는 결정의 자리에 나타나기를 그만뒀다.
> 이제 그건 거의 모든 일에 닿아 있다. 무엇을 사는지, 언제 자는지, 누구를 믿는지까지.

**미디어:** 미니멀 키네틱 타이포 한 컷(한 문장이 천천히 드러남), 또는 무마찰 원클릭 UI들이 흐려지며 지나가는 배경.

### 2 · FRICTION AS FEATURE — "What if resistance was the point?" / "저항이 핵심이라면?"  ‹중간·개념›
**EN**
> Most design spends its energy removing friction. Fewer steps, fewer clicks, nothing left between you and done.
> **DWELL goes the other way, on purpose.** It places a small, deliberate resistance exactly where a real choice should happen. Not a wall that stops you, but a pause you can feel: long enough to think, short enough to trust you with the rest.
> The idea has roots in HCI research on deliberate friction and automation overtrust. Handled with care, friction gives judgment its moment back.

**KR**
> 대부분의 디자인은 마찰을 없애는 데 힘을 쏟는다. 더 적은 단계, 더 적은 클릭, 당신과 '완료' 사이에 아무것도 남기지 않기.
> **DWELL은 일부러 반대로 간다.** 진짜 선택이 일어나야 할 바로 그 지점에 작고 의도된 저항을 놓는다. 멈춰 세우는 벽이 아니라, 느낄 수 있는 멈춤. 생각하기엔 충분히 길고, 나머지는 당신에게 맡길 만큼 짧게.
> 이 발상에는 뿌리가 있다. 의도적 마찰과 자동화 과신을 다루는 HCI 연구들이 같은 곳에 닿는다. 조심스럽게 다루면, 마찰은 판단에게 그 순간을 되돌려준다.

**미디어:** 단일 강한 메타포 비주얼(손가락이 유체 표면에 닿아 잠시 버티는 클로즈업), 정지 + 미세 모션.

### 3 · THE APPROVAL GATE — "One click. 340 people." / "클릭 한 번. 340명."  ‹씬›
**EN**
> Picture the moment. An AI agent is ready to email 340 people for you. Twelve of them sit outside the company, three are executives, and none of it can be pulled back. The send button glows, helpful as ever.
> DWELL lives in the half second before that glow turns into action, while the choice is still yours to make.

**KR**
> 그 순간을 그려보자. AI 에이전트가 당신 대신 340명에게 메일을 보낼 준비를 마쳤다. 그중 열둘은 회사 밖 사람이고, 셋은 임원이며, 어느 것도 되돌릴 수 없다. 전송 버튼은 여느 때처럼 친절하게 빛난다.
> DWELL은 그 빛이 행동이 되기 직전의 반 초, 선택이 아직 당신 몫인 그 순간에 산다.

**미디어:** 시나리오 셋업 — 에이전트 카드 + 340/외부12/임원3 칩 스택(compare.html 상단 캡처), 또는 짧은 셋업 영상.

### 4 · THREE WAYS TO MEET IT — "Three ways to meet the moment." / "그 순간을 마주하는 세 가지 방법."  ‹구조›
**EN**
> Same decision, three responses. I built all three so the difference is something you feel, not something you take on my word.
> **No friction.** One tap, already gone. The default we all know.
> **Screen friction.** A dialog asks if you're sure, and most people click straight past it. A safeguard that rarely does its job.
> **Tangible friction.** You have to stay with it. Hold, and the moment comes back to you.
> Resistance you can sense is resistance you can't autopilot through.

**KR**
> 같은 결정, 세 가지 반응. 차이를 내 말로 믿는 게 아니라 직접 느끼도록 셋 다 만들었다.
> **마찰 없음.** 한 번 탭하면 이미 끝. 우리 모두 아는 기본값.
> **화면 마찰.** 정말 하시겠냐고 팝업이 묻지만, 사람들은 대개 그대로 지나쳐 누른다. 좀처럼 제 일을 못 하는 안전장치.
> **물리 마찰.** 그 순간에 머물러야 한다. 누르고 있으면, 그 순간이 다시 당신에게 돌아온다.
> 감각되는 저항은 자동조종으로 지나칠 수 없다.

**미디어:** compare.html 인터랙티브 임베드(가능하면) 또는 A/B/C 3분할 GIF 나란히(각 5~7초).

### 5 · THE HELD MOMENT — "Hold, and it's yours again." / "누르면, 다시 당신 것이 된다."  ‹길게·핵심›
**EN**
> Holding is the entire interaction. The part worth explaining sits underneath it.
> **The hold reads you.** Tap fast and commit on reflex, and the device asks for a longer hold. Slow down, and it relaxes. The more impulsively you act, the more it pushes back, in proportion. The friction is tuned to the person in front of it, not to a fixed rule, and that small idea is the research question made tangible.
> The waiting is never empty. As you hold, the cost surfaces: who this reaches, what can't be undone. The pause becomes the place where reflection actually happens, instead of a warning you scroll past.
> The form was a decision too, not decoration. A message to 340 people spreads, and what spreads can't be gathered back. I wanted something that behaved like a fluid you set in motion, so that committing would feel less like pressing a button and more like releasing a tide.

**KR**
> 누르고 있는 것이 인터랙션의 전부다. 설명할 가치가 있는 건 그 아래에 있다.
> **홀드가 당신을 읽는다.** 빠르게 탭하고 반사적으로 확정하면 더 긴 홀드를 요구하고, 속도를 늦추면 누그러진다. 충동적으로 굴수록 그만큼 비례해 밀어낸다. 마찰이 정해진 규칙이 아니라 앞에 있는 사람에게 맞춰진다는 것, 그 작은 발상이 곧 이 연구 질문을 손에 잡히게 만든다.
> 기다림은 결코 비어 있지 않다. 누르는 동안 대가가 떠오른다. 이게 누구에게 닿는지, 무엇을 되돌릴 수 없는지. 그 멈춤은 스크롤해 지나치는 경고가 아니라, 성찰이 실제로 일어나는 자리가 된다.
> 형태 역시 결정이었지 장식이 아니었다. 340명에게 가는 메시지는 퍼지고, 퍼진 것은 다시 거둘 수 없다. 나는 당신이 움직이게 만든 유체처럼 거동하는 무언가를 원했다. 그래서 확정한다는 행위가, 버튼을 누르는 것보다 밀물을 놓아주는 것에 가깝게 느껴지도록.

**미디어:** 핵심 인터랙션 GIF(홀드 → 단계 채움 → 확산) + 적응형 escalation 데이터(연타 시 required 800 → 4372ms로 치솟는 CSV 표/클립). 나란히 배치해 "느낌 + 증거" 동시에.

### 6 · TWO EMBODIMENTS — "The same idea, in two bodies." / "같은 생각, 두 개의 몸."  ‹중간·신뢰›
**EN**
> On a screen, DWELL is something you feel. In hardware, it's something I can prove.
> The decision logic is written to stand on its own, apart from any screen or chip. It runs on a laptop and on a virtual Arduino board, and it passes a full suite of unit tests. So when I say the friction adapts to your impulsivity, that claim isn't a rendered animation; it's a system you can rerun and check.
> Every attempt it handles becomes one row of data: timestamp, required hold, actual hold, impulsivity, outcome. Behavior turns into something legible.
> One honest note on scope. This is an engineering and design demonstration, not a validated user study, and I would rather say that plainly than dress it up.

**KR**
> 화면에서 DWELL은 느끼는 것이다. 하드웨어에서는 내가 증명할 수 있는 것이다.
> 판단 로직은 화면이나 칩과 무관하게 홀로 설 수 있도록 쓰였다. 노트북에서도, 가상 아두이노 보드에서도 돌고, 단위 테스트 전부를 통과한다. 그래서 마찰이 당신의 충동성에 적응한다고 말할 때, 그 주장은 렌더링된 애니메이션이 아니라 다시 돌려보고 확인할 수 있는 시스템이다.
> 장치가 처리하는 모든 시도는 한 줄의 데이터가 된다. 타임스탬프, 요구된 홀드, 실제 홀드, 충동성, 결과. 행동이 읽을 수 있는 것으로 바뀐다.
> 범위에 대한 정직한 한마디. 이건 엔지니어링·디자인 시연이지 검증된 사용자 연구가 아니다. 그 점은 포장하기보다 그대로 말하고 싶다.

**미디어:** Wokwi 동작 클립(버튼 → LED → Serial CSV) + 통과 테스트 출력(20/20) + 코어 코드 일부. 3분할 또는 순차 등장. (실물 영상은 후속 시 추가.)

### 7 · THE MAKING — "Six versions deep." / "여섯 번째 버전."  ‹길게·과정›
**EN**
> None of this arrived in a straight line.
> The first fluid was flat, an illustration of water rather than water, so I scrapped it. The next attempt was real 3D glass that came out looking like chrome, then like frosted silicone, then it tore through its own surface once the ripples grew too strong. Every failure was specific, and every one taught me what the material was really doing.
> I went all the way out to a free-floating blob, fell for the look, then walked it back to a ring. The ring had to earn that, and it did: it carries both the press and the spread in a single shape.
> I'm showing the misses on purpose. The version that works only exists because the ones that didn't came first.

**KR**
> 이 중 어느 것도 직선으로 오지 않았다.
> 첫 유체는 평평했다. 물이 아니라 물 일러스트에 가까워서 버렸다. 다음 시도는 진짜 3D 글래스였는데 크롬처럼 나왔고, 다음엔 프로스트된 실리콘처럼, 그다음엔 주름이 너무 세지자 제 표면을 뚫고 나왔다. 실패는 매번 구체적이었고, 그때마다 그 재질이 실제로 무엇을 하는지 가르쳐 줬다.
> 자유롭게 떠다니는 덩어리까지 갔다가 그 룩에 반했지만, 결국 링으로 되돌렸다. 링은 그 자리를 얻어내야 했고, 얻어냈다. 누름과 확산을 한 형태에 담아내니까.
> 실패들을 일부러 보여준다. 작동하는 버전은, 작동하지 않은 버전들이 먼저 있었기에 존재한다.

**미디어:** 이터레이션 타임라인 스트립(2D → 3D 크롬 → 실리콘 → 자기교차 버그 → 블롭 → 링) 썸네일/GIF, 각 한 줄 캡션.

### 8 · REFLECTION / SCOPE — "What it is, and what it isn't." / "무엇이고, 무엇이 아닌가."  ‹짧고 정직›
**EN**
> DWELL is a working argument: that friction can be designed, tuned to a person, built to be tested, and felt in two materials at once.
> What it isn't is a validated study. The impulsivity model and the timings are design probes, chosen to make the idea legible rather than to prove a figure. I'd rather be precise about that than oversell it.
> The next step takes it out of the simulator and into your hand. The firmware is already waiting for the board.

**KR**
> DWELL은 작동하는 주장이다. 마찰이 설계될 수 있고, 사람에 맞춰 조율될 수 있고, 테스트되도록 만들어질 수 있고, 두 재질에서 동시에 느껴질 수 있다는 주장.
> 아닌 것은 검증된 연구다. 충동성 모델과 타이밍은 design probe다. 수치를 증명하려는 게 아니라 아이디어를 읽히게 하려고 고른 것이고, 그 점은 부풀리기보다 정확히 말하고 싶다.
> 다음 단계는 이것을 시뮬레이터 밖, 당신의 손으로 옮긴다. 펌웨어는 이미 보드를 기다리고 있다.

**미디어:** 차분한 타이포(배경에 유체가 거의 멈춘 듯 미세하게 일렁임).

### 9 · OUTRO — "Stay a second." / "잠깐만 머물러요."  ‹압축›
**EN**
> That's the whole idea.
> [Live demo] · [Code]
> DWELL. Designed and built by Gyuho Lee.

**KR**
> 그게 전부다.
> [라이브 데모] · [코드]
> DWELL. 이규호 디자인·제작.

**미디어:** 유체가 마지막으로 한 번 잔잔히 확산한 뒤 멈추는 루프 + 링크 버튼.
