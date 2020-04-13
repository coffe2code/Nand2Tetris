#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"


void main(int argc, char* argv[]) {
	
	isEOFTrig = 0;
	Infile = fopen(argv[1], "r");
	 
	int flag = advance();

	while(flag && !isEOFTrig)
	{	

		if(flag) {
			printf("%d\n", CurrCommand.ComType);
			printf("%s\n", CurrCommand.arg1);
			printf("\n");
		} 
		flag = advance();
	}
	
	
	fclose(Infile);


}
