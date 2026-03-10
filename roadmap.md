# 🛠️ 추천 6개월 로드맵 (현실적인 버전)

목표:

**시스템 보안 기초 + 보안 도구 개발 감각**

---

# 🟢 1단계 (1~6주) — Stack Exploit 기초

목표:

**메모리 취약점이 어떻게 exploit되는지 이해**

배울 것

```
Stack layout
buffer overflow
NX
ASLR
Stack Canary
```

도구

- gdb + pwndbg
- pwntools
- checksec

추천 플랫폼

- Dreamhack
- pwnable.kr

목표

```
ROP chain으로 system("/bin/sh") 실행
```

이걸 한 번 성공하면

**exploit의 감각이 생깁니다.**

---

# 🟡 2단계 (7~10주) — ROP + Binary 분석

여기서 **Reverse Engineering**을 시작합니다.

도구

- Ghidra

배울 것

```
ELF 구조
PLT / GOT
ret2libc
ROP gadget
```

목표

```
소스 없는 바이너리 분석
→ 취약점 찾기
→ exploit 작성
```

---

# 🟠 3단계 (11~14주) — Heap + Fuzzing

Heap은 난이도가 올라가지만

**도구 개발과 굉장히 관련이 깊습니다.**

배울 것

```
glibc malloc
tcache
UAF
double free
```

그리고 **Fuzzing**

추천 도구

- AFL++

목표

```
프로그램 fuzzing
→ crash 발견
```

이 경험이 있으면

```
자동 취약점 탐지 도구
```

개발 감각이 생깁니다.

---

# 🔵 4단계 (15~18주) — Reverse Engineering 심화

도구

- Ghidra
- IDA Pro

연습

```
간단한 crackme 분석
```

배우는 것

```
assembly 읽기
control flow
함수 추적
```

---

# 🟣 5단계 (19~24주) — AI + 보안 실험

여기서 **AI를 도구로 활용하는 연습**을 합니다.

예시 프로젝트 3개

### 1️⃣ 취약점 후보 탐지

```
C 코드
→ LLM에게 취약점 후보 찾게 하기
```

예

```
buffer overflow
format string
use-after-free
```

---

### 2️⃣ crash 분석 도구

fuzzing 결과

```
crash log
+
stack trace
```

를

LLM에게 분석하게 하기

---

### 3️⃣ binary 설명 생성

```
assembly
→ pseudocode
→ 설명
```

이런 보안 도구를 만들어 보는 것입니다.

---

# 🎯 6개월 후 기대 상태

6개월 후에는 최소한 다음을 경험하게 됩니다.

```
exploit 작성
binary 분석
fuzzing
보안 자동화
AI 활용
```

이 상태면 다음 질문이 자연스럽게 생깁니다.

```
나는 공격이 재밌나?
연구가 재밌나?
도구 만드는 게 재밌나?
```

그때 방향을 정하면 됩니다.
