#include "defs.h"
#include "data.h"
#include "decl.h"



void parseAcom(void) {
	
	memset(CurrBinary, '0', sizeof(CurrBinary));
	CurrBinary[0] = '0';

	int val = CurrCommand.ComVal;
	int flag;
	int pos = 15;

	while(val>0) {
		flag = val%2;

		CurrBinary[pos] = flag+'0';
		val = val/2;
		pos = pos - 1;
	}	
	CurrBinary[16] = '\0';
}


void parseAssignment(char* lhs, char* rhs)
{
	memset(CurrBinary, '0', sizeof(CurrBinary));
	
	CurrBinary[16] = '\0';
	CurrBinary[0] = '1';
	CurrBinary[1] = '1';
	CurrBinary[2] = '1';

	if(strcmp(lhs,"M") == 0) {

		CurrBinary[10] = '0';
		CurrBinary[11] = '0';
		CurrBinary[12] = '1';
	}
	else if(strcmp(lhs, "D") == 0) {
		
		CurrBinary[10] = '0';
		CurrBinary[11] = '1';
		CurrBinary[12] = '0';
	}
	else if(strcmp(lhs, "MD") == 0) {
		
		CurrBinary[10] = '0';
		CurrBinary[11] = '1';
		CurrBinary[12] = '1';	 	
	}
	else if(strcmp(lhs, "A") == 0) {
		
		CurrBinary[10] = '1';
		CurrBinary[11] = '0';
		CurrBinary[12] = '0';		
	}
	else if(strcmp(lhs, "AM") == 0) {
		CurrBinary[10] = '1';
		CurrBinary[11] = '0';
		CurrBinary[12] = '1';		
	}
	else if(strcmp(lhs, "AD") == 0) {
		CurrBinary[10] = '1';
		CurrBinary[11] = '1';
		CurrBinary[12] = '0';		
	}
	else if(strcmp(lhs, "AMD") == 0) {
		CurrBinary[10] = '1';
		CurrBinary[11] = '1';
		CurrBinary[12] = '1';		
	}
	
	CurrBinary[3] = '0';

	if(strchr(rhs, 'M') != NULL) {

		CurrBinary[3] = '1';
	}

	
	int count = 0;

	for(count=0;*(rhs+count)!='\0';count++)
	{

	}

	if(strcmp(rhs, "0") == 0) {
		CurrBinary[4] = '1';
		CurrBinary[5] = '0';
		CurrBinary[6] = '1';
		CurrBinary[7] = '0';
		CurrBinary[8] = '1';
		CurrBinary[9] = '0';
	}
	else if(strcmp(rhs, "1") == 0) {

		CurrBinary[4] = '1';
		CurrBinary[5] = '1';
		CurrBinary[6] = '1';
		CurrBinary[7] = '1';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'1';

	}
	else if(strcmp(rhs, "-1") == 0) {
		
		CurrBinary[4] = '1';
		CurrBinary[5] = '1';
		CurrBinary[6] = '1';
		CurrBinary[7] = '0';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'0';
	}
	else if(strcmp(rhs, "D") == 0) {
		
		CurrBinary[4] = '0';
		CurrBinary[5] = '0';
		CurrBinary[6] = '1';
		CurrBinary[7] = '1';
		CurrBinary[8] = '0';
		CurrBinary[9] =	'0';
	}
	else if(strcmp(rhs, "A") == 0 || strcmp(rhs, "M") == 0) {

		CurrBinary[4] = '1';
		CurrBinary[5] = '1';
		CurrBinary[6] = '0';
		CurrBinary[7] = '0';
		CurrBinary[8] = '0';
		CurrBinary[9] =	'0';
	}
	else if(strcmp(rhs, "!D") == 0) {
		
		CurrBinary[4] = '0';
		CurrBinary[5] = '0';
		CurrBinary[6] = '1';
		CurrBinary[7] = '1';
		CurrBinary[8] = '0';
		CurrBinary[9] =	'1';
	}
	else if(strcmp(rhs, "!A") == 0 || strcmp(rhs, "!M") == 0) {
		
		CurrBinary[4] = '1';
		CurrBinary[5] = '1';
		CurrBinary[6] = '0';
		CurrBinary[7] = '0';
		CurrBinary[8] = '0';
		CurrBinary[9] =	'1';
	}
	else if(strcmp(rhs, "-D") == 0) {
		
		CurrBinary[4] = '0';
		CurrBinary[5] = '0';
		CurrBinary[6] = '1';
		CurrBinary[7] = '1';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'1';
	}
	else if(strcmp(rhs, "-A") == 0 || strcmp(rhs, "-M") == 0) {
		
		CurrBinary[4] = '1';
		CurrBinary[5] = '1';
		CurrBinary[6] = '0';
		CurrBinary[7] = '0';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'1';
	}
	else if(strcmp(rhs, "D+1") == 0) {
		
		CurrBinary[4] = '0';
		CurrBinary[5] = '1';
		CurrBinary[6] = '1';
		CurrBinary[7] = '1';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'1';
	}
	else if(strcmp(rhs, "A+1") == 0 || strcmp(rhs, "M+1") == 0) {
		
		CurrBinary[4] = '1';
		CurrBinary[5] = '1';
		CurrBinary[6] = '0';
		CurrBinary[7] = '1';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'1';
	}
	else if(strcmp(rhs, "D-1") == 0) {
		
		CurrBinary[4] = '0';
		CurrBinary[5] = '0';
		CurrBinary[6] = '1';
		CurrBinary[7] = '1';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'0';
	}
	else if(strcmp(rhs, "A-1") == 0 || strcmp(rhs, "M-1") == 0) {
		
		CurrBinary[4] = '1';
		CurrBinary[5] = '1';
		CurrBinary[6] = '0';
		CurrBinary[7] = '0';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'0';
	}
	else if(strcmp(rhs, "D+A") == 0 || strcmp(rhs, "D+M") == 0) {
		

		CurrBinary[4] = '0';
		CurrBinary[5] = '0';
		CurrBinary[6] = '0';
		CurrBinary[7] = '0';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'0';
	}
	else if(strcmp(rhs, "D-A") == 0 || strcmp(rhs, "D-M") == 0) {
		
		CurrBinary[4] = '0';
		CurrBinary[5] = '1';
		CurrBinary[6] = '0';
		CurrBinary[7] = '0';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'1';
	}
	else if(strcmp(rhs, "A-D") == 0 || strcmp(rhs, "M-D") == 0) {
		
		CurrBinary[4] = '0';
		CurrBinary[5] = '0';
		CurrBinary[6] = '0';
		CurrBinary[7] = '1';
		CurrBinary[8] = '1';
		CurrBinary[9] =	'1';
	}
	else if(strcmp(rhs, "D&A") == 0 || strcmp(rhs, "D&M") == 0) {
		
		CurrBinary[4] = '0';
		CurrBinary[5] = '0';
		CurrBinary[6] = '0';
		CurrBinary[7] = '0';
		CurrBinary[8] = '0';
		CurrBinary[9] =	'0';
	}
	else if(strcmp(rhs, "D|A") == 0 || strcmp(rhs, "D|M") == 0) {
		
		CurrBinary[4] = '0';
		CurrBinary[5] = '1';
		CurrBinary[6] = '0';
		CurrBinary[7] = '1';
		CurrBinary[8] = '0';
		CurrBinary[9] =	'1';
	}	
	
	CurrBinary[16] = '\0';
}

