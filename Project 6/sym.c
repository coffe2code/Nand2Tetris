#include "defs.h"
#include "data.h"
#include "decl.h"

static int Globs = 0;

int findglob(char* s) {
	int i;

	for (i=0;i<Globs;i++) {
		if(!strcmp(s, GSym[i].symbol))
			return i;
	}

	return -1;
}

static int newglob(void) {
	int p;

	p = Globs++;

	return p;
}

void addglob(char* name, int value) {

	int y;
	y = newglob();
	GSym[y].symbol = name;
	GSym[y].RamPos = value;
}