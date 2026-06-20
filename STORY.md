# Friction as Feature — 프로젝트 서사 (Narrative & Rationale)

> 이 문서는 포트폴리오 works 아카이브 소개글과 인터뷰 답변의 *논리적 뼈대*다.
> 한국어 서사 + 인터뷰에 그대로 옮길 수 있는 영문 핵심 문장(▷)을 함께 둔다.
> 정직성 원칙: 이건 **엔지니어링·인터랙션 디자인 시연**이지 사용자 연구가 아니다. 과장 지표 없음.

---

## 0. 한 줄 정의

화면과 손, 두 매체로 구현한 **"마찰을 기능으로(Friction as Feature)"** 연구 — *AI가 우리를 대신해 행동하기 직전, 보정된 멈춤(calibrated pause)을 되돌려 넣는 장치.*

▷ *A tangible-and-screen study of friction as a feature: reintroducing a calibrated pause at the moment AI acts on our behalf.*

---

## 1. 어떻게 시작했나 (Origin)

학부 산업디자인 졸업연구에서 **아이들을 위한 행동 유도(behavior-guiding) 디자인**을 다루며 더 큰 질문이 생겼다: "사용자를 **막지 않으면서도** 멈춤의 순간을 만들 수 있을까?"

이 질문은 곧 **AI 시대의 문제**로 확장됐다. 최근 AI가 디지털 전반에 들어오며 사용자 경험은 그 어느 때보다 매끄러워졌지만, 동시에 **의존성이 커지면서 인간의 독자적·능동적 행위와 이성적·합리적 판단이 거의 불필요해지거나 어려워졌다.** 게다가 현재 AI의 판단·결정은 아직 인간의 사고를 온전히 뛰어넘지 못한다 — 그럼에도 우리는 점점 더 반사적으로 위임하고 승인한다.

이 문제는 한 분야에 그치지 않는다: **수면 시간, 학업, 돈 소비, 디지털 신뢰** 등 곳곳에서 같은 양상이 나타난다.

그래서 이 프로젝트는 **의도적인 마찰**을 끼워 넣어, 조금 더 *이성적·합리적인 판단*과 *건강한 신뢰 상호작용*을 일으키고, 궁극적으로 **인간의 독자적 판단을 증진해 더 나은 결과**를 기대하는 데 초점을 둔다.

이론적 근거:
- Laschke & Hassenzahl, *Pleasurable Troublemakers* / frictional feedback — "생산적 마찰"이 성찰을 돕는다.
- Riener, *trust calibration / automation overtrust* — 자동화에 대한 과신을 어떻게 보정할 것인가.

▷ *As AI smooths every digital experience, our dependency grows and our own reasoned judgment is exercised ever less — while AI's decisions still don't fully surpass human thinking. The same pattern surfaces across sleep, studying, spending, and digital trust. This project introduces intentional friction to restore more rational judgment and calibrated trust — strengthening human agency toward better outcomes.*

---

## 2. 컨셉: The Approval Gate

상황을 하나로 압축했다 — **AI 에이전트가 340명에게 메일을 보내기 직전, 사람이 '승인 게이트'가 된다.**

세 가지 조건을 같은 무대에서 비교한다:
- **A. 마찰 없음** — 원클릭, 즉시 실행
- **B. 화면 마찰** — "정말 보낼까요?" 확인
- **C. 물리 마찰** — 버튼을 *계속 눌러야* 통과

마찰은 정확히 **되돌릴 수 없는 확정(commit)의 순간**에 다시 끼워 넣는다.

---

## 3. 왜 아두이노(탠저블)인가

연구의 주장이 **물리적 마찰**에 관한 것이므로, 실제 *손으로 만지는 장치*로 구현해야 명제가 성립한다.

동시에 이건 THI(Informatik/Mensch-Technik Interaktion)에 대한 **구현 역량의 증거**다. 핵심은 "장치가 멋지다"가 아니라:

- 판단 로직(마찰 정책·상태기)을 **하드웨어 비의존 순수 함수**로 분리
- 그 로직을 **호스트 단위 테스트로 커버 → 통과(20/20)**
- Wokwi 가상 보드로 **누구나 재현 가능**

▷ *The headline evidence is not a gadget but testable, hardware-independent decision logic with a passing unit-test suite — proof I write code that can be verified.*

---

## 4. 왜 웹 인터페이스를 *따로 하나 더* 만들었나 (핵심 질문)

세 가지 이유로 갈린다:

**(1) 연구 설계가 요구한다.** 세 조건(없음/화면/물리)을 *통제된, 공유 가능한* 무대에서 비교해야 한다. 웹이 조건 A·B를 담고 비교의 틀을 제공하며, 아두이노가 조건 C(물리)를 담는다.

**(2) 하나의 개념, 두 가지 구현.** 같은 마찰 로직이 *화면에서도, 손에서도* 작동함을 보이면 — 이 아이디어가 특정 가젯에 묶이지 않고 매체를 가로질러 일반화됨을 증명한다. 의사결정 로직(`FrictionPolicy`/`StateMachine`)은 양쪽이 *공유*한다.

