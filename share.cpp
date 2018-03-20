#include "share.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cong_1_bit(bool *bits, int size)
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

void tru_1_bit(bool *bits, int size)
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

void in_bit(bool *bits, int size)
{
	for (int i = 0; i < size; ++i) {
		printf("%d", bits[i]);
	}
	printf("\n");
}

// 101 -> 010
void nghich_dao_bit(bool *bits, int size)
{
	for (int i = 0; i < size; ++i) {
		bits[i] = 1 - bits[i];
	}
}

// am -> duong va nguoc lai (bu 2)
void doi_dau_bit(bool *bits, int size)
{
	if (bits[0] == 0) {
		// so duong
		nghich_dao_bit(bits, size);
		cong_1_bit(bits, size);
	} else {
		tru_1_bit(bits, size);
		nghich_dao_bit(bits, size);
	}
}

// radix la co so (10, 2, 16)
bool la_chu_so(char c, int radix)
{
	if (radix == 10)
		return c >= '0' && c <= '9';
	if (radix == 2)
		return c == '0' || c == '1';
	if (radix == 16)
		return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
	return 0;
}

// sequences la mot day bit
// chuyen 1 sequence (day bit bu 2) sang so nguyen
int seq_to_int(bool *bits, int from, int to)
{
	int size = to - from + 1;
	if (size != 32) {
		printf("Sequence khong du 32 bit\n");
		return 0;
	}
	bool *temp_bits = (bool *)malloc(sizeof(bool) * size);
	for (int i = 0; i < size; ++i) {
		temp_bits[i] = bits[from + i];
	}
	bool laSoAm = 0;
	if (temp_bits[0] == 1) {
		laSoAm = 1;
		doi_dau_bit(temp_bits, size);
	}
	int result = 0;
	for (int i = 0; i < size; ++i) {
		result = result * 2 + temp_bits[i];
	}
	free(temp_bits);
	return laSoAm == 0 ? result : -result;
}

void int_to_seq(int x, bool *bits, int from, int to)
{
	int size = to - from + 1;
	if (size != 32) {
		printf("Sequence khong du 32 bit\n");
		return;
	}
	for (int i = to; i >= from; --i) {
		bits[i] = x & 1;
		x >>= 1;
	}
}
// Doi ra so nguyen khong dau
int seq_to_uint(bool *bits, int from, int to)
{
	int size = to - from + 1;
	if (size >= 32) {
		return 0;
	}

	int result = 0;
	for (int i = 0; i < size; ++i) {
		result = result * 2 + bits[i + from];
	}
	return result;
}

/* Dich sang trai, phai dung 1 bit
 * Dich trai luon them so 0
 * Dich phai them bit dau tien (0 hoac 1)
 */
void dich_trai_1_bit(bool *bits, int size)
{
	for (int i = 0; i < size - 1; ++i) {
		bits[i] = bits[i + 1];
	}
	bits[size - 1] = 0;
}
void dich_phai_1_bit(bool *bits, int size)
{
	for (int i = size - 1; i > 0; --i) {
		bits[i] = bits[i - 1];
	}
}

// Cong tru 2 bits
bool *cong_bits(bool *bits_1, bool *bits_2, int size)
{
	bool *tong = (bool *)malloc(sizeof(bool) * (size));
	int rememberNumber = 0; // 1 + 1 = 0 remember 1

	for (int i = size - 1; i >= 0; --i) {
		if (rememberNumber == 0) {
			if (bits_1[i] == 1 && bits_2[i] == 1) {
				tong[i] = 0;
				rememberNumber = 1;
			} else {
				if (bits_1[i] == 0 && bits_2[i] == 0)
					tong[i] = 0;
				else
					tong[i] = 1;
			}
		} else {
			if (bits_1[i] == 0 && bits_2[i] == 0) {
				tong[i] = 1;
				rememberNumber = 0;
			} else {
				if (bits_1[i] == 1 && bits_2[i] == 1)
					tong[i] = 1;
				else
					tong[i] = 0;
			}
		}
	}

	return tong;
}

bool *tru_bits(bool *bits_1, bool *bits_2, int size)
{
	// tru la cong voi so doi
	doi_dau_bit(bits_2, size);
	return cong_bits(bits_1, bits_2, size);
}

// str10 "123456" or "-1234"
// A = A + B (10-digits, A va B > 0)
void cong_str10(char *A, char *B)
{
	if (!A || !B || strlen(A) != strlen(B)) {
		printf("A, B khong cung chieu dai\n");
		return;
	}
	int d = 0;
	for (int i = strlen(A) - 1; i >= 0; --i) {
		int sum = A[i] - '0' + B[i] - '0' + d;
		A[i] = sum % 10 + '0';
		d = sum / 10;
	}
}

// num = num * 2 (10-digits, num > 0)
void nhan_2_str10(char *num)
{
	if (!num || strlen(num) < 1) {
		printf("num khong hop le\n");
		return;
	}
	int d = 0;
	for (int i = strlen(num) - 1; i >= 0; --i) {
		int multi = (num[i] - '0') * 2 + d;
		num[i] = multi % 10 + '0';
		d = multi / 10;
	}
}

// so string 10-digits chia 2 (ket qua > 0)
void chia_2_str10(char *num)
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

// Chuyen bit sang chuoi co so 10
char *bit_to_str10(bool *bits, int size)
{
	// Kiem tra so am
	bool *temp_bits = (bool *)malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i) {
		temp_bits[i] = bits[i];
	}
	bool laSoAm = 0;
	if (temp_bits[0] == 1) {
		laSoAm = 1;
		doi_dau_bit(temp_bits, size);
	}

	// 2^10 = 1024 xap xi 10^3,
	// 2^15 xap xi 10^4.5
	const int max_size = (int)((size * 3) / 10) + 1;

	// xay dung num="00..01"
	// roi nhan 2 dan dan theo temp_bits[]
	char *num = (char *)malloc(sizeof(char) * (max_size + 1));
	num[max_size] = '\0';
	for (int i = 0; i < max_size; ++i) {
		num[i] = '0';
	}

	// temp_bits[] -> num
	for (int i = 0; i < size; ++i) {
		if (temp_bits[size - 1 - i] == 1) {
			// lay 2^i
			char *temp =
			    (char *)malloc(sizeof(char) * (max_size + 1));
			temp[max_size] = '\0';

			for (int j = 0; j < max_size - 1; ++j) {
				temp[j] = '0';
			}

			temp[max_size - 1] = '1';
			for (int j = 0; j < i; ++j) {
				nhan_2_str10(temp);
			}
			cong_str10(num, temp);
			free(temp);
		}
	}

	free(temp_bits);
	int i = 0;
	while (num[i] == '0')
		++i;
	if (i == max_size)
		--i;
	int new_size = size - i + laSoAm;
	char *new_num = (char *)malloc(sizeof(char) * (new_size + 1));
	new_num[new_size] = '\0';
	if (laSoAm)
		new_num[0] = '-';
	strcpy(new_num + laSoAm, num + i);
	free(num);
	return new_num;
}