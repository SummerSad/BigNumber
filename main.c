#include "qint.h"
#include <stdio.h>

int main()
{
	char num[] = "-100";
	int bits[128];
	strtob128(num, bits);
	in128(bits);
	return 0;
}