**(3) 청중이 다르다.** 웹 = 링크 가능한 *시각·UX 산출물*(Bamberg, 취업). 아두이노+테스트 = *엔지니어링 증거*(THI). **한 프로젝트, 두 가지 독법.**

▷ *Same concept, two embodiments. The screen version makes the idea shareable and legible; the tangible version proves it lives in the body. One decision logic underneath both.*

---

## 5. 왜 유체(fluid) 형태인가

핵심 행위는 정보의 **확산(spread)** 이다 — 한 번의 승인이 340명에게 *바깥으로 퍼지고*, 되돌릴 수 없다.

- **유체 = 확산의 자연스러운 은유.** 물결처럼 퍼지고, 한 번 쏟으면 주워 담을 수 없다(비가역성).
- **표면장력 = 확정 직전의 긴장.** 누르며 *조여지고 팽팽*해지다가, 완성되면 *터져 퍼진다.*
- **차분하고 인간적 — 벌이 아니다.** 물은 부드럽게 읽힌다. 이는 *"마찰은 장애물이 아니라 지원"* 이라는 명제, 즉 **자율성 보존**을 형태로 번역한 것.
- **링(torus) 형태**가 두 기능을 하나로 묶는다: 누르는 *어포던스*(반지)이자 퍼지는 *파동*.

▷ *Fluid is the metaphor for an irreversible spread; surface tension is the tension before commitment; water reads as care, not punishment — friction as support, not obstacle.*

---

## 6. 유체가 사용자와 *어떻게* 상호작용하며, 그 이유는

모든 인터랙션 디테일이 명제를 인코딩한다:

- **클릭이 아니라 누르고 머무르기.** 지속적인 신체적 노력 = 마찰 그 자체. 요구되는 시간(required dwell)은 **이해관계(수신자 수·외부·비가역성)** 와 **최근의 충동성(반사적 승인 연속)** 에 비례한다. 막 누를수록 장치가 *더 큰 마찰*을 요구한다 — **신뢰 보정(trust calibration)을 손으로 만지게** 한 것.
- **누르는 동안 결과가 3단계로 드러난다** (Reach → Recipients → No undo), 마지막 단계가 가장 길다. *대기 시간을 죽은 기다림이 아니라 성찰로* 전환.
- **안쪽 컬러 유체가 제자리에서 조여지며 얇아져 사라진다** — 확정이 "조여드는" 과정을 시각화. 바깥 물은 climax에서 *팽팽하게 매끈*해진다(긴장).
- **완성 시: 링이 팽창→2D 흔적으로 납작해지고, 행동이 퍼진다** — 컬러 물방울 + 화면 전체로 번지는 파동. *비가역적 확산*을 체감.
- **일찍 손을 떼면(abort): 유체가 잦아들고**, 인간적인 메시지("It's okay. Nothing went out." 외 6종 순환)가 *멈춤을 올바른 선택으로* 프레이밍. → **자율성 보존, 처벌 아님.**

▷ *Effort calibrated to consequence; waiting repurposed into seeing; release framed as care. Pausing is never punished — it is affirmed.*

---

## 7. 정직한 범위 (Honest Scope)

- 이것은 **방법·디자인 시연**이지 통계적 사용자 연구가 아니다.
- 충동성 추정·타이밍 상수는 *설계된 프로브(design probe)* 이지 검증된 심리척도가 아니다.
- 웹의 유체는 *실시간 근사*이지 물리 시뮬레이션이 아니다.

▷ *This is an engineering and interaction-design demonstration, not a user study. The heuristics are design probes, honestly scoped.*

---

## 8. 포트폴리오 포지셔닝

**Works 아카이브 배치**
1. 먼저 **웹 경험**(인터랙티브·링크 가능)으로 끌어들이고
2. 그 아래 **엔지니어링**(repo·통과 테스트·Wokwi)을 *같은 연구 질문의 두 구현*으로 제시.

**인터뷰 Q&A (요약 답변)**
- *어떻게 시작?* — 학부 행동유도 연구 → "막지 않는 멈춤" 질문 → **AI 의존으로 인간의 독자적·이성적 판단이 약해지는 문제**(수면·학업·소비·디지털 신뢰 전반)로 확장 → 의도적 마찰로 합리적 판단·신뢰 보정·인간 주체성 증진.
- *왜 이 형태?* — 비가역적 확산을 다루므로 *유체 + 링*; 차분·인간적 톤으로 "지원으로서의 마찰".
- *왜 아두이노인데 웹도?* — 연구 설계(3조건)·하나의 개념 두 구현·청중 분리. 로직은 공유.
- *왜 유체?* — 확산·표면장력·비가역성·자율성의 은유.
- *유체가 어떻게/왜 상호작용?* — 노력=결과에 비례, 대기=성찰, 멈춤=긍정. trust calibration을 촉각화.

---

*다음 단계: 위 한국어 서사를 THI Pb4 a) 링크용 **영문 writeup 1페이지**로 폴리시 + Pb4 a) 750자 안에 넣을 2~3줄 영문 요약 추출.*
