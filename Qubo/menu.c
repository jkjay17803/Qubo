#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "menu.h"
#include "struct.h"
#include "load.h"
#include "solve.h"

char restartBuffer;

void menu_main() {
	restart:
	system("cls");

	char test; // 종료 후 입력 확인용
	int select;
	printf("[ 메뉴 ]\n\n");
	printf("원하는 것을 선택해주세요.\n");
	printf("( 0: 종료 / 1: 외우기 모드 (답이 표시됩니다.) / 2: 실전 모드 (답이 표시되지 않습니다.) )\n");
	printf(":");
	scanf_s("%d", &select);
	

	switch (select) {
	case 0:
		printf("종료합니다.");
		exit(0);
		break;
	case 1:
		selectSubject();
		solve();
		printf("문제 풀이가 끝났습니다!\n아무 문자나 입력해서 돌아가세요.");
		scanf_s(" %c", &test, (unsigned int)sizeof(test));
		break;
	case 2:
		selectSubject();
		solve_remember();
		printf("문제 풀이가 끝났습니다!\n아무 문자나 입력해서 돌아가세요.");
		scanf_s(" %c", &test, (unsigned int)sizeof(test));
		break;
	default:
		restartBuffer = getchar();
		goto restart;
	}
}

void selectSubject() {
	system("cls");
	printf("[ 과목 선택 ]\n\n");
	printf("원하는 과목의 번호를 입력해주세요.\n");
	printf("( 0 입력 시. 돌아가기 )\n\n");
	for (int i = 0; i < qubo.subjectNumber; i++) {
		printf("[%d] - %s\n", i + 1, qubo.subject[i].subjectName);
	}
	scanf_s("%d", &qubo.select.subject);
	if (qubo.select.subject == 0) {
		menu_main();
		return;
	}
	qubo.select.subject -= 1;
	selectChapter();
}

void selectChapter() {
	system("cls");
	printf("[ 챕터 선택 ]\n\n");
	printf("' %s ' 과목이 선택되었습니다.\n\n", qubo.subject[qubo.select.subject].subjectName);
	printf("원하는 챕터의 번호를 입력해주세요.\n");
	printf("( 0 입력 시. 돌아가기 )\n\n");
	for (int i = 0; i < qubo.subject[qubo.select.subject].chapterNumber; i++) {
		printf("# %d %s\n", i + 1, qubo.subject[qubo.select.subject].chapter[i].chapterName);
	}
	scanf_s("%d", &qubo.select.chapter);
	if (qubo.select.chapter == 0) {
		selectSubject();
		return;
	}
	qubo.select.chapter -= 1;
	checkChapter();
}

void checkChapter() {
	SUBJECT* currentSubject = &qubo.subject[qubo.select.subject];
	CHAPTER* currentChapter = &currentSubject->chapter[qubo.select.chapter];
	
restart:
	system("cls");
	printf("[ 챕터 확인 ]\n\n");
	printf("' %s ' 챕터가 선택되었습니다.\n계속 진행할까요? (y/n)\n", currentChapter->chapterName);
	char yn;
	yn = getchar();
	if (yn == 'n' || yn == 'N') {
		printf("처음으로 돌아갑니다.");
		menu_main();
	}
	else if (yn == 'Y' || yn == 'y') {
		return;
	}
	else {
		system("cls");
		goto restart;
	}
}