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

void cong1(int bits[], int size)
{
	if (bits[size - 1] == 0) {
		// 0 + 1 = 1
		bits[size - 1] = 1;
	} else {
		// 1 + 1 = 10
		bits[size - 1] = 0;
		int d = 1;
		for (int i = size - 2; i >= 0; --i) {
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

void tru1(int bits[], int size)
{
	if (bits[size - 1] == 1) {
		// 1 - 1 = 0
		bits[size - 1] = 0;
	} else {
		// (1)0 - 1 = 1
		bits[size - 1] = 1;
		int d = 1;
		for (int i = size - 2; i >= 0; --i) {
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

void inbit(int bits[], int size)
{
	for (int i = 0; i < size; ++i) {
		printf("%d", bits[i]);
	}
	printf("\n");
}

// 101 -> 010
void nghichDao(int bits[], int size)
{
	for (int i = 0; i < size; ++i) {
		bits[i] = 1 - bits[i];
	}
}

// am -> duong va nguoc lai (bu 2)
void doiDau(int bits[], int size)
{
	if (bits[0] == 0) {
		// so duong
		nghichDao(bits, size);
		cong1(bits, size);
	} else {
		tru1(bits, size);
		nghichDao(bits, size);
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
	char *thuong = (char *)malloc(sizeof(char) * (strlen(num) + 1));

	int i = 0;
	if (num[i] == '-' || num[i] == '+')
		++i;
	int temp = num[i] - '0';
	if (num[i] - '0' < 2) {
		if (num[i + 1] == '\0') {
			strcpy(num, "0");
			free(thuong);
			return;
		}
		temp = temp * 10 + num[i + 1] - '0';
		++i;
	}

	int j = 0;
	for (; num[i] != '\0'; ++i) {
		thuong[j++] = temp / 2 + '0';
		temp = (temp % 2) * 10 + num[i + 1] - '0';
	}
	thuong[j] = '\0';
	strcpy(num, thuong);
	free(thuong);
}

void strtobit(char *num, int bits[], int size)
{
	if (!laHopLe(num)) {
		printf("Input khong hop le\n");
	}
	char *temp_num = (char *)malloc(sizeof(char) * (strlen(num) + 1));
	temp_num[strlen(num)] = '\0';
	strcpy(temp_num, num);

	int i = 0;
	int laSoAm = 0;
	if (temp_num[i] == '-' || temp_num[i] == '+') {
		if (temp_num[i] == '-') {
			laSoAm = 1;
		}
		++i;
	}

	for (i = 127; i >= 0; --i) {
		if ((temp_num[strlen(temp_num) - 1] - '0') % 2 == 0) {
			bits[i] = 0;
		} else {
			bits[i] = 1;
		}
		chia2(temp_num);
	}

	if (laSoAm) {
		doiDau(bits, size);
	}

	free(temp_num);
}

// chuyen 1 block (bu 2) sang so nguyen
int blocktoint(int bits[], int from, int to)
{
	int size = to - from + 1;
	if (size != 32) {
		printf("Block khong du 32 bit\n");
		return 0;
	}
	int temp_bits[size];
	for (int i = 0; i < size; ++i) {
		temp_bits[i] = bits[from + i];
	}
	int laSoAm = 0;
	if (temp_bits[0] == 1) {
		laSoAm = 1;
		doiDau(temp_bits, size);
	}
	int result = 0;
	for (int i = 0; i < size; ++i) {
		result = result * 2 + temp_bits[i];
	}
	return laSoAm == 0 ? result : -result;
}

QInt b128toQInt(int bits[128])
{
	QInt x;
	for (int i = 0, j = 0; i < 4; ++i, j += 32) {
		x.block[i] = blocktoint(bits, j, j + 31);
	}
	return x;
}

void inQInt(QInt x)
{
	for (int i = 0; i < 4; ++i) {
		printf("%d ", x.block[i]);
	}
	printf("\n");
}