void parseJump(char* lhs, char* rhs)
{
	memset(CurrBinary, '0', sizeof(CurrBinary));
	CurrBinary[0] = '1';
	CurrBinary[1] = '1';
	CurrBinary[2] = '1';

	if(strcmp(lhs, "D")==0)
	{
		CurrBinary[4] = '0';
		CurrBinary[5] = '0';
		CurrBinary[6] = '1';
		CurrBinary[7] = '1';
		CurrBinary[8] = '0';
		CurrBinary[9] =	'0';
	}
	else
	{
		CurrBinary[4] = '1';
		CurrBinary[5] = '0';
		CurrBinary[6] = '1';
		CurrBinary[7] = '0';
		CurrBinary[8] = '1';
		CurrBinary[9] = '0';
	}

	if(strcmp(rhs, "JGT") == 0) {

		CurrBinary[13] = '0';
		CurrBinary[14] = '0';
		CurrBinary[15] = '1';

	}
	else if(strcmp(rhs, "JEQ") == 0) {

		CurrBinary[13] = '0';
		CurrBinary[14] = '1';
		CurrBinary[15] = '0';
	}
	else if(strcmp(rhs, "JGE") == 0) {
		
		CurrBinary[13] = '0';
		CurrBinary[14] = '1';
		CurrBinary[15] = '1';
	}
	else if(strcmp(rhs, "JLT") == 0) {
		
		CurrBinary[13] = '1';
		CurrBinary[14] = '0';
		CurrBinary[15] = '0';
	}
	else if(strcmp(rhs, "JNE") == 0) {
		
		CurrBinary[13] = '1';
		CurrBinary[14] = '0';
		CurrBinary[15] = '1';
	}
	else if(strcmp(rhs, "JLE") == 0) {
		
		CurrBinary[13] = '1';
		CurrBinary[14] = '1';
		CurrBinary[15] = '0';
	}
	else if(strcmp(rhs, "JMP") == 0) {
		
		CurrBinary[13] = '1';
		CurrBinary[14] = '1';
		CurrBinary[15] = '1';
	}

	CurrBinary[16] = '\0';

}

void parseCcom(void) {

	char* Text       = CurrCommand.ComText;
	char* assignment = strchr(Text, '=');
	char* jump       = strchr(Text, ';');

	if(assignment != NULL) {

		char* rhs = assignment+1;

		*(assignment) = '\0';

		char* lhs = Text;

		parseAssignment(lhs, rhs);
	}
	else
	{
		char* rhs = jump+1;
		*(jump) = '\0';

		char* lhs = Text;

		parseJump(lhs, rhs);


	}

}

void parse(void) {

	struct Command Current = CurrCommand;

	switch(Current.ComType) {

		case(A_COMMAND):
			parseAcom();
			break;
		case(C_COMMAND):
			parseCcom();
			break;
		case(L_COMMAND):
			break;
	}
}