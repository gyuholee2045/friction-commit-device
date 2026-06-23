# dwell-scrub — 스크롤 스크럽용 이미지 시퀀스

`frame_0000.webp` … `frame_0089.webp` (90프레임, 배경 #04040A 베이크드).
idle 유체 일렁임(frame 0) → 완성된 ring(frame 89)으로의 단일 연속 모핑.

## 생성 방법
1. `web/sequence/render-dwell-scrub.html` 를 **GPU 브라우저(Chrome)** 로 연다.
   (로컬 서버로 열어야 three.js CDN/캡처가 정상: `localhost:3000/sequence/render-dwell-scrub.html`)
2. 미리보기 슬라이더로 morph 0→1 확인 → 마음에 들면 **Render & Download ZIP**.
3. 받은 `dwell-scrub.zip` 을 풀어 이 폴더에 `frame_0000.webp` … 로 넣는다.

스펙: WebP / 배경 #04040A / 기본 1280px·q0.85 (해상도·품질·프레임수는 하니스 상단 컨트롤에서 조절, 총 용량 실시간 표시).
