#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load.h"
#include "struct.h"

void loadFile() {
	printf("파일을 불러오는 중입니다...\n\n");

	qubo.subjectNumber = 0;

	FILE* file;
	fopen_s(&file, "question.txt", "r");
	if (file == NULL) {
		printf("파일 열기 실패");
		exit(4);
	}

	char line[256];
	while (fgets(line, sizeof(line), file)) {
		if (qubo.condition == NULL) {

			if (line[0] == '[') getSubject(line);
			if (line[0] == '#') getChapter(line);
			if (line[0] == 'q') {
				switch (line[1]) {
				case 'm':
					//getQM(line);
					break;
				case 's':
					getQS(line);
					break;
				case 'n':
					//getQN(line);
					break;
				}
			} 

		}
		else {
			switch (qubo.condition) {
			case QM:
				break;
			case QS:
				getQS(line);
				break;
			case QN:
				break;
			}
		}
	}
}

void strTrim(char line[]) {
	while (line[0] == ' ') {
		for (int i = 0; line[i] != '\0'; i++) {
			line[i] = line[i + 1];
		}
	}
	int len = (int)strlen(line)-1;
	while (line[len] == ' ') {
		line[len] = line[len + 1];
		len = (int)strlen(line)-1;
	}
}

void getSubject(char line[]) {
	for (int i = 0; line[i] != '\0'; i++) {
		line[i] = line[i + 1];
		if (line[i] == ']') 
			line[i] = '\0';
	}
	strTrim(line);

	qubo.subjectNumber++;
	SUBJECT* tmp = realloc(qubo.subject, qubo.subjectNumber * sizeof(SUBJECT));
	if (tmp != NULL) {
		qubo.subject = tmp;
	}
	else {
		printf("<과목> 메모리 할당 실패");
		exit(1);
	}

	SUBJECT* currentSubject = &qubo.subject[qubo.subjectNumber - 1];

	strcpy_s(currentSubject->subjectName, sizeof(currentSubject->subjectName), line);
	currentSubject->chapterNumber = 0;
	currentSubject->chapter = NULL;
	printf("- [ %s ]\n", currentSubject->subjectName);
}

void getChapter(char line[]) {
	for (int i = 0; line[i] != '\0'; i++) {
		line[i] = line[i + 1];
	}
	strTrim(line);

	SUBJECT* currentSubject = &qubo.subject[qubo.subjectNumber - 1];

	currentSubject->chapterNumber++;
	CHAPTER* tmp = realloc(currentSubject->chapter, currentSubject->chapterNumber * sizeof(CHAPTER));
	if (tmp != NULL) currentSubject->chapter = tmp;
	else {
		printf("<챕터> 메모리 할당 실패>");
		exit(1);
	}

	strcpy_s(currentSubject->chapter[currentSubject->chapterNumber - 1].chapterName,
		sizeof(currentSubject->chapter[currentSubject->chapterNumber - 1].chapterName),
		line
	);
	CHAPTER* currentChapter = &currentSubject->chapter[currentSubject->chapterNumber - 1];
	currentChapter->questionNumber = 0;
	currentChapter->question = NULL;
	printf("%s", currentSubject->chapter[currentSubject->chapterNumber-1].chapterName);
}

void getQS(char line[]) {
	static int condition = 0;
	if (condition == 0) getQSQuestion(line);
	
}

void getQSQuestion(char line[]) {
	for (int ii = 0; ii < 2; ii++) {
		for (int i = 0; line[i] != '\0'; i++) {
			line[i] = line[i + 1];
		}
	}
	strTrim(line);

	SUBJECT* currentSubject = &qubo.subject[qubo.subjectNumber - 1];
	CHAPTER* currentChapter = &currentSubject->chapter[currentSubject->chapterNumber - 1];

	currentChapter->questionNumber++;
	QUESTION* tmp = realloc(currentChapter->question, currentChapter->questionNumber * sizeof(QUESTION));
	if (tmp != NULL) currentChapter->question = tmp;
	else {
		printf("<문제> 메모리 할당 실패>");
		exit(1);
	}

	strcpy_s(currentChapter->question[currentChapter->questionNumber - 1].qs.question,
		sizeof(currentChapter->question[currentChapter->questionNumber - 1].qs.question),
		line
	);

	printf("%s", currentChapter->question[currentChapter->questionNumber - 1].qs.question);
}
