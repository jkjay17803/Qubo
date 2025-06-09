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

	char test; // ���� �� �Է� Ȯ�ο�
	int select;
	printf("[ �޴� ]\n\n");
	printf("���ϴ� ���� �������ּ���.\n");
	printf("( 0: ���� / 1: �ܿ�� ��� (���� ǥ�õ˴ϴ�.) / 2: ���� ��� (���� ǥ�õ��� �ʽ��ϴ�.) )\n");
	printf(":");
	scanf_s("%d", &select);
	

	switch (select) {
	case 0:
		printf("�����մϴ�.");
		exit(0);
		break;
	case 1:
		selectSubject();
		solve();
		printf("���� Ǯ�̰� �������ϴ�!\n�ƹ� ���ڳ� �Է��ؼ� ���ư�����.");
		scanf_s(" %c", &test, (unsigned int)sizeof(test));
		break;
	case 2:
		selectSubject();
		solve_remember();
		printf("���� Ǯ�̰� �������ϴ�!\n�ƹ� ���ڳ� �Է��ؼ� ���ư�����.");
		scanf_s(" %c", &test, (unsigned int)sizeof(test));
		break;
	default:
		restartBuffer = getchar();
		goto restart;
	}
}

void selectSubject() {
	system("cls");
	printf("[ ���� ���� ]\n\n");
	printf("���ϴ� ������ ��ȣ�� �Է����ּ���.\n");
	printf("( 0 �Է� ��. ���ư��� )\n\n");
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
	printf("[ é�� ���� ]\n\n");
	printf("' %s ' ������ ���õǾ����ϴ�.\n\n", qubo.subject[qubo.select.subject].subjectName);
	printf("���ϴ� é���� ��ȣ�� �Է����ּ���.\n");
	printf("( 0 �Է� ��. ���ư��� )\n\n");
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
	printf("[ é�� Ȯ�� ]\n\n");
	printf("' %s ' é�Ͱ� ���õǾ����ϴ�.\n��� �����ұ��? (y/n)\n", currentChapter->chapterName);
	char yn;
	yn = getchar();
	if (yn == 'n' || yn == 'N') {
		printf("ó������ ���ư��ϴ�.");
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