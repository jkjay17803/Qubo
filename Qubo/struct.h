#pragma once

#define MAX_SIZE_OF_STR 256

typedef struct {
	char question[MAX_SIZE_OF_STR];
	char** choices;
	int choiceNumber;
	int answer;
} MULTIPLE;

typedef struct {
	char question[MAX_SIZE_OF_STR];
	char answer[MAX_SIZE_OF_STR];
} SHORT;

typedef struct {
	char content[MAX_SIZE_OF_STR];
} NOTE;

typedef struct {
	int isQm;
	MULTIPLE qm;
	SHORT qs;
	NOTE qn;
} QUESTION;

typedef struct{
	char chapterName[MAX_SIZE_OF_STR];
	QUESTION* question;
	int questionNumber;
} CHAPTER;

typedef struct {
	char subjectName[MAX_SIZE_OF_STR];
	CHAPTER* chapter;
	int chapterNumber;
} SUBJECT;

typedef enum {
	None,
	Qm,
	Qs
} LOADTYPE;

typedef struct {
	int main;
	int Qm;
	int Qs;
}CONDITION;

typedef struct {
	int subject;
	int chapter;
	int qs;
	int qm;
	int qn;
	int question;
} SELECT;

typedef struct {
	SUBJECT* subject;
	int subjectNumber;

	SELECT select;

	CONDITION condition;

	LOADTYPE type;
	union {
		int chapterNumber;
		char text[256]; // type == Qs
	} submission;
}QUBO;

QUBO qubo;