#include <libgen.h>
#include <string.h>
#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"


void main(int argc, char* argv[]) {
	
	isEOFTrig = 0;
	CurrFlag = 0;
	Infile = fopen(argv[1], "r");


	///Messy Hack to get filename without extension
	char* filename = basename(argv[1]);

	int count = 0;
	for(count=0; filename[count]!='\0';count++)
	{
		if(filename[count]=='.')
			filename[count]='\0';
	}

	char* temp;
	strcpy(temp, filename);
	char* outputfile = strcat(temp, ".asm");
	
	
	Outfile = fopen(outputfile, "w");	
	 
	int flag = 1;

	while(flag && !isEOFTrig)
	{	

		flag = advance();

		if(flag) {

			codebody(CurrCommand.arg1, CurrCommand.arg2, filename);
		} 
		
	}
	fprintf(Outfile, "(END)\n");
	fprintf(Outfile, "@END\n");
	fprintf(Outfile, "0;JMP\n");
	
	fclose(Infile);
	fclose(Outfile);


}
