#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
	C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, 
	C_IF, C_FUNCTION, C_RETURN, C_CALL
};

struct Command {
	int ComType;
	char* arg1;
	int arg2;
};

