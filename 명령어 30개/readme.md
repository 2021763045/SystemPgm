### 1. pwd (현재 작업 디렉터리 출력)

현재 프로세스의 작업 디렉터리 경로를 출력합니다.

```c
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd error");
        return 1;
    }
    return 0;
}

```

### 2. cd (디렉터리 이동)

지정된 경로로 현재 작업 디렉터리를 변경합니다.

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }
    if (chdir(argv[1]) != 0) {
        perror("cd error");
        return 1;
    }
    return 0;
}

```

### 3. ls (디렉터리 목록 표시)

지정된 디렉터리 내의 파일 및 디렉터리 이름을 목록으로 출력합니다.

```c
#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char *path = (argc > 1) ? argv[1] : ".";
    DIR *dir = opendir(path);
    if (!dir) {
        perror("ls error");
        return 1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}

```

### 4. cat (파일 내용 출력)

지정된 파일의 데이터를 출력합니다.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("cat error");
        return 1;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    return 0;
}

```

### 5. echo (문자열 출력)

문자열을 화면에 출력합니다.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s%s", argv[i], (i == argc - 1) ? "" : " ");
    }
    printf("\n");
    return 0;
}

```

### 6. mkdir (디렉터리 생성)

지정된 이름으로 새 디렉터리를 생성합니다.

```c
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <dirname>\n", argv[0]);
        return 1;
    }
    if (mkdir(argv[1], 0755) != 0) {
        perror("mkdir error");
        return 1;
    }
    return 0;
}

```

### 7. rmdir (빈 디렉터리 삭제)

비어 있는 디렉터리를 삭제합니다.

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <dirname>\n", argv[0]);
        return 1;
    }
    if (rmdir(argv[1]) != 0) {
        perror("rmdir error");
        return 1;
    }
    return 0;
}

```

### 8. touch (빈 파일 생성 또는 타임스탬프 수정)

파일이 존재하지 않으면 새로 생성하고, 존재하면 수정 시간을 현재로 갱신합니다.

```c
#include <stdio.h>
#include <utime.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("touch error (open)");
        return 1;
    }
    close(fd);
    if (utime(argv[1], NULL) != 0) {
        perror("touch error (utime)");
        return 1;
    }
    return 0;
}

```

### 9. rm (파일 삭제)

지정된 경로의 파일을 제거합니다.

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    if (unlink(argv[1]) != 0) {
        perror("rm error");
        return 1;
    }
    return 0;
}

```

### 10. cp (파일 복사)

원본 파일의 데이터를 읽어 새로운 대상 파일로 복사합니다.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        perror("cp error (source)");
        return 1;
    }
    FILE *dst = fopen(argv[2], "wb");
    if (!dst) {
        perror("cp error (destination)");
        fclose(src);
        return 1;
    }
    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dst);
    }
    fclose(src);
    fclose(dst);
    return 0;
}

```

### 11. mv (파일 이동 및 이름 변경)

파일의 경로를 바꾸거나 이름을 변경합니다.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    if (rename(argv[1], argv[2]) != 0) {
        perror("mv error");
        return 1;
    }
    return 0;
}

```

### 12. head (파일의 앞부분 출력)

파일의 처음 10줄을 출력합니다.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("head error");
        return 1;
    }
    char line[1024];
    int count = 0;
    while (count < 10 && fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        count++;
    }
    fclose(file);
    return 0;
}

```

### 13. tail (파일의 뒷부분 출력)

파일의 마지막 10줄을 출력합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("tail error");
        return 1;
    }
    char lines[10][1024];
    int count = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        strcpy(lines[count % 10], buffer);
        count++;
    }
    fclose(file);
    int start = (count > 10) ? (count % 10) : 0;
    int total = (count > 10) ? 10 : count;
    for (int i = 0; i < total; i++) {
        printf("%s", lines[(start + i) % 10]);
    }
    return 0;
}

```

### 14. wc (파일의 줄, 단어, 바이트 수 계산)

파일 내의 줄 바꿈 횟수, 단어 개수, 전체 바이트 크기를 측정합니다.

```c
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("wc error");
        return 1;
    }
    int lines = 0, words = 0, bytes = 0;
    int ch, in_word = 0;
    while ((ch = fgetc(file)) != EOF) {
        bytes++;
        if (ch == '\n') lines++;
        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    fclose(file);
    printf(" %d  %d %d %s\n", lines, words, bytes, argv[1]);
    return 0;
}

```

### 15. chmod (파일 권한 변경)

파일의 접근 권한을 수정합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <octal_mode> <filename>\n", argv[0]);
        return 1;
    }
    mode_t mode = strtol(argv[1], NULL, 8);
    if (chmod(argv[2], mode) != 0) {
        perror("chmod error");
        return 1;
    }
    return 0;
}

```

### 16. chown (파일 소유자 및 그룹 변경)

