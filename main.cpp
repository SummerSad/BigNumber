#include "qint.h"
#include <stdio.h>

int main()
{
	char num[] = "-100";
	int bits[128];
	strtobit(num, bits, 128);
	inbit(bits, 128);
	QInt x = b128toQInt(bits);
	inQInt(x);
	return 0;
}