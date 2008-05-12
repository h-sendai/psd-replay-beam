#include <stdio.h>
#include <stdlib.h>

extern int data_send_probability;

int may_send(void)
{
	int i, rv;
	double random;
	double upper_limit;

	upper_limit = (double) data_send_probability / 100.0;
	i = rand(); /* i = from 0 to RAND_MAX (2147483647) */
	random = (double) 1 / RAND_MAX * i;
	if (random < upper_limit) {
		rv = 1;
	}
	else {
		rv = 0;
	}
	return rv;
}
