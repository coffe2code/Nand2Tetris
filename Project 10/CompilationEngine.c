#include "defs.h"
#include "data.h"
#include "decl.h"


void compileLet();
void compileDo();
void compileWhile();
void compileIf();
void compileReturn();
void compileStatements();
void compileVarDec();
void compileParameterList();
void CompileTerm();
void CompileExpression();
void CompileExpressionList();
void CompileSubroutine();
void CompileClassVarDec();
void CompileClass();
void Constructor();

void compileLet() {

	fprintf(Outfile, "<letStatement>\n");
	fprintf(Outfile, "<keyword> let </keyword>\n");
	advance();
	fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);
	
	advance();

	while(CurrToken.symbol == '[') {
		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
		CompileExpression();
		
		if(TokenPutback == 0)
			advance();
		else
			TokenPutback = 0;

		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
		advance();
	}

	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	CompileExpression();
	
	if(TokenPutback == 0)
		advance();
	else
		TokenPutback = 0;

	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	fprintf(Outfile, "</letStatement>\n");
}

void compileDo() {
	
	fprintf(Outfile, "<doStatement>\n");
	fprintf(Outfile, "<keyword> do </keyword>\n");
	advance();
	fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);
	advance();

	if(CurrToken.symbol == '(') {

		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

	}
	else if(CurrToken.symbol == '.') {

		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
		advance();
		fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);
		advance();
		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

	}

		CompileExpressionList();

		if(TokenPutback == 0)
			advance();
		else
			TokenPutback = 0;
		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
		advance();
		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
		fprintf(Outfile, "</doStatement>\n");
}

void compileWhile() {

	fprintf(Outfile, "<whileStatement>\n");
	fprintf(Outfile, "<keyword> while </keyword>\n");
	advance();
	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	CompileExpression();

	if(TokenPutback == 0)
		advance();
	else
		TokenPutback = 0;

	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	advance();
	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	compileStatements();

	if(TokenPutback == 0)
		advance();
	else 
		TokenPutback = 0;

	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	fprintf(Outfile, "</whileStatement>\n");
}

void compileIf() {

	fprintf(Outfile, "<ifStatement>\n");
	fprintf(Outfile, "<keyword> if </keyword>\n");
	advance();
	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	CompileExpression();

	if(TokenPutback == 0)
		advance();
	else
		TokenPutback = 0;
	
	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	advance();
	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	compileStatements();
	if(TokenPutback==0)
		advance();
	else
		TokenPutback=0;
	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	advance();
	if(CurrToken.tokentype == KEYWORD && strcmp(CurrToken.keyword,"else") == 0) {

		fprintf(Outfile, "<keyword> else </keyword>\n");
		advance();
		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
		compileStatements();

		if(TokenPutback==0)
			advance();
		else
			TokenPutback=0;

		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	}
	else {

		TokenPutback = 1;
	}

	fprintf(Outfile, "</ifStatement>\n");

	
}

void compileReturn() {

	fprintf(Outfile, "<returnStatement>\n");
	fprintf(Outfile, "<keyword> return </keyword>\n");
	advance();

	if(CurrToken.tokentype == SYMBOL) {
		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	}
	else {
		
		TokenPutback = 1;
		CompileExpression();
		if(TokenPutback==0)
			advance();
		else
			TokenPutback=0;
		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	}

	fprintf(Outfile, "</returnStatement>\n");
}

void compileStatements() {

	fprintf(Outfile, "<statements>\n");
	struct Token current;

	if(TokenPutback) {

		TokenPutback = 0;
		current = CurrToken;
	}
	else {

		advance();
		current = CurrToken;
	}

	while(current.tokentype == KEYWORD && 
		(strcmp(current.keyword, "let") == 0 || strcmp(current.keyword, "if") == 0 || strcmp(current.keyword, "while") == 0 || 
		strcmp(current.keyword, "do") == 0 || strcmp(current.keyword, "return") == 0)) {

		if(strcmp(current.keyword, "let") == 0) {

			compileLet();

		}
		else if(strcmp(current.keyword, "if") == 0) {

			compileIf();
		}
		else if(strcmp(current.keyword, "while") == 0) {

			compileWhile();
		}
		else if(strcmp(current.keyword, "do") == 0) {

			compileDo();
		}
		else if(strcmp(current.keyword, "return") == 0) {

			compileReturn();
		}
		
		if(TokenPutback==0)
			advance();
		else
			TokenPutback=0;
		current = CurrToken;
	}

	fprintf(Outfile, "</statements>\n");
	TokenPutback = 1;

}