시스템 사용자와 그룹 ID를 통해 파일의 소유권을 변경합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <uid> <gid> <filename>\n", argv[0]);
        return 1;
    }
    uid_t uid = atoi(argv[1]);
    gid_t gid = atoi(argv[2]);
    if (chown(argv[3], uid, gid) != 0) {
        perror("chown error");
        return 1;
    }
    return 0;
}

```

### 17. clear (터미널 화면 초기화)

터미널 화면을 초기화합니다.

```c
#include <stdio.h>

int main() {
    if (printf("\033[H\033[2J") < 0) {
        return 1;
    }
    return 0;
}

```

### 18. whoami (현재 사용자 이름 출력)

현재 프로세스를 실행 중인 사용자의 이름을 출력합니다.

```c
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    if (!pw) {
        perror("whoami error");
        return 1;
    }
    printf("%s\n", pw->pw_name);
    return 0;
}

```

### 19. id (사용자 및 그룹 ID 정보 출력)

현재 사용자 ID, 그룹 ID 정보를 출력합니다.

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("uid=%d gid=%d\n", geteuid(), getegid());
    return 0;
}

```

### 20. sleep (지정한 시간 동안 대기)

입력된 초 단위 시간만큼 프로세스의 실행을 중단합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
        return 1;
    }
    unsigned int secs = atoi(argv[1]);
    sleep(secs);
    return 0;
}

```

### 21. date (현재 시간 출력)

시스템의 현재 날짜와 시간 정보를 출력합니다.

```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    if (!tm_info) {
        perror("date error");
        return 1;
    }
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Z %Y", tm_info);
    printf("%s\n", buffer);
    return 0;
}

```

### 22. uname (시스템 정보 출력)

운영체제의 이름을 확인하여 출력합니다.

```c
#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        perror("uname error");
        return 1;
    }
    printf("%s\n", buffer.sysname);
    return 0;
}

```

### 23. hostname (호스트 이름 출력)

현재 시스템의 호스트명을 출력합니다.

```c
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("hostname error");
        return 1;
    }
    printf("%s\n", hostname);
    return 0;
}

```

### 24. kill (프로세스 종료)

프로세스에 종료 시그널을 전송합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }
    pid_t pid = atoi(argv[1]);
    if (kill(pid, SIGTERM) != 0) {
        perror("kill error");
        return 1;
    }
    return 0;
}

```

### 25. uptime (시스템 가동 시간 정보 계산)

시스템이 부팅된 이후 경과된 총 시간을 계산하여 출력합니다.

```c
#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("uptime error");
        return 1;
    }
    long days = info.uptime / 86400;
    long hours = (info.uptime % 86400) / 3600;
    long minutes = (info.uptime % 3600) / 60;
    printf("up %ld days, %ld:%02ld\n", days, hours, minutes);
    return 0;
}

```

### 26. stat (파일 상태 상세 정보 표시)

파일의 크기, 블록 수, I/O 블록 크기 등의 상세 정보를 출력합니다.

```c
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        perror("stat error");
        return 1;
    }
    printf("File: %s\nSize: %lld\nBlocks: %lld\nIO Block: %d\n",
           argv[1], (long long)sb.st_size, (long long)sb.st_blocks, sb.st_blksize);
    return 0;
}

```

### 27. grep (문자열 검색)

파일에 특정 문자열이 포함되어 있는지 검사하고 출력합니다.

```c
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[2], "r");
    if (!file) {
        perror("grep error");
        return 1;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, argv[1]) != NULL) {
            printf("%s", line);
        }
    }
    fclose(file);
    return 0;
}

```

### 28. du (파일 또는 디렉터리의 디스크 사용량 확인)

지정된 파일이나 디렉터리가 차지하는 디스크 공간의 크기를 계산합니다.

```c
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename/dirname>\n", argv[0]);
        return 1;
    }
    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        perror("du error");
        return 1;
    }
    printf("%lld\t%s\n", (long long)sb.st_blocks / 2, argv[1]);
    return 0;
}

```

### 29. sort (파일 내용 정렬)

파일을 오름차순(사전순)으로 정렬하여 출력합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("sort error");
        return 1;
    }
    char **lines = NULL;
    char buffer[1024];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lines = realloc(lines, (count + 1) * sizeof(char *));
        lines[count] = strdup(buffer);
        count++;
    }
    fclose(file);
    qsort(lines, count, sizeof(char *), compare);
    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
    free(lines);
    return 0;
}

```

### 30. ps (실행 중인 프로세스 목록 확인)

실행 중인 프로세스 목록을 확인합니다.

```c
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>

int main() {
    DIR *dir = opendir("/proc");
    if (!dir) {
        perror("ps error");
        return 1;
    }
    struct dirent *entry;
    printf("  PID\n");
    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            printf("%5s\n", entry->d_name);
        }
    }
    closedir(dir);
    return 0;
}

```
