#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"
#include "load.h"

#define MAX_SIZE_OF_STR 500

int main(void) {
	loadFile();
	showQuestionNumber();
	return 0;
}