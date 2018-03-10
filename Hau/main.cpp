#include "qint.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	QInt q;
	ScanQInt(q);
	// PrintQInt(q);

	bool *bits = DecToBin(q);
	in_bit(bits, 128);
	char *text = BinToHex(bits);
	printf("Hexa: %s\n", text);
	free(bits);
	free(text);
	int t = -123456;
	printf("%x\n", t);
	return 0;
}