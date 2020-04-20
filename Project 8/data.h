#ifndef extern_
	#define extern_ extern
#endif

extern_ FILE				*Infile;
extern_ FILE				*Outfile;
extern_ struct Command		CurrCommand;
extern_ char 				CurrBinary[17];
extern_ int 				CurrFlag;
extern_ int 				CurrReturn;
extern_ int 				isEOFTrig;
extern_ int 				isFunc;
extern_ char				functionName[100];