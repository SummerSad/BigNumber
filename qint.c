#include "qint.h"
#include <stdio.h>

// Ham phu tro
int power2(int i)
{
	if (i == 0) {
		return 1;
	}
	if (i < 0) {
		printf("Don't deal with i < 0\n");
	}
	if (i >= 31) {
		// int range is -2^31 ... 2^31-1
		printf("2^31 or more is too big\n");
		return 0;
	}
	return 2 * power2(i - 1);
}

void cong1(int bits[128])
{
	if (bits[127] == 0) {
		bits[127] = 1;
	} else {
		bits[127] = 0;
		int d = 1;
		for (int i = 126; i >= 0; --i) {
			if (d == 0)
				break;
			if (bits[i] == 0) {
				bits[i] = 1;
				d = 0;
			} else {
				bits[i] = 0;
			}
		}
	}
}

void tru1(int bits[128])
{
	if (bits[127] == 1) {
		bits[127] = 0;
	} else {
		bits[127] = 1;
		int d = 1;
		for (int i = 126; i >= 0; --i) {
			if (d == 0)
				break;
			if (bits[i] == 1) {
				bits[i] = 0;
				d = 0;
			} else {
				bits[i] = 1;
			}
		}
	}
}

void in(int bits[128])
{
	for (int i = 0; i < 128; ++i) {
		printf("%d", bits[i]);
	}
	printf("\n");
}