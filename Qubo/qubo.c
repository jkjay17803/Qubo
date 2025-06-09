#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"
#include "load.h"
#include "menu.h"

int main(void) {
	loadFile();
	showQuestionNumber();

	restart:
	printf("\n���α׷��� �����մϱ�? (y/n)\n:");
	char yn;
	scanf_s(" %c", &yn, (unsigned int)sizeof(yn));
	if (yn == 'n' || yn == 'N') {
		printf("���α׷��� �����մϴ�.");
		return 0;
	}
	else if (yn == 'Y' || yn == 'y') {
		while(1) menu_main();
	}
	else {
		system("cls");
		goto restart;
	}

	menu_main();
}

