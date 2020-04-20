#include <libgen.h>
#include <string.h>
#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"


void main(int argc, char* argv[]) {
		
	Outfile = fopen(argv[1], "w");

	int files = 0;

	preamble();

	for(files=2;files<argc;files++)
	{
		isEOFTrig = 0;
		CurrFlag = 0;
		Infile = fopen(argv[files], "r");
	
		char* filename = basename(argv[files]);

		int count = 0;
		
		for(count=0; filename[count]!='\0';count++)
		{
			if(filename[count]=='.')
				filename[count]='\0';
		}

		int flag = 1;

		while(flag && !isEOFTrig)
		{	

			flag = advance();

			if(flag) {

				codebody(CurrCommand.arg1, CurrCommand.arg2, filename);
			} 
		
		}
		fclose(Infile);
	}
	 

	fprintf(Outfile, "(END)\n");
	fprintf(Outfile, "@END\n");
	fprintf(Outfile, "0;JMP\n");
	
	
	fclose(Outfile);


}
