#include "qint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ham phu tro
void cong_1(bool bits[], int size)
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

void tru_1(bool bits[], int size)
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

void in_bit(bool bits[], int size)
{
	for (int i = 0; i < size; ++i) {
		printf("%d", bits[i]);
	}
	printf("\n");
}

// 101 -> 010
void nghichDao(bool bits[], int size)
{
	for (int i = 0; i < size; ++i) {
		bits[i] = 1 - bits[i];
	}
}

// am -> duong va nguoc lai (bu 2)
void doiDau(bool bits[], int size)
{
	if (bits[0] == 0) {
		// so duong
		nghichDao(bits, size);
		cong_1(bits, size);
	} else {
		tru_1(bits, size);
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
void chia_2(char *num)
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

int compare_bit(bool b1[], bool b2[], int size)
{
	for (int i = 0; i < size; ++i) {
		if (b1[i] != b2[i])
			return 0;
	}
	return 1;
}

/* Chuyen input -> QInt
 * cu the, input -> bit[128]
 * bit[128] chia ra 4 block
 * moi block dua ve block cua QInt
 */
void str_to_bit(char *num, bool bits[], int size)
{
	if (!laHopLe(num)) {
		printf("Input khong hop le\n");
		for (int i = 0; i < size; ++i) {
			bits[i] = 0;
		}
		return;
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
		chia_2(temp_num);
	}

	if (laSoAm) {
		doiDau(bits, size);
	}

	free(temp_num);
}

// chuyen 1 block (bu 2) sang so nguyen
int block_to_int(bool bits[], int from, int to)
{
	int size = to - from + 1;
	if (size != 32) {
		printf("Block khong du 32 bit\n");
		return 0;
	}
	bool *temp_bits = (bool *)malloc(sizeof(bool) * size);
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
	free(temp_bits);
	return laSoAm == 0 ? result : -result;
}

/* Chuyen QInt -> input
 * cu the, doi tung block cua QInt -> bit[128]
 * bit[128] -> input (so dang string)
 */
void int_to_block(int x, bool bits[], int from, int to)
{
	int size = to - from + 1;
	if (size != 32) {
		printf("Block khong du 32 bit\n");
		return;
	}
	for (int i = to; i >= from; --i) {
		bits[i] = x & 1;
		x >>= 1;
	}
}

void QInt_to_b128(QInt q, bool bits[128])
{
	for (int i = 0, y = 0; i < 4; ++i, y += 32) {
		int_to_block(q.block[i], bits, y, y + 31);
	}
}

// A = A + B (10-digits, A va B > 0)
void cong_str(char *A, char *B)
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
void nhan_2(char *num)
{
	if (!num || strlen(num) < 1) {
		printf("num khong hop le\n");
		return;
	}
	int d = 0;
	for (int i = strlen(num) - 1; i >= 0; --i) {
		int mult = (num[i] - '0') * 2 + d;
		num[i] = mult % 10 + '0';
		d = mult / 10;
	}
}

/* vi du doi 0101(2) ra 10-digits
 * di tu phai qua trai, cho num = 0
 * so 1 dau tien la 2^0 -> cong vao num
 * so 1 cuoi cung la 2^2 -> cong vao num
 */
void bit_to_str(bool bits[], int size)
{
	if (size > 128) {
		printf("Day bit lon hon 128, bo qua\n");
		return;
	}

	// Kiem tra so am
	bool *temp_bits = (bool *)malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i) {
		temp_bits[i] = bits[i];
	}
	int laSoAm = 0;
	if (temp_bits[0] == 1) {
		laSoAm = 1;
		doiDau(temp_bits, size);
	}

	// 2^10 = 1024 xap xi 10^3, 128 : 3 = 42
	// nen so thap phan khong qua
	// 43 chu so, lay 50 cho chac
	const int max_size = 50;

	// xay dung num="00..01"
	// roi nhan 2 dan dan theo temp_bits[]
	char *num = (char *)malloc(sizeof(char) * (max_size + 1));
	num[max_size] = '\0';
	for (int i = 0; i < max_size; ++i) {
		num[i] = '0';
	}

	// temp_bits[] -> num
	for (int i = 0; i < 128; ++i) {
		if (temp_bits[127 - i] == 1) {
			// lay 2^i
			char *temp =
			    (char *)malloc(sizeof(char) * (max_size + 1));
			temp[max_size] = '\0';
			for (int j = 0; j < max_size - 1; ++j) {
				temp[j] = '0';
			}
			temp[max_size - 1] = '1';
			for (int j = 0; j < i; ++j) {
				nhan_2(temp);
			}
			cong_str(num, temp);
			free(temp);
		}
	}

	// Input
	if (laSoAm)
		printf("-");
	int i = 0;
	while (num[i] == '0') {
		++i;
	}
	if (i == max_size)
		--i;
	printf("%s\n", num + i);
	free(temp_bits);
	free(num);
}

// Nhap xuat theo YEUCAU
void ScanQInt(QInt &q)
{
	const int max_size = 50;
	char num[max_size + 1];
	printf("Nhap so nguyen lon: ");
	scanf("%s", num);
	bool bits[128];
	str_to_bit(num, bits, 128);
	q = BinToDec(bits);
}

void PrintQInt(QInt q)
{
	bool bits[128];
	QInt_to_b128(q, bits);
	printf("Xuat so nguyen lon: ");
	bit_to_str(bits, 128);
}

// Chuyen doi theo YEUCAU, mac dinh bits la 128
bool *DecToBin(QInt q)
{
	bool *bits = (bool *)malloc(sizeof(bool) * 128);
	for (int i = 0, y = 0; i < 4; ++i, y += 32) {
		int_to_block(q.block[i], bits, y, y + 31);
	}
	return bits;
}

QInt BinToDec(bool *bits)
{
	QInt x;
	for (int i = 0, j = 0; i < 4; ++i, j += 32) {
		x.block[i] = block_to_int(bits, j, j + 31);
	}
	return x;
}

int nibble_to_uint(bool bits[], int from, int to)
{
	int size = to - from + 1;
	if (size != 4) {
		printf("Khong phai nibble \n");
		return 0;
	}

	int result = 0;
	for (int i = 0; i < size; ++i) {
		result = result * 2 + bits[i + from];
	}
	return result;
}

char *BinToHex(bool *bits)
{
	// cu 4 bits la 1 chu so hexa
	// 128 : 4 = 32
	// chuyen doi tung nibble (4-bit)
	const int size = 32;
	char *hexas = (char *)malloc(sizeof(char) * (size + 1));
	hexas[size] = '\0';
	char hexa_digit[] = "0123456789ABCDEF";
	for (int i = 0, j = 0; i < size; ++i, j += 4) {
		int d = nibble_to_uint(bits, j, j + 3);
		hexas[i] = hexa_digit[d];
	}
	return hexas;
}

char *DecToHex(QInt q)
{
	bool *temp_bits = DecToBin(q);
	bool bits[128];
	for (int i = 0; i < 128; ++i) {
		bits[i] = temp_bits[i];
	}
	free(temp_bits);
	return BinToHex(bits);
}

/* Xu ly toan tu + - * /
 * tran so cua cong: am + am = duong va duong + duong = am
 * tru la nguoc lai cua cong
 * nhan su dung booth
 */
bool *cong(bool *bits_1, bool *bits_2, int size)
{
	bool laSoAm_1 = 0;
	if (bits_1[0] == 1)
		laSoAm_1 = 1;
	bool laSoAm_2 = 0;
	if (bits_2[0] == 1)
		laSoAm_2 = 1;

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
	if (laSoAm_1 && laSoAm_2) {
		if (tong[0] == 0)
			printf("am + am = duong, tran so\n");
	}
	if (!laSoAm_1 && !laSoAm_2) {
		if (tong[0] == 1)
			printf("duong + duong = am, tran so\n");
	}
	return tong;
}

QInt operator+(QInt a, QInt b)
{
	bool *bits_1 = DecToBin(a);
	bool *bits_2 = DecToBin(b);
	bool *tong = cong(bits_1, bits_2, 128);
	QInt q = BinToDec(tong);
	free(bits_1);
	free(bits_2);
	free(tong);
	return q;
}

QInt operator-(QInt a, QInt b)
{
	// tru la cong voi so doi
	bool *bits_2 = DecToBin(b);
	doiDau(bits_2, 128);
	QInt new_b = BinToDec(bits_2);
	free(bits_2);
	return a + new_b;
}

/* Xu ly toan tu AND (&), OR(|), XOR(^), NOT(~)
 * dich trai(<<) va dich phai(>>)
 */
QInt operator&(QInt a, QInt b)
{
	bool *bits_1 = DecToBin(a);
	bool *bits_2 = DecToBin(b);
	bool *bits_3 = (bool *)malloc(sizeof(bool) * 128);

	for (int i = 0; i < 128; ++i) {
		if (bits_1[i] == 1 && bits_2[i] == 1)
			bits_3[i] = 1;
		else
			bits_3[i] = 0;
	}

	QInt q = BinToDec(bits_3);

	free(bits_1);
	free(bits_2);
	free(bits_3);
	return q;
}

QInt operator|(QInt a, QInt b)
{
	bool *bits_1 = DecToBin(a);
	bool *bits_2 = DecToBin(b);
	bool *bits_3 = (bool *)malloc(sizeof(bool) * 128);

	for (int i = 0; i < 128; ++i) {
		if (bits_1[i] == 0 && bits_2[i] == 0)
			bits_3[i] = 0;
		else
			bits_3[i] = 1;
	}

	QInt q = BinToDec(bits_3);

	free(bits_1);
	free(bits_2);
	free(bits_3);
	return q;
}

QInt operator^(QInt a, QInt b)
{
	bool *bits_1 = DecToBin(a);
	bool *bits_2 = DecToBin(b);
	bool *bits_3 = (bool *)malloc(sizeof(bool) * 128);

	for (int i = 0; i < 128; ++i) {
		if (bits_1[i] == bits_2[i])
			bits_3[i] = 0;
		else
			bits_3[i] = 1;
	}

	QInt q = BinToDec(bits_3);

	free(bits_1);
	free(bits_2);
	free(bits_3);
	return q;
}

QInt operator~(QInt a)
{
	bool *bits_1 = DecToBin(a);
	nghichDao(bits_1, 128);
	QInt q = BinToDec(bits_1);
	free(bits_1);
	return q;
}

// Dich trai luon them so 0
QInt operator<<(QInt a, int count)
{
	bool *bits = DecToBin(a);
	if (count < 1) {
		printf("Dich trai, count < 1\n");
	} else if (count >= 128) {
		for (int i = 0; i < 128; ++i) {
			bits[i] = 0;
		}
	} else {
		for (int i = 0; i < count; ++i) {
			for (int j = 0; j < 127; ++j) {
				bits[j] = bits[j + 1];
			}
			bits[127] = 0;
		}
	}
	QInt q = BinToDec(bits);
	free(bits);
	return q;
}

// Dich phai them so 0 (so duong) hoac 1 (so am)
QInt operator>>(QInt a, int count)
{
	bool *bits = DecToBin(a);
	int laSoAm = 0;
	if (bits[0] == 1)
		laSoAm = 1;
	if (count < 0) {
		printf("Dich phai, count < 1\n");
	} else if (count >= 128) {
		for (int i = 0; i < 128; ++i) {
			bits[i] = laSoAm;
		}
	} else {
		for (int i = 0; i < count; ++i) {
			for (int j = 127; j > 0; --j) {
				bits[j] = bits[j - 1];
			}
			bits[0] = laSoAm;
		}
	}
	QInt q = BinToDec(bits);
	free(bits);
	return q;
}

// Cac ham kiem tra
void test_input_convert()
{
	QInt q;
	ScanQInt(q);
	PrintQInt(q);

	printf("DecToBin\n");
	bool *bits = DecToBin(q);
	in_bit(bits, 128);

	printf("BinToDec\n");
	QInt q_2 = BinToDec(bits);
	PrintQInt(q_2);

	printf("BinToHex\n");
	char *s1 = BinToHex(bits);
	printf("%s\n", s1);
	free(s1);

	printf("DecToHex\n");
	char *s2 = DecToHex(q);
	printf("%s\n", s2);
	free(s2);

	free(bits);
}

void test_cong_tru()
{
	QInt q_1, q_2;
	ScanQInt(q_1);
	ScanQInt(q_2);
	printf("Tong\n");
	QInt q_3 = q_1 + q_2;
	PrintQInt(q_3);
	printf("Hieu\n");
	QInt q_4 = q_1 - q_2;
	PrintQInt(q_4);
}

void test_bit_operator()
{
	QInt q_1, q_2;
	ScanQInt(q_1);
	ScanQInt(q_2);

	printf("AND\n");
	QInt q_3 = q_1 & q_2;
	PrintQInt(q_3);

	printf("OR\n");
	QInt q_4 = q_1 | q_2;
	PrintQInt(q_4);

	printf("XOR\n");
	QInt q_5 = q_1 ^ q_2;
	PrintQInt(q_5);

	printf("NOT\n");
	QInt q_6 = ~q_1;
	QInt q_7 = ~q_2;
	PrintQInt(q_6);
	PrintQInt(q_7);

	printf("Left Shift\n");
	QInt q_8 = q_1 << 1;
	QInt q_9 = q_2 << 2;
	PrintQInt(q_8);
	PrintQInt(q_9);

	printf("Right Shift\n");
	QInt q_10 = q_1 >> 1;
	QInt q_11 = q_2 >> 2;
	PrintQInt(q_10);
	PrintQInt(q_11);
}