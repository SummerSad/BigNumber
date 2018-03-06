#include "qint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		// 0 + 1 = 1
		bits[127] = 1;
	} else {
		// 1 + 1 = 10
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
		// 1 - 1 = 0
		bits[127] = 0;
	} else {
		// (1)0 - 1 = 1
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

void in128(int bits[128])
{
	for (int i = 0; i < 128; ++i) {
		printf("%d", bits[i]);
	}
	printf("\n");
}

// 101 -> 010
void nghichDao(int bits[128])
{
	for (int i = 0; i < 128; ++i) {
		bits[i] = 1 - bits[i];
	}
}

// am -> duong va nguoc lai (bu 2)
void doiDau(int bits[128])
{
	if (bits[0] == 0) {
		// so duong
		nghichDao(bits);
		cong1(bits);
	} else {
		tru1(bits);
		nghichDao(bits);
	}
}

int laChuSo(char c)
{
	return c >= '0' && c <= '9';
}

int laHopLe(char *num)
{
	if (!num || strlen(num) <= 0)
		return 0;
	int i = 0;
	if (num[i] == '+' || num[i] == '-')
		++i;
	for (; num[i] != '\0'; ++i) {
		if (!laChuSo(num[i]))
			return 0;
	}
	return 1;
}

// luu y sau khi chia 2
// ket qua luon duong
// dau se luu sau
void chia2(char *num)
{
	char *thuong = malloc(sizeof(char) * (strlen(num) + 1));

	int i = 0;
	if (num[i] == '-' || num[i] == '+')
		++i;
	int temp = num[i] - '0';
	if (num[i] == '1') {
		temp = temp * 10 + num[i + 1] - '0';
		++i;
	}

	int j = 0;
	for (; num[i] != '\0'; ++i) {
		thuong[j++] = temp / 2 + '0';
		temp = (temp % 2) * 10 + num[i + 1] - '0';
	}

	strcpy(num, thuong);
	free(thuong);
}