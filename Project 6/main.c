#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"

#define PreSymNo 7
#define PreRegNo 16

char* predefsym[PreSymNo] = {"SP", "LCL", "ARG", "THIS", "THAT", "SCREEN", "KBD"};
int RamLoc[PreSymNo] = {0, 1, 2, 3, 4, 16384, 24576};   


char* predefreg[PreRegNo] = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", 
						"R9", "R10", "R11", "R12", "R13", "R14", "R15"};
void init() {

	int count = 0;

	for(count=0;count<PreSymNo;count++) {

		addglob(predefsym[count], RamLoc[count]);
	}

	for(count=0;count<PreRegNo;count++)
	{
		addglob(predefreg[count], count);
	}

	//(CurrCommand.ComText) = malloc( 100*sizeof( char ) );
}

void main(int argc, char* argv[]) {

	//(CurrCommand.ComText) = malloc( sizeof( char ) );
	init();
	ROM = 0;
	CurrRAM = 16;

	Infile = fopen(argv[1], "r");

	isPrimScan  = 1;

	int flag = advance();

	while(flag)
	{
		parse();
		flag = advance();
	}
	int x=0;
	//for(x=0;x<=23;x++)
	//	printf("%s\n", GSym[x].symbol);

	fclose(Infile);

	Infile = fopen(argv[1], "r");
	isPrimScan = 0;

	FILE* out;
	out = fopen("OUT.hack", "w");
	
	flag = advance();

	while(flag)
	{
		parse();
		if(CurrCommand.ComType != L_COMMAND) {
			
			printf("%s\n", CurrBinary);
			fprintf(out, "%s\n", CurrBinary);			
		}

		flag = advance();
	}

	fclose(Infile);
	fclose(out);
}
