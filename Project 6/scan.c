#include "defs.h"
#include "data.h"
#include "decl.h"

int next(void)
{
	int character;

	character = fgetc(Infile);

	if(character == '\n')
		ROM++;

	return character;
}

int skip(void)
{
	int character = next();

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
	c = next(); 
	while(isdigit(c))
	{
		val = (val*10) + (c-48);
		c = next(); 
	}

	return val;
}

void scanline(int character) {
	
	(CurrCommand.ComText) = malloc( sizeof( char ) );
	*(CurrCommand.ComText) = '\0';
	*(CurrCommand.ComText) = character;
	
	int i = 1;
	
	while(' ' != character && '\t' != character &&
		'\n' != character && '\r' != character &&
		'\f' != character)
	{
		character = next();
		*(CurrCommand.ComText+i) = character;
		i+=1;
	}

	*(CurrCommand.ComText+i) = '\0';

}

int advance(void)
{

	int c;

	c = skip();

	switch(c) {

		case EOF:
			return 0;
			break;
		case '@':
			CurrCommand.ComType = A_COMMAND;
			CurrCommand.ComVal		 = scanint(c);
			break;
		case '(':
			CurrCommand.ComType = L_COMMAND;
			scanline(c);
			break;
		default:
			CurrCommand.ComType = C_COMMAND;
			scanline(c);
			break;
	}

	return 1;
}