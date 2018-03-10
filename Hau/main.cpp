#include "qint.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	QInt q;
	ScanQInt(q);
	char *s = DecToHex(q);
	printf("Hexa %s\n", s);
	free(s);
	printf("%x\n", -2123);
	return 0;
}