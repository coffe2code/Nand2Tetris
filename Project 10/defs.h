#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
	KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST
};


struct Token {
	
	int tokentype;
	char* keyword;
	char symbol;
	int intval;
	char* identifier;
	char* stringval;
};

