#include "hf2.h"
#include <iostream>
#include <math.h>

using namespace std;

extern bool pr;

double hf2(char* pass, int pass_length)
{
	double hps;
	int j;
	hps = 0;

	for (int i = 0; i < pass_length; i++) {
		j = pass[i] - 96;
		if (pr) cout << "hf2:   pass[" << i << "] = " << pass[i] << " = " << j << endl;
		hps = hps + pow(2,j);
	}
	if (pr) cout << "hf2: (hash for password) hps = " << hps / 1000000 << endl;
	return hps / 1000000;
}