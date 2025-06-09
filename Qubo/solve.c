#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NUMBER_OF_QUESTION 256

#include "load.h"
#include "struct.h"
#include "solve.h"

#include <time.h>

// 공백 제거 함수
void removeSpace(char* str) {
    int i, j = 0;
    char temp[256];
    for (i = 0; str[i]; i++) {
        if (str[i] != ' ') {
            temp[j++] = str[i];
        }
    }
    temp[j] = '\0';
    strcpy_s(str,sizeof(temp), temp);
}

// 문제 출제 함수
void solve_remember() {
    system("cls");
    SUBJECT* subject = &qubo.subject[qubo.select.subject];
    CHAPTER* chapter = &subject->chapter[qubo.select.chapter];
    int total = chapter->questionNumber;
    int correct = 0;

    srand((unsigned int)time(NULL)); // 랜덤 시드 설정

    // 문제 인덱스를 랜덤으로 섞기
    int index[MAX_NUMBER_OF_QUESTION];
    for (int i = 0; i < total; i++) index[i] = i;
    for (int i = 0; i < total; i++) {
        int j = rand() % total;
        int temp = index[i];
        index[i] = index[j];
        index[j] = temp;
    }

    for (int i = 0; i < total; i++) {
        printf("\n[문제 %d / %d]\n", i + 1, total);

        QUESTION* q = &chapter->question[index[i]];

        // 단답형 문제
        if (q->isQm != 7) {
            printf("%s\n", q->qs.question);
            char input[256];
            printf("정답 입력: ");
            scanf_s(" %[^\n]", input, (unsigned int)sizeof(input));
            //fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            removeSpace(input);
            char answer[256];
            strcpy_s(answer,sizeof(q->qs.answer), q->qs.answer);
            removeSpace(answer);

            system("cls");
            if (strcmp(input, answer) == 0) {
                printf("정답입니다!\n");
                correct++;
            }
            else {
                printf("오답입니다. 정답: %s\n", q->qs.answer);
            }
        }

        // 객관식 문제
        if (q->isQm == 7) {
            printf("%s\n", q->qm.question);

            // 랜덤 순서로 선택지 섞기
            int count = q->qm.choiceNumber;
            int order[MAX_NUMBER_OF_QUESTION];
            for (int j = 0; j < count; j++) order[j] = j;
            for (int j = 0; j < count; j++) {
                int k = rand() % count;
                int temp = order[j];
                order[j] = order[k];
                order[k] = temp;
            }

            int answerIndex = -1;
            for (int j = 0; j < count; j++) {
                printf("%d. %s\n", j + 1, q->qm.choices[order[j]]);
                if (order[j] == q->qm.answer) {
                    answerIndex = j + 1;
                }
            }

            int input;
            printf("정답 선택 (번호): ");
            scanf_s("%d", &input);
            while (getchar() != '\n'); // 버퍼 비우기

            system("cls");
            if (input == answerIndex) {
                printf("정답입니다!\n");
                correct++;
            }
            else {
                printf("오답입니다. 정답: %d. %s\n", answerIndex, q->qm.choices[q->qm.answer]);
            }
        }
    }

    printf("\n전체 결과: %d / %d 정답\n", correct, total);
}

// 문제 출제 함수
void solve() {
    system("cls");
    SUBJECT* subject = &qubo.subject[qubo.select.subject];
    CHAPTER* chapter = &subject->chapter[qubo.select.chapter];
    int total = chapter->questionNumber;
    int correct = 0;

    srand((unsigned int)time(NULL)); // 랜덤 시드 설정

    // 문제 인덱스를 랜덤으로 섞기
    int index[MAX_NUMBER_OF_QUESTION];
    for (int i = 0; i < total; i++) index[i] = i;
    for (int i = 0; i < total; i++) {
        int j = rand() % total;
        int temp = index[i];
        index[i] = index[j];
        index[j] = temp;
    }

    for (int i = 0; i < total; i++) {
        printf("\n[문제 %d / %d]\n", i + 1, total);

        QUESTION* q = &chapter->question[index[i]];

        // 단답형 문제
        if (q->isQm != 7) {
            printf("%s\n정답 : %s\n", q->qs.question,q->qs.answer);
            char input[256];
            printf("정답 입력: ");
            scanf_s(" %[^\n]", input, (unsigned int)sizeof(input));
            //fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            removeSpace(input);
            char answer[256];
            strcpy_s(answer, sizeof(q->qs.answer), q->qs.answer);
            removeSpace(answer);

            system("cls");
            if (strcmp(input, answer) == 0) {
                printf("정답입니다!\n");
                correct++;
            }
            else {
                printf("오답입니다. 정답: %s\n", q->qs.answer);
            }
        }

        // 객관식 문제
        else {

            // 랜덤 순서로 선택지 섞기
            int count = q->qm.choiceNumber; 
            int* order = malloc(count * sizeof(int));
            if (order == NULL) {
                printf("메모리 할당 실패\n");
                exit(1);
            }
            for (int j = 0; j < count; j++) order[j] = j;
            for (int j = 0; j < count; j++) {
                int k = rand() % count;
                int temp = order[j];
                order[j] = order[k];
                order[k] = temp;
            }

            int answerIndex = -1;
            for (int j = 0; j < count; j++) {
                printf("%d. %s\n", j + 1, q->qm.choices[order[j]]);
                if (order[j] == q->qm.answer) {
                    answerIndex = j + 1;
                }
            }
            printf("\n%s\n정답: %d\n", q->qm.question, answerIndex);

            int input;
            printf("정답 선택 (번호): ");
            scanf_s("%d", &input);
            while (getchar() != '\n'); // 버퍼 비우기

            system("cls");
            if (input == answerIndex) {
                printf("정답입니다!\n");
                correct++;
            }
            else {
                printf("오답입니다. 정답: %d. %s\n", answerIndex, q->qm.choices[q->qm.answer]);
            }
        }
    }

    printf("\n전체 결과: %d / %d 정답\n", correct, total);
}