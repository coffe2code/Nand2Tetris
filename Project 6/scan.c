#include "defs.h"
#include "data.h"
#include "decl.h"

int next(void)
{
	int character;

	character = fgetc(Infile);

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
	while(isdigit(c))
	{
		val = (val*10) + (c-48);
		c = next(); 
	}

	return val;
}

void scanline(int character) {

	(CurrCommand.ComText) = malloc( 100*sizeof( char ) );
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

	*(CurrCommand.ComText+i-1) = '\0';

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
			c = next();
			
			if(isdigit(c)) {

				CurrCommand.ComVal = scanint(c);
			}
			else {
				scanline(c);
				
				if(!isPrimScan) {

					if(findglob(CurrCommand.ComText) == -1) {
						
						addglob(CurrCommand.ComText, CurrRAM);

						CurrCommand.ComVal = CurrRAM;

						CurrRAM++;
					}
					else {
						
						CurrCommand.ComVal = GSym[findglob(CurrCommand.ComText)].RamPos;
					}
				}

			}
			break;
		case '(':
			CurrCommand.ComType = L_COMMAND;
			c = next();
			scanline(c);
			int len = strlen(CurrCommand.ComText);
			*(CurrCommand.ComText+len-1) = '\0';

			if(isPrimScan) {

				addglob(CurrCommand.ComText, ROM);
			}
			ROM--;

			break;
		default:
			if(!isPrimScan) {
				
				CurrCommand.ComType = C_COMMAND;
				scanline(c);
				break;	
			}
			else {
				scanline(c);
			}
			
	}
	
	ROM++;

	return 1;
}