# 컴파일러와 옵션 설정
CC = gcc
CFLAGS = -Wall -g

# 소스 파일과 오브젝트 파일
SRC = A.c B.c main.c
OBJ = $(SRC:.c=.o)

# 최종 실행 파일
TARGET = main

# 기본 타겟
all: $(TARGET)

# 실행 파일 생성
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# .c -> .o 컴파일 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 청소 타겟
clean:
	rm -f $(OBJ) $(TARGET)

# 의존성 없이 .PHONY 지정
.PHONY: all clean