void compileVarDec() {

	fprintf(Outfile, "<varDec>\n");
	fprintf(Outfile, "<keyword> var </keyword>\n");

	advance();

	if(CurrToken.tokentype == KEYWORD)
		fprintf(Outfile, "<keyword> %s </keyword>\n", CurrToken.keyword);
	else
		fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);

	advance();

	while(CurrToken.tokentype == IDENTIFIER)
	{
		fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);

		advance();

		if(CurrToken.tokentype == SYMBOL && CurrToken.symbol == ',') {

			fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
			advance();
		}
		else if(CurrToken.symbol == ';') {

			fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
			advance();
			TokenPutback = 1;
			break;
		}
		
	}

	fprintf(Outfile, "</varDec>\n");

}

void compileParameterList() {

	fprintf(Outfile, "<parameterList>\n");

	if(TokenPutback==0)
		advance();
	else
		TokenPutback=0;

	while(CurrToken.tokentype == KEYWORD) {

		fprintf(Outfile, "<keyword> %s </keyword>\n", CurrToken.keyword);
		advance();
		fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);
		advance();

		if(CurrToken.tokentype == SYMBOL && CurrToken.symbol == ',') {

			fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
			advance();
		}
		else {

			TokenPutback = 1;
			break;

		}
	}
	TokenPutback=1;
	fprintf(Outfile, "</parameterList>\n");
}


void CompileSubroutine() {

	fprintf(Outfile, "<subroutineDec>\n");

	if(TokenPutback = 0)
		advance();
	else
		TokenPutback = 0;

	fprintf(Outfile, "<keyword> %s </keyword>\n", CurrToken.keyword);
	advance();
	if(CurrToken.tokentype == KEYWORD)
		fprintf(Outfile, "<keyword> %s </keyword>\n", CurrToken.keyword);
	else
		fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);

	advance();

	fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);

	advance();
	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	
	advance();
	if(CurrToken.tokentype != SYMBOL) {

		TokenPutback=1;
		compileParameterList();
		if(TokenPutback == 0)
			advance();
		else
			TokenPutback = 0;
	}
	else
	{
		fprintf(Outfile, "<parameterList>\n");
		fprintf(Outfile, "</parameterList>\n");
	}

	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

	fprintf(Outfile, "<subroutineBody>\n");

	advance();

	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

	advance();

	if(CurrToken.tokentype == KEYWORD && strcmp(CurrToken.keyword,"var") == 0) {

		while(strcmp(CurrToken.keyword, "var") == 0) {

			compileVarDec();

		}

		TokenPutback = 1;
	}
	else {

		TokenPutback = 1;
	}

	compileStatements();

	if(TokenPutback = 0)
		advance();
	else
		TokenPutback = 0;

	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	fprintf(Outfile, "</subroutineBody>\n");
	fprintf(Outfile, "</subroutineDec>\n");

}

void CompileClassVarDec() {

	fprintf(Outfile, "<classVarDec>\n");

	if(TokenPutback = 0)
		advance();
	else
		TokenPutback = 0;

	fprintf(Outfile, "<keyword> %s </keyword>\n", CurrToken.keyword);

	advance();

	if(CurrToken.tokentype == KEYWORD)
		fprintf(Outfile, "<keyword> %s </keyword>\n", CurrToken.keyword);
	else
		fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);

	advance();

	while(CurrToken.tokentype == IDENTIFIER) {

		fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);

		advance();

		if(CurrToken.tokentype == SYMBOL && CurrToken.symbol == ',') {

			fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
			advance();
		}
		else {

			fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
		}
	}

	fprintf(Outfile, "</classVarDec>\n");
}

