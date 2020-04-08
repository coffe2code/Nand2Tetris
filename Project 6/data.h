#ifndef extern_
	#define extern_ extern
#endif

extern_ int 				ROM;
extern_ FILE				*Infile;
extern_ struct Command		CurrCommand;
extern_ char 				CurrBinary[17];
extern_ int					isPrimScan;
extern_ int 				CurrRAM;
extern_ struct sym			GSym[1000];