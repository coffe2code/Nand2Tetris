#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
	A_COMMAND, C_COMMAND, L_COMMAND
};

struct Command {
	int ComType;
	int ComVal;
	char* ComText;
};

struct sym {
	char* symbol;
	int RamPos;

};

