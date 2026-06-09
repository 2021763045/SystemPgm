## 쉘 스크립트(Shell Script)

### 1. 개요

쉘 스크립트(Shell Script)는 Linux 쉘에서 실행되는 명령어들을 파일로 작성하여 자동으로 실행할 수 있도록 만든 프로그램이다. 반복적인 작업을 자동화하고 시스템 관리 업무를 효율적으로 수행할 수 있다.

---

### 2. 기본 구조

쉘 스크립트 파일은 보통 `.sh` 확장자를 사용한다.

예시

```bash
#!/bin/bash

echo "Hello World"
```

설명

* `#!/bin/bash` : 사용할 쉘 지정(Shebang)
* `echo` : 문자열 출력

실행 방법

```bash
chmod +x test.sh
./test.sh
```

---

### 3. 변수 사용

변수를 선언하여 데이터를 저장할 수 있다.

```bash
name="Hong"

echo $name
```

출력

```text
Hong
```

주의

* `=` 양쪽에 공백을 두지 않는다.
* 변수 사용 시 `$`를 붙인다.

---

### 4. 입력 받기

사용자로부터 입력을 받을 수 있다.

```bash
read name

echo "이름: $name"
```

---

### 5. 조건문

#### if 문

```bash
if [ $num -gt 10 ]
then
    echo "10보다 큼"
else
    echo "10 이하"
fi
```

비교 연산자

| 연산자   | 의미     |
| ----- | ------ |
| `-eq` | 같다     |
| `-ne` | 같지 않다  |
| `-gt` | 크다     |
| `-lt` | 작다     |
| `-ge` | 크거나 같다 |
| `-le` | 작거나 같다 |

---

### 6. 반복문

#### for 문

```bash
for i in 1 2 3 4 5
do
    echo $i
done
```

#### while 문

```bash
count=1

while [ $count -le 5 ]
do
    echo $count
    count=$((count+1))
done
```

---

### 7. 함수

반복되는 작업을 함수로 정의할 수 있다.

```bash
hello() {
    echo "Hello Linux"
}

hello
```

---

### 8. 주요 활용 분야

* 시스템 관리 자동화
* 파일 및 디렉터리 관리
* 서버 운영 작업 자동화
* 백업 스크립트 작성
* 프로그램 실행 및 배포 자동화

---

### 정리

| 기능       | 예시               |
| -------- | ---------------- |
| 출력       | `echo`           |
| 입력       | `read`           |
| 변수       | `name="Hong"`    |
| 조건문      | `if ~ then ~ fi` |
| 반복문      | `for`, `while`   |
| 함수       | `function()`     |
| 실행 권한 부여 | `chmod +x`       |
