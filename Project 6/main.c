#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"



void main(int argc, char* argv[]) {

	ROM = 0;
	Infile = fopen(argv[1], "r");

	FILE* out;
	out = fopen("OUT.hack", "w");

	int flag = advance();

	while(flag)
	{
		parse();
		printf("%s\n", CurrBinary);
		fprintf(out, "%s\n", CurrBinary);
		flag = advance();
	}

	fclose(Infile);
	fclose(out);
}
