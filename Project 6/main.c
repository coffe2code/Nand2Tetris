#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"


void main(int argc, char* argv[]) {

	ROM = 0;
	Infile = fopen(argv[1], "r");

	int flag = advance();

	while(flag)
	{
		printf("The line is: %d\n", ROM);	
		if(CurrCommand.ComType != A_COMMAND)
			printf("%s\n", CurrCommand.ComText);
		else
		{
			printf("%d\n", CurrCommand.ComVal);
		}
		flag = advance();
	}

}
