#include "defs.h"
#include "data.h"
#include "decl.h"

void preamble() {

	fprintf(Outfile, "@256\n");
	fprintf(Outfile, "D=A\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "M=D\n");

	//Push return address
	fprintf(Outfile, "@return-address%d\n", CurrReturn);
	fprintf(Outfile, "D=A\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "A=M\n");
	fprintf(Outfile, "M=D\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "M=M+1\n");

	//Push LCL
	fprintf(Outfile, "@LCL\n");
	fprintf(Outfile, "D=M\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "A=M\n");
	fprintf(Outfile, "M=D\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "M=M+1\n");			

	//Push ARG
	fprintf(Outfile, "@ARG\n");
	fprintf(Outfile, "D=M\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "A=M\n");
	fprintf(Outfile, "M=D\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "M=M+1\n");

	//Push THIS
	fprintf(Outfile, "@THIS\n");
	fprintf(Outfile, "D=M\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "A=M\n");
	fprintf(Outfile, "M=D\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "M=M+1\n");

	//Push THAT
	fprintf(Outfile, "@THAT\n");
	fprintf(Outfile, "D=M\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "A=M\n");
	fprintf(Outfile, "M=D\n");
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "M=M+1\n");

	//Set ARG = SP -n -5
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "D=M\n");
	fprintf(Outfile, "@%d\n", CurrCommand.arg2);
	fprintf(Outfile, "D=D-A\n");
	fprintf(Outfile, "@5\n");
	fprintf(Outfile, "D=D-A\n");
	fprintf(Outfile, "@ARG\n");
	fprintf(Outfile, "M=D\n");

	//Set LCL = SP
	fprintf(Outfile, "@SP\n");
	fprintf(Outfile, "D=M\n");
	fprintf(Outfile, "@LCL\n");
	fprintf(Outfile, "M=D\n");

	//goto function
	fprintf(Outfile, "@Sys.init\n");
	fprintf(Outfile, "0;JMP\n");

	//Label for return-address
	fprintf(Outfile, "(return-address%d)\n", CurrReturn);

	CurrReturn += 1;
		
}

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

		case C_LABEL:

			if(isFunc) {

				fprintf(Outfile, "(%s.%s)\n", functionName, CurrCommand.arg1);
			}
			else {

				fprintf(Outfile, "(%s)\n", CurrCommand.arg1);
			}
			
			break;

		case C_GOTO:

			if(isFunc) {

				fprintf(Outfile, "@%s.%s\n", functionName, CurrCommand.arg1);
				fprintf(Outfile, "0;JMP\n");
			}
			else {

				fprintf(Outfile, "@%s\n", CurrCommand.arg1);
				fprintf(Outfile, "0;JMP\n");
			}
			
			break;

		case C_IF:

			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "A=M-1\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "M=M-1\n");

			if(isFunc) {

				fprintf(Outfile, "@%s.%s\n", functionName, CurrCommand.arg1);
			}
			else {

				fprintf(Outfile, "@%s\n", CurrCommand.arg1);
			}

			fprintf(Outfile, "D;JNE\n");

			break;

		case C_FUNCTION:
			
			isFunc = 1;
			strcpy(functionName, CurrCommand.arg1);

			int temp = 0;

			fprintf(Outfile, "(%s)\n", CurrCommand.arg1);

			for(temp=0;temp<CurrCommand.arg2;temp++) {

				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "A=M\n");
				fprintf(Outfile, "M=0\n");
				fprintf(Outfile, "@SP\n");
				fprintf(Outfile, "M=M+1\n");
			}

			break;	

		case C_CALL:

			//Push return address
			fprintf(Outfile, "@return-address%d\n", CurrReturn);
			fprintf(Outfile, "D=A\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "M=D\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "M=M+1\n");

			//Push LCL
			fprintf(Outfile, "@LCL\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "M=D\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "M=M+1\n");			

			//Push ARG
			fprintf(Outfile, "@ARG\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "M=D\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "M=M+1\n");

			//Push THIS
			fprintf(Outfile, "@THIS\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "M=D\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "M=M+1\n");

			//Push THAT
			fprintf(Outfile, "@THAT\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "M=D\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "M=M+1\n");

			//Set ARG = SP -n -5
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@%d\n", CurrCommand.arg2);
			fprintf(Outfile, "D=D-A\n");
			fprintf(Outfile, "@5\n");
			fprintf(Outfile, "D=D-A\n");
			fprintf(Outfile, "@ARG\n");
			fprintf(Outfile, "M=D\n");

			//Set LCL = SP
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@LCL\n");
			fprintf(Outfile, "M=D\n");

			//goto function
			fprintf(Outfile, "@%s\n", CurrCommand.arg1);
			fprintf(Outfile, "0;JMP\n");

			//Label for return-address
			fprintf(Outfile, "(return-address%d)\n", CurrReturn);

			CurrReturn += 1;
			break;

		case C_RETURN:

			//Set FRAME = LCL 
			fprintf(Outfile, "//Set FRAME = LCL\n");
			fprintf(Outfile, "@LCL\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@13\n");
			fprintf(Outfile, "M=D\n");

			//Set RET = *(FRAME-5)
			fprintf(Outfile, "//Set RET = *(FRAME-5)\n");
			fprintf(Outfile, "@13\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@5\n");
			fprintf(Outfile, "D=D-A\n");
			fprintf(Outfile, "A=D\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@14\n");
			fprintf(Outfile, "M=D\n");

			//Set arg=pop()
			fprintf(Outfile, "//Set arg=pop()\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "A=M-1\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@ARG\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "M=D\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "M=M-1\n");

			//Set SP = ARG+1
			fprintf(Outfile, "//Set SP = ARG+1\n");
			fprintf(Outfile, "@ARG\n");
			fprintf(Outfile, "D=M+1\n");
			fprintf(Outfile, "@SP\n");
			fprintf(Outfile, "M=D\n");

			//Set THAT = *(frame-1)
			fprintf(Outfile, "//Set THAT = *(frame-1)\n");
			fprintf(Outfile, "@13\n");
			fprintf(Outfile, "A=M-1\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@THAT\n");
			fprintf(Outfile, "M=D\n");
			
			//Set THIS = *(frame-2)
			fprintf(Outfile, "//Set THIS = *(frame-2)\n");
			fprintf(Outfile, "@2\n");
			fprintf(Outfile, "D=A\n");			
			fprintf(Outfile, "@13\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "A=A-D\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@THIS\n");
			fprintf(Outfile, "M=D\n");

			//Set ARG = *(frame-3)
			fprintf(Outfile, "//Set ARG = *(frame-3)\n");
			fprintf(Outfile, "@3\n");
			fprintf(Outfile, "D=A\n");			
			fprintf(Outfile, "@13\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "A=A-D\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@ARG\n");
			fprintf(Outfile, "M=D\n");

			//Set LCL = *(frame-4)
			fprintf(Outfile, "//Set LCL = *(frame-4)\n");
			fprintf(Outfile, "@4\n");
			fprintf(Outfile, "D=A\n");			
			fprintf(Outfile, "@13\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "A=A-D\n");
			fprintf(Outfile, "D=M\n");
			fprintf(Outfile, "@LCL\n");
			fprintf(Outfile, "M=D\n");


			//goto ret
			fprintf(Outfile, "//goto ret\n");
			fprintf(Outfile, "@14\n");
			fprintf(Outfile, "A=M\n");
			fprintf(Outfile, "0;JMP\n");

			break;
	}
	return;

}