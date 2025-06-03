#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load.h"
#include "struct.h"

void loadFile() {
	printf("파일을 불러오는 중입니다...\n\n");

	qubo.type = None;
	qubo.subjectNumber = 0;

	FILE* file;
	fopen_s(&file, "question.txt", "r");
	if (file == NULL) {
		printf("파일 열기 실패");
		exit(4);
	}

	char line[256];
	while (fgets(line, sizeof(line), file)) {
		if (qubo.type == None) {

			if (line[0] == '[') { 
				getSubject(line); }
			else if (line[0] == '#') {
				getChapter(line);
			}
			else if (line[0] == 'q') {
				switch (line[1]) {
				case 'm':
					qubo.condition.Qm = 0;
					getQM(line);
					break;
				case 's':
					qubo.condition.Qs = 0;
					getQS(line);
					break;
				case 'n':
					getQN(line);
					break;
				}
			} 

		}
		else {
			switch (qubo.type) {
			case Qm:
				getQM(line);
				break;
			case Qs:
				getQS(line);
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
	printf("    # %s", currentSubject->chapter[currentSubject->chapterNumber-1].chapterName);
}


void getQS(char line[]) {
	if (qubo.condition.Qs == 0) getQSQuestion(line);
	else if (qubo.condition.Qs == 1) getQSAnswer(line);
}

void getQSQuestion(char line[]) {
	qubo.type = Qs;
	qubo.condition.Qs++;

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
		printf("<문제> 메모리 할당 실패");
		exit(1);
	}

	strcpy_s(currentChapter->question[currentChapter->questionNumber - 1].qs.question,
		sizeof(currentChapter->question[currentChapter->questionNumber - 1].qs.question),
		line
	);
}

void getQSAnswer(char line[]) {
	qubo.condition.Qs = 0;
	qubo.type = None;

	strTrim(line);

	SUBJECT* currentSubject = &qubo.subject[qubo.subjectNumber - 1];
	CHAPTER* currentChapter = &currentSubject->chapter[currentSubject->chapterNumber - 1];
	strcpy_s(currentChapter->question[currentChapter->questionNumber - 1].qs.answer,
		sizeof(currentChapter->question[currentChapter->questionNumber - 1].qs.answer),
		line
	);
}


void getQM(char line[]) {
	if (qubo.condition.Qm == 0) getQMQuestion(line);
	else if (qubo.condition.Qm == 1) getQMChoice(line);
}

void getQMQuestion(char line[]) {
	qubo.type = Qm;
	qubo.condition.Qm++;

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
		printf("<문제> 메모리 할당 실패");
		exit(1);
	}

	strcpy_s(currentChapter->question[currentChapter->questionNumber - 1].qm.question,
		sizeof(currentChapter->question[currentChapter->questionNumber - 1].qm.question),
		line
	);
	currentChapter->question[currentChapter->questionNumber - 1].qm.choiceNumber = 0;
	currentChapter->question[currentChapter->questionNumber - 1].qm.choices = NULL;
}

void getQMChoice(char line[]) {
	if (line[0] != '-') {
		getQMAnswer(line);
		return;
	}

	for (int i = 0; line[i] != '\0'; i++) 
		line[i] = line[i + 1];
	strTrim(line);

	SUBJECT* currentSubject = &qubo.subject[qubo.subjectNumber - 1];
	CHAPTER* currentChapter = &currentSubject->chapter[currentSubject->chapterNumber - 1];
	QUESTION* currentQuestion = &currentChapter->question[currentChapter->questionNumber - 1];

	currentQuestion->qm.choiceNumber++;
	char** tmp = realloc(currentQuestion->qm.choices, currentQuestion->qm.choiceNumber * sizeof(char*));
	if (tmp != NULL) currentQuestion->qm.choices = tmp;
	else {
		printf("<문제-선택지> 메모리 할당 실패");
		exit(1);
	}

	currentQuestion->qm.choices[currentQuestion->qm.choiceNumber - 1] = malloc(MAX_SIZE_OF_STR * sizeof(char));
	if (currentQuestion->qm.choices[currentQuestion->qm.choiceNumber - 1] == NULL) {
		printf("<문제-선택지-문자열> 메모리 할당 실패");
		exit(1);
	}

	strcpy_s(currentQuestion->qm.choices[currentQuestion->qm.choiceNumber-1],
		sizeof(currentQuestion->qm.choices[currentQuestion->qm.choiceNumber - 1]),
		line
	);
}

void getQMAnswer(char line[]) {
	qubo.condition.Qm = 0;
	qubo.type = None;
	strTrim(line);

	if (line[0] >= '1' && line[0] <= '9');
	int tmp = line[0]-1;

	SUBJECT* currentSubject = &qubo.subject[qubo.subjectNumber - 1];
	CHAPTER* currentChapter = &currentSubject->chapter[currentSubject->chapterNumber - 1];
	QUESTION* currentQuestion = &currentChapter->question[currentChapter->questionNumber - 1];

	currentQuestion->qm.answer = tmp;
}


void getQN(char line[]) {
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

	strcpy_s(currentChapter->question[currentChapter->questionNumber - 1].qn.content,
		sizeof(currentChapter->question[currentChapter->questionNumber - 1].qn.content),
		line
	);
}

//void showQuestionNumber() {
//	static int condition = 0;
//	if (condition == 0) {
//		condition++;
//		return;
//	}
//	SUBJECT* currentSubject = &qubo.subject[qubo.subjectNumber - 1];
//	CHAPTER* currentChapter = &currentSubject->chapter[currentSubject->chapterNumber - 1];
//	if(currentChapter->questionNumber > 0) 
//		printf("%d\n", currentChapter->questionNumber);
//	condition = 0;
//}


//getQS QM 예외처리
