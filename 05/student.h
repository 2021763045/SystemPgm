#ifndef STUDENT_H
#define STUDENT_H

#define NAME_SIZE 20
#define START_ID 1001001

struct student {
    int id;             // 학번
    char name[20]; // 이름
    int score;          // 점수
};

#endif