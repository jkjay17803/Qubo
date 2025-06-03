#pragma once

#define MAX_SIZE_OF_STR 256

typedef struct {
	char* question;
	char** choices;
	int answer;
} MULTIPLE;

typedef struct {
	char* question;
	char* answer;
} SHORT;

typedef struct {
	char* content;
} NOTE;

typedef struct {
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
	Qm,
	Qs,
	Qn
} TYPE;

typedef enum {
	Qm,
	Qs,
	Qn
} CONDITION;

typedef struct {
	SUBJECT* subject;
	int subjectNumber;

	CONDITION condition;

	TYPE type;
	union {
		int chapterNumber;
		char text[256]; // type == Qs
	} submission;
}QUBO;

QUBO qubo;