void CompileClass() {

	fprintf(Outfile, "<class>\n");
	if(TokenPutback == 0)
		advance();
	else
		TokenPutback = 0;

	fprintf(Outfile, "<keyword> %s </keyword>\n", CurrToken.keyword);
	advance();
	fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);
	advance();
	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

	advance();

	while(CurrToken.tokentype == KEYWORD && (strcmp(CurrToken.keyword,"static") == 0 || strcmp(CurrToken.keyword,"field") == 0)) {

		CompileClassVarDec();
		if(TokenPutback == 0)
			advance();
		else
			TokenPutback = 0;
	}

	while(CurrToken.tokentype == KEYWORD || CurrToken.tokentype == IDENTIFIER) {

		CompileSubroutine();

		if(TokenPutback == 0)
			advance();
		else
			TokenPutback = 0;
	}
	
	fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	fprintf(Outfile, "</class>\n");

}

void CompileExpression() {
	fprintf(Outfile, "<expression>\n");

	CompileTerm();
	if(TokenPutback==0)
		advance();
	else
		TokenPutback = 0;

	while(CurrToken.tokentype == SYMBOL && (CurrToken.symbol=='+' || CurrToken.symbol=='-'
			|| CurrToken.symbol=='*' || CurrToken.symbol=='/' || CurrToken.symbol=='&'
			|| CurrToken.symbol=='|' || CurrToken.symbol=='<' || CurrToken.symbol=='>'
			|| CurrToken.symbol=='=')) {

		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

		CompileTerm();

		if(TokenPutback==0)
			advance();
		else
			TokenPutback=0;
	}

	TokenPutback = 1;

	fprintf(Outfile, "</expression>\n");

}

void CompileTerm() {

	fprintf(Outfile, "<term>\n");

	if(TokenPutback == 0)
		advance();
	else
		TokenPutback = 0;

	if(CurrToken.tokentype == SYMBOL && CurrToken.symbol == '(') {

		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
		CompileExpression();

		if(TokenPutback == 0)
			advance();
		else
			TokenPutback = 0;

		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
	}
	else if(CurrToken.tokentype == STRING_CONST) {

		fprintf(Outfile, "<stringConstant> %s </stringConstant>\n", CurrToken.stringval);
	}
	else if(CurrToken.tokentype == KEYWORD) {

		fprintf(Outfile, "<keyword> %s </keyword>\n", CurrToken.keyword);
	}
	else if(CurrToken.tokentype == INT_CONST) {

		fprintf(Outfile, "<integerConstant> %d </integerConstant>\n", CurrToken.intval);
	}
	else if(CurrToken.tokentype == IDENTIFIER) {

		fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);
		struct Token current = CurrToken;

		advance();

		if(CurrToken.tokentype == SYMBOL && (CurrToken.symbol == '[' || CurrToken.symbol == '('
			|| CurrToken.symbol == '.')) {

			fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

			if(CurrToken.symbol == '[') {

				CompileExpression();

				if(TokenPutback == 0)
					advance();
				else
					TokenPutback = 0;

				fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

			}
			else if(CurrToken.symbol == '(') {

				CompileExpressionList();

				if(TokenPutback == 0)
					advance();
				else
					TokenPutback = 0;
				fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

			}
			else if(CurrToken.symbol == '.') {

				advance();
				fprintf(Outfile, "<identifier> %s </identifier>\n", CurrToken.identifier);
				advance();
				fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
				CompileExpressionList();
				
				//TokenPutback should be 1 but is actually 0
				if(TokenPutback == 0)
					advance();
				else
					TokenPutback = 0;

				fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);

			}

		}
		else {

			TokenPutback = 1;
		}

	}
	else if(CurrToken.tokentype == SYMBOL && (CurrToken.symbol == '-' 
			|| CurrToken.symbol == '~')) {

		fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
		CompileTerm();
	}
	else {

		TokenPutback = 1;
	}
	
	fprintf(Outfile, "</term>\n");
}

void CompileExpressionList() {

	fprintf(Outfile, "<expressionList>\n");

	CompileExpression();

	if(TokenPutback == 0)
		advance();
	else
		TokenPutback = 0;

	if(CurrToken.tokentype == SYMBOL && CurrToken.symbol == ',') {

		while(CurrToken.tokentype == SYMBOL && CurrToken.symbol == ',') {

			fprintf(Outfile, "<symbol> %c </symbol>\n", CurrToken.symbol);
			CompileExpression();

			if(TokenPutback == 0)
				advance();
			else 
				TokenPutback = 0;

		}
	}

	TokenPutback = 1;
	
	
	fprintf(Outfile, "</expressionList>\n");
}

void Constructor() {

	CompileClass();
}