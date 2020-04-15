#include "defs.h"
#include "data.h"
#include "decl.h"


void codebody(char* arg1, int arg2, char* filename) {

	switch(CurrCommand.ComType) {

		case C_ARITHMETIC:
			if(!strcmp(CurrCommand.arg1, "add")) {
				
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "A=A-1\n");
				fprintf(Outfile, "D=D+M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
			}
			else if(!strcmp(CurrCommand.arg1, "sub")) {
				
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "A=A-1\n");
				fprintf(Outfile, "D=M-D\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
			}
			else if(!strcmp(CurrCommand.arg1, "neg")) {

				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "M=-M\n");
			}
			else if(!strcmp(CurrCommand.arg1, "eq")) {
				
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "A=A-1\n");
				fprintf(Outfile, "D=M-D\n");
				fprintf(Outfile, "@IfEq%d\n", CurrFlag);
				fprintf(Outfile, "D;JNE\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "A=A-1\n");
				fprintf(Outfile, "M=-1\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
				fprintf(Outfile, "@IfEqEnd%d\n", CurrFlag);
				fprintf(Outfile, "0;JMP\n");
				fprintf(Outfile, "(IfEq%d)\n", CurrFlag);
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "A=A-1\n");				
				fprintf(Outfile, "M=0\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
				fprintf(Outfile, "(IfEqEnd%d)\n", CurrFlag);

				CurrFlag+=1;
			}
			else if(!strcmp(CurrCommand.arg1, "gt")) {
				
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "A=A-1\n");
				fprintf(Outfile, "D=M-D\n");
				fprintf(Outfile, "@IfGt%d\n", CurrFlag);
				fprintf(Outfile, "D;JLE\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "A=A-1\n");				
				fprintf(Outfile, "M=-1\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
				fprintf(Outfile, "@IfGtEnd%d\n", CurrFlag);
				fprintf(Outfile, "0;JMP\n");
				fprintf(Outfile, "(IfGt%d)\n", CurrFlag);
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "A=A-1\n");				
				fprintf(Outfile, "M=0\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
				fprintf(Outfile, "(IfGtEnd%d)\n", CurrFlag);

				CurrFlag+=1;

			}
			else if(!strcmp(CurrCommand.arg1, "lt")) {
				
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "A=A-1\n");
				fprintf(Outfile, "D=M-D\n");
				fprintf(Outfile, "@IfLt%d\n", CurrFlag);
				fprintf(Outfile, "D;JGE\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "A=A-1\n");				
				fprintf(Outfile, "M=-1\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
				fprintf(Outfile, "@IfLtEnd%d\n", CurrFlag);
				fprintf(Outfile, "0;JMP\n");
				fprintf(Outfile, "(IfLt%d)\n", CurrFlag);
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "A=A-1\n");				
				fprintf(Outfile, "M=0\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
				fprintf(Outfile, "(IfLtEnd%d)\n", CurrFlag);

				CurrFlag+=1;
			}
			else if(!strcmp(CurrCommand.arg1, "and")) {

				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "A=A-1\n");
				fprintf(Outfile, "D=D&M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");												
			}
			else if(!strcmp(CurrCommand.arg1, "or")) {
				
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "A=A-1\n");
				fprintf(Outfile, "M=D|M\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");																
			}
			else if(!strcmp(CurrCommand.arg1, "not")) {

				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "M=!M\n");				
			}
			break;

		case C_PUSH:
			
			if(!strcmp(CurrCommand.arg1, "constant")) {
				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M+1\n");

			}
			else if(!strcmp(CurrCommand.arg1, "local")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@LCL\n");
				fprintf(Outfile, "A=D+M\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M+1\n");				
			}
			else if(!strcmp(CurrCommand.arg1, "argument")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@ARG\n");
				fprintf(Outfile, "A=D+M\n");
				fprintf(Outfile, "D=M\n" );
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");	
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M+1\n");			
			}
			else if(!strcmp(CurrCommand.arg1, "pointer")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@3\n");
				fprintf(Outfile, "A=D+A\n");
				fprintf(Outfile, "D=M\n" );
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");	
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M+1\n");
			}
			else if(!strcmp(CurrCommand.arg1, "this")) {
				
				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@THIS\n");
				fprintf(Outfile, "A=D+M\n");
				fprintf(Outfile, "D=M\n" );
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");	
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M+1\n");				
			}
			else if(!strcmp(CurrCommand.arg1, "that")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@THAT\n");
				fprintf(Outfile, "A=D+M\n");
				fprintf(Outfile, "D=M\n" );
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");	
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M+1\n");				
			}
			else if(!strcmp(CurrCommand.arg1, "temp")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@5\n");
				fprintf(Outfile, "A=D+A\n");
				fprintf(Outfile, "D=M\n" );
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");	
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M+1\n");
			}
			else if(!strcmp(CurrCommand.arg1, "static")) {

				fprintf(Outfile, "@%s.%d\n",filename, CurrCommand.arg2 );
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n" );
				fprintf(Outfile, "M=M+1\n");
			}
			break;

		case C_POP:

			if(!strcmp(CurrCommand.arg1, "local")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@LCL\n");
				fprintf(Outfile, "D=D+M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
			}
			else if(!strcmp(CurrCommand.arg1, "argument")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@ARG\n");
				fprintf(Outfile, "D=D+M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
			
			}
			else if(!strcmp(CurrCommand.arg1, "pointer")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@3\n");
				fprintf(Outfile, "D=D+A\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
			}
			else if(!strcmp(CurrCommand.arg1, "this")) {
				
				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@THIS\n");
				fprintf(Outfile, "D=D+M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");			
			}
			else if(!strcmp(CurrCommand.arg1, "that")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@THAT\n");
				fprintf(Outfile, "D=D+M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");		
			}
			else if(!strcmp(CurrCommand.arg1, "temp")) {

				fprintf(Outfile, "@%d\n", CurrCommand.arg2);
				fprintf(Outfile, "D=A\n");
				fprintf(Outfile, "@5\n");
				fprintf(Outfile, "D=D+A\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "@13\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
			}
			else if(!strcmp(CurrCommand.arg1, "static")) {

				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M-1\n");
				fprintf(Outfile, "D=M\n");
				fprintf(Outfile, "@%s.%d\n", filename, CurrCommand.arg2);
				fprintf(Outfile, "M=D\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M-1\n");
			}
			break;
			

	}
	return;

}