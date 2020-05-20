#include <libgen.h>
#include <string.h>
#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"


void main(int argc, char* argv[]) {
		
	Outfile = fopen(argv[1], "w");
	//fprintf(Outfile, "<tokens>\n");
	int files = 0;


	for(files=2;files<argc;files++)
	{
		isEOFTrig = 0;

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

				TokenPutback = 1;
				Constructor();
			} 
		
		}

		fclose(Infile);
	}

	fclose(Outfile);
}