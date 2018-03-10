#include "qint.h"
#include <stdio.h>

int main()
{
	char num[] = "-1999999999999999999999999999999";
	int bits[128];
	str_to_bit(num, bits, 128);
	QInt q = b128_to_QInt(bits);
	in_bit(bits, 128);
	in_QInt(q);

	int test[128];
	QInt_to_b128(q, test);
	in_bit(test, 128);

	printf("%d\n", compare_bit(bits, test, 128));

	bit_to_str(bits, 128);

	return 0;
}