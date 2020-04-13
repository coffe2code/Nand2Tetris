#include "defs.h"
#include "data.h"
#include "decl.h"

int next(void)
{
	int character;

	if(isEOFTrig) {
		character = EOF;
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

int scanint(int c) {
	int val = 0;
	while(isdigit(c))
	{
		val = (val*10) + (c-48);
		c = next(); 
	}

	return val;
}

char* scanline(int character) {

	char* buffer = malloc( 100*sizeof( char ) );
	*(buffer) = character;
	
	int i = 1;
	
	while(' ' != character && '\t' != character &&
		'\n' != character && '\r' != character &&
		'\f' != character && EOF != character)
	{
		character = next();
		*(buffer+i) = character;
		i+=1;
	}
	if(character == EOF) {
		isEOFTrig = 1;
	}

	*(buffer+i-1) = '\0';
	return buffer;
}

int advance(void)
{

	if(isEOFTrig)
		return 0;

	int c;
	c = skip();
	char* temp;

	switch(c) {
		case EOF:
			return 0;
		case 'p':

			temp = scanline(c);

			if(!strcmp(temp, "push")) 
				CurrCommand.ComType = C_PUSH;
			else 
				CurrCommand.ComType = C_POP;
			
			c = skip();
			CurrCommand.arg1 = scanline(c);

			c = skip();

			CurrCommand.arg2 = scanint(c);
			//printf("%s\n", CurrCommand.arg1);
			break;

		default:
			CurrCommand.ComType = C_ARITHMETIC;
			CurrCommand.arg1 = scanline(c);
			break;
			
	}
	
	return 1;
}