# Linux-Shell-Project

## 목차
- [프로젝트 시작 계기](#프로젝트-시작-계기)
- [구현한 기능](#구현한-기능)
- [후에 추가하고 싶은 기능](#후에-추가하고-싶은-기능)
- [프로젝트. 그 이후](#프로젝트.-그-이후)

### 프로젝트 시작 계기
이 프로젝트는 __C언어 공부__ 라는 큰 틀 내에서, 이전 [C-Study](https://github.com/Master-C-Programming/C-Study)에서 각자 문서로만 공부했던 내용을 직접 코드로 써보기 위한 프로젝트다. 
- ##### 2학년 2학기에 수강한 `유닉스프로그래밍`의 내용과 스터디 내용을 연계하고 싶었다.
- ##### 코드로 작성해봐야 진정으로 아는 것이다.
- ##### 팀원들과의 협업을 통해 Git을 이해할 수 있다.

<hr>

### 구현한 기능
- 사용자의 현재 작업 디렉토리 표시
- 리다이렉션
- 파이프
- 백그라운드(단일 명령)

<hr>

### 후에 추가하고 싶은 기능
- ↑, ↓ 로 명령어 가져오기
- 완전한 백그라운드
- 사용자 등록 및 로그인
- --help 기능
- `tab`자동 완성

<hr>

### 프로젝트. 그 이후
기능들을 추가하다보니 리눅스 커널과 쉘의 동작 과정에 대해서 깊게 이해할 필요성을 느꼈다. 다음 목록들은 우리가 프로그램 구현 시 느꼈던 의문점이다.
- ##### 쉘은 이전 명령어들을 어디에 저장하는가? ↑, ↓ 를 이용하여 터미널에 이전 명령어들을 띄워주려면 사용자가 ↑, ↓ 를 입력할 때 쉘은 터미널에 `write()` 시스템 콜을 해야 하는가?
- ##### cd명령어로 디렉토리를 이동할 때, 명령어 입력 와중에도 쉘은 `tab` 자동 완성 기능을 제공한다. 쉘은 `/`을 기준으로 실시간으로 현재 디렉토리를 추적하는가?
- ##### 사용자 등록 및 로그인을 구현하기 위해서는 서버 구현이 필요할텐데, 리눅스 서버는 어떻게 구현되는가?

위에 더해 여러 의문점들을 느끼며 더 많은 기능 추가를 위해 먼저 리눅스 커널을 공부하기로 결정했다. 
