#include "defs.h"
#include "data.h"
#include "decl.h"

int next(void)
{

	int character;

	if(Putback) {

		character = Putback;
		Putback  = 0;
		return character;
	}

	character = fgetc(Infile);

	return character;
}

int skip(void)
{
	int character;

	character = next();

	while(' ' == character || '\t' == character ||
		'\n' == character || '\r' == character ||
		'\f' == character)
	{
		character = next();
	}

	return character;
}

void putback(int character) {

	Putback = character;
}

int scanint(int c) {
	int val = 0;
	while(isdigit(c))
	{
		val = (val*10) + (c-48);
		c = next(); 
	}

	putback(c);

	return val;
}

char* scanident(int character, int istring) {

	char* buffer = malloc( 100*sizeof( char ) );
	*(buffer) = character;
	
	int i = 1;
	
	if(istring) {
		
		while(character != '"' && character != '\n')
		{
			character = next();
			*(buffer+i) = character;
			i+=1;
		}
	}
	else {
		
		while(isalpha(character) || isdigit(character) || character == '_')
		{
			character = next();
			*(buffer+i) = character;
			i+=1;
		}
	}
	
	putback(character);

	*(buffer+i-1) = '\0';
	return buffer;
}


int keyword(char* text) {

	switch(*text) {

		case 'c':
			if(!strcmp(text, "class")) {
				
				CurrToken.keyword   = "class";
				return 1;
			}
			else if(!strcmp(text, "constructor")) {
				
				CurrToken.keyword   = "constructor";
				return 1;
			}
			else if(!strcmp(text, "char")) {
				
				CurrToken.keyword   = "char";
				return 1;
			}
			break;
		case 'f':
			if(!strcmp(text, "function")) {
				
				CurrToken.keyword   = "function";
				return 1;
			}
			else if(!strcmp(text, "field")) {
				
				CurrToken.keyword   = "field";
				return 1;
			}
			else if(!strcmp(text, "false")) {

				CurrToken.keyword 	= "false";
				return 1;
			}
			break;
		case 'm':
			if(!strcmp(text, "method")) {
				
				CurrToken.keyword   = "method";
				return 1;
			}
			break;
		case 's':
			if(!strcmp(text, "static")) {
				
				CurrToken.keyword   = "static";
				return 1;
			}
			break;
		case 'v':
			if(!strcmp(text, "var")) {
				
				CurrToken.keyword   = "var";
				return 1;
			}
			else if(!strcmp(text, "void")) {
				
				CurrToken.keyword   = "void";
				return 1;
			}
			break;
		case 'b':
			if(!strcmp(text, "boolean")) {
				
				CurrToken.keyword   = "boolean";
				return 1;
			}
			break;
		case 't':
			if(!strcmp(text, "this")) {
				
				CurrToken.keyword   = "this";
				return 1;
			}
			else if(!strcmp(text, "true")) {

				CurrToken.keyword 	= "true";
				return 1;
			}
			break;
		case 'n':
			if(!strcmp(text, "null")) {
				
				CurrToken.keyword   = "null";
				return 1;
			}
			break;
		case 'l':
			if(!strcmp(text, "let")) {
				
				CurrToken.keyword   = "let";
				return 1;
			}
			break;
		case 'd':
			if(!strcmp(text, "do")) {
				
				CurrToken.keyword   = "do";
				return 1;
			}
			break;
		case 'i':
			if(!strcmp(text, "if")) {
				
				CurrToken.keyword   = "if";
				return 1;
			}
			else if(!strcmp(text, "int")) {
				
				CurrToken.keyword   = "int";
				return 1;
			}
			break;
		case 'e':
			if(!strcmp(text, "else")) {
				
				CurrToken.keyword   = "else";
				return 1;
			}
			break;
		case 'w':
			if(!strcmp(text, "while")) {
				
				CurrToken.keyword   = "while";
				return 1;
			}
			break;
		case 'r':
			if(!strcmp(text, "return")) {
				
				CurrToken.keyword   = "return";
				return 1;
			}
			break;
	}

	return 0;
}

int advance(void)
{
	char* temp;
	int counter = 0;

	int c;
	c = skip();

	if(c == EOF)
		return 0;


	switch(c) {
		
		case '{':
		case '}':
		case '(':
		case ')':
		case '[':
		case ']':
		case '.':
		case ',':
		case ';':
		case '+':
		case '-':
		case '*':
		case '/':
		case '&':
		case '|':
		case '<':
		case '>':
		case '=':
		case '~':
			CurrToken.tokentype = SYMBOL;
			CurrToken.symbol    = c;
			break;

		case '"':
			CurrToken.tokentype = STRING_CONST;
			c = next();
			temp = scanident(c,1);
			c = next();
			CurrToken.stringval = temp;
			break;

		default:
			
			if(isdigit(c)) {

				CurrToken.tokentype = INT_CONST;
				CurrToken.intval    = scanint(c);

			}
			else {

				temp = scanident(c,0);
				if(keyword(temp)) {

					CurrToken.tokentype = KEYWORD;
				}
				else {
					CurrToken.tokentype = IDENTIFIER;
					CurrToken.identifier = temp;
				}
			}


	}
	
	return 1;
}