#include "qfloat.h"
#include "share.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int la_hop_le_Qfloat(char *num, int radix);

bool *lay_Phan_ThapPhan_BD(char *num);
bool *lay_Phan_ThapPhan(int so_mu_int, bool *bits_nguyen,
			bool *bits_thapphan_BD);
bool *lay_Phan_Nguyen(char *num);
int lay_So_Mu_INT(bool *bits_nguyen, bool *bits_thapphan_BD);

void int_to_bi(int x, bool *bits, int bits_size);
bool *int_to_biased(int so_mu_int);
bool *bits_so_cham_dong(bool laSoAm, bool *so_mu_biased, bool *bits_thapphan);
bool *float_str10_to_bit(char *num);

bool *biased_to_bits(bool *biased, int size);
char *chuyen_so_mu_biased(bool *bits);
char *chuyen_thaphan_bits(bool *bits);
char *chuyen_nguyen_bits(bool *bits, int so_mu);
void chia_2_str10_thapphan(char *num, int size);
int str10_to_int(char *num);
char *Qfloat_bit_to_str10(bool *bits);

bool *lay_Phan_Nguyen(char *num)
{
	// Kiem tra xem ki tu dau tien co phai la dau + or - hay khong?
	int stop_point = 0;
	if (num[stop_point] == '+' || num[stop_point] == '-') {
		++stop_point;
	}

	// Tach dau cham phan nguyen truoc dau '.'
	char *char_nguyen = strtok(num + stop_point, ".");

	// Khoi tao mang bits cho phan nguyen
	bool *bits_phan_nguyen = (bool *)malloc(sizeof(bool) * Qfloat_MAX_STR2);
	for (int i = 0; i < Qfloat_MAX_STR2; ++i) {
		bits_phan_nguyen[i] = 0;
	}

	// chuyen phan nguyen tu char -> bit
	for (int i = Qfloat_MAX_STR2 - 1; i >= stop_point; --i) {
		if ((char_nguyen[strlen(char_nguyen) - 1] - '0') % 2 == 0) {
			bits_phan_nguyen[i] = 0;
		} else {
			bits_phan_nguyen[i] = 1;
		}
		chia_2_str10(char_nguyen);
	}
	return bits_phan_nguyen;
}

// Ham lay phan thap phan ban dau
bool *lay_Phan_ThapPhan_BD(char *num)
{

	// Tach dau cham phan thap phan sau dau '.'
	char *char_thapphan = strtok(num, ".");
	// Lay phan con lai sau dau "."
	char_thapphan = strtok(NULL, ".");

	// Khoi tao mang bits cho phan thap phan
	bool *bits_phan_thapphan =
	    (bool *)malloc(sizeof(bool) * Qfloat_MAX_STR2);

	// Kiem tra xem co chu so sau dau "." hay khong?
	if (char_thapphan == NULL) {
		for (int i = 0; i < Qfloat_MAX_STR2; ++i) {
			bits_phan_thapphan[i] = 0;
		}
		return bits_phan_thapphan;
	}
	// chuyen phan nguyen tu char -> bit
	int d;
	for (int i = 0; i < Qfloat_MAX_STR2; ++i) {

		d = 0;

		for (int j = strlen(char_thapphan) - 1; j >= 0; --j) {
			int multi = (char_thapphan[j] - '0') * 2 + d;
			char_thapphan[j] = multi % 10 + '0';
			d = multi / 10;
		}
		bits_phan_thapphan[i] = d;
	}

	return bits_phan_thapphan;
}

// Kiem tra Qfloat hop le
// -1: khong hop le, 0: co 0 dau cham dot, 1: co 1 dau cham dot
int la_hop_le_Qfloat(char *num, int radix)
{
	if (!num || strlen(num) <= 0)
		return -1;

	int i = 0;
	if (radix == 10) {
		if (num[i] == '+' || num[i] == '-')
			++i;
	}

	int count_dot = 0;
	for (; num[i] != '\0'; ++i) {
		if (num[i] == '.')
			++count_dot;
		else if (!la_chu_so(num[i], radix) || count_dot > 1)
			return -1;
	}
	if (count_dot == 0) {
		return 0;
	}
	return 1;
}

int lay_So_Mu_INT(bool *bits_nguyen, bool *bits_thapphan_BD)
{
	// Tim vi tri 1. trong bits_nguyen
	int dot = 0;
	for (; bits_nguyen[dot] != 1 && dot < Qfloat_MAX_STR2; ++dot) {
	}
	// Xet bits_nguyen co toan = 0 hay khong?
	if (dot == Qfloat_MAX_STR2) {
		dot = 1;
		// Tim vi tri 1. trong bits_thaphan. Qfloat_MAX_STR2 -2 vì khong
		// the chua qua -Qfloat_MAX_STR2-1
		for (int j = 0;
		     bits_thapphan_BD[j] != 1 && j < Qfloat_MAX_STR2 - 2;
		     ++dot, ++j) {
		}
		return -dot;
	}

	return Qfloat_MAX_STR2 - dot - 1;
}

// Lay ra phan thap phan that su
bool *lay_Phan_ThapPhan(int so_mu_int, bool *bits_nguyen,
			bool *bits_thapphan_BD)
{
	bool *bits_thaphan =
	    (bool *)malloc(sizeof(bool *) * Qfloat_Bits_ThapPhan);
	for (int i = 0; i < Qfloat_Bits_ThapPhan; ++i) {
		bits_thaphan[i] = 0;
	}

	if (so_mu_int == 0) {
		memcpy(bits_thaphan, bits_thapphan_BD, Qfloat_Bits_ThapPhan);
	} else if (so_mu_int > 0) {
		int i = 0;
		int j = Qfloat_MAX_STR2 - so_mu_int;
		// Copy bits sau 1. trong phan nguyen
		for (; j < Qfloat_MAX_STR2 && i < Qfloat_Bits_ThapPhan; ++j) {
			bits_thaphan[i++] = bits_nguyen[j];
		}
		// Copy bits trong phan thap phan ban dau. Phan du cua phan thap
		// phan ban dau sau do khong su dung
		j = 0;
		for (; i < Qfloat_Bits_ThapPhan; ++i) {
			bits_thaphan[i] = bits_thapphan_BD[j++];
		}
	} else {
		// so_mu_int < 0

		int i = 0;
		int j = -so_mu_int;
		// Copy bits sau 1. trong phan thap phan
		for (; j < Qfloat_Bits_ThapPhan; ++j) {
			bits_thaphan[i++] = bits_thapphan_BD[j];
		}
	}
	return bits_thaphan;
}

// Chuyen int qua binary
void int_to_bi(int x, bool *bits, int bits_size)
{
	for (int i = bits_size - 1; i >= 0; --i) {
		bits[i] = x & 1;
		x >>= 1;
	}
}

// chuyen int qua biased
bool *int_to_biased(int so_mu_int)
{
	bool *biased = (bool *)malloc(sizeof(bool) * Qfloat_Bits_Mu);

	// Dua so_mu_int ve binary
	bool *int_bi = (bool *)malloc(sizeof(bool) * Qfloat_Bits_Mu);
	int_to_bi(so_mu_int, int_bi, Qfloat_Bits_Mu);
	// Thiet lap so 0 biased
	bool *biased_0 = (bool *)malloc(sizeof(bool) * Qfloat_Bits_Mu);
	biased_0[0] = 0;
	for (int i = 1; i < Qfloat_Bits_Mu; ++i) {
		biased_0[i] = 1;
	}

	biased = cong_bits(int_bi, biased_0, Qfloat_Bits_Mu);

	free(biased_0);
	free(int_bi);
	return biased;
}

// Thiet lap day bits so cham dong
bool *bits_so_cham_dong(bool laSoAm, bool *so_mu_biased, bool *bits_thapphan)
{
	bool *bits_qfloat = (bool *)malloc(sizeof(bool) * Qfloat_bits_size);
	// gan so am
	bits_qfloat[Qfloat_bits_size - 1] = laSoAm;
	// Gan phan thap phan
	int i = 0;
	for (; i < Qfloat_Bits_ThapPhan; ++i) {
		bits_qfloat[i] = bits_thapphan[i];
	}
	// gan phan mu biased
	int j = 0;
	for (; i < Qfloat_bits_size - 1; ++i) {
		bits_qfloat[i] = so_mu_biased[j++];
	}
	return bits_qfloat;
}

// Chuyen chuoi float 10 sang bits
bool *float_str10_to_bit(char *num)
{
	int dot = la_hop_le_Qfloat(num, 10);
	if (dot == -1) {
		printf("Input khong hop le\n");
		return NULL;
	}

	bool laSoAm = 0;
	if (num[0] == '-') {
		laSoAm = 1;
	}

	char temp[Qfloat_MAX_STR10];
	strcpy(temp, num);

	// Phan nguyen cua so nguyen nhap vao
	bool *bits_nguyen = lay_Phan_Nguyen(temp);

	strcpy(temp, num);
	// Phan thap phan cua so nguyen nhap vao
	bool *bits_thapphan_BD = lay_Phan_ThapPhan_BD(temp);

	int so_mu_int = lay_So_Mu_INT(bits_nguyen, bits_thapphan_BD);

	// Phan thap phan that su dang chuan
	bool *bits_thapphan =
	    lay_Phan_ThapPhan(so_mu_int, bits_nguyen, bits_thapphan_BD);

	free(bits_nguyen);
	free(bits_thapphan_BD);

	bool *so_mu_biased = int_to_biased(so_mu_int);

	bool *qfloat_bits =
	    bits_so_cham_dong(laSoAm, so_mu_biased, bits_thapphan);

	free(so_mu_biased);
	free(bits_thapphan);

	return qfloat_bits;
}

Qfloat BinToDec_float(bool *bits)
{
	Qfloat x;
	for (int i = 0, j = 0; i < 4; ++i, j += 32) {
		x.block[i] = seq_to_int(bits, j, j + 31);
	}
	return x;
}

void ScanQfloat(Qfloat &x)
{
	char num[Qfloat_MAX_STR10];

	printf("Nhap so thuc lon: ");
	scanf("%s", num);

	bool *qfloat_bits = float_str10_to_bit(num);

	if (qfloat_bits != NULL)
		x = BinToDec_float(qfloat_bits);

	free(qfloat_bits);
}

// Chuyen doi theo YEUCAU, mac dinh bits la 128
bool *DecToBin_float(Qfloat q)
{
	bool *bits = (bool *)malloc(sizeof(bool) * Qfloat_bits_size);
	for (int i = 0, y = 0; i < 4; ++i, y += 32) {
		int_to_seq(q.block[i], bits, y, y + 31);
	}
	return bits;
}

// Chuyen so biased sang bits so bu 2
bool *biased_to_bits(bool *biased, int size)
{
	bool *bits = (bool *)malloc(sizeof(bool) * size);
	// Thiet lap so 0 biased
	bool *biased_0 = (bool *)malloc(sizeof(bool) * size);
	biased_0[0] = 0;
	for (int i = 1; i < size; ++i) {
		biased_0[i] = 1;
	}

	bits = tru_bits(biased, biased_0, size);

	free(biased_0);
	return bits;
}

// Chuyen so mu tu biased sang chuoi co so 10
char *chuyen_so_mu_tu_biased(bool *bits)
{
	// So so mu biased
	bool *so_mu_biased = (bool *)malloc(sizeof(bool) * Qfloat_Bits_Mu);
	int j = 0;
	for (int i = Qfloat_Bits_ThapPhan;
	     i < Qfloat_Bits_ThapPhan + Qfloat_Bits_Mu; ++i) {
		so_mu_biased[j++] = bits[i];
	}

	// chuyen so mu biased thanh so mu bits so bu 2
	bool *so_mu_bits = biased_to_bits(so_mu_biased, Qfloat_Bits_Mu);

	// chuyen so mu bits so bu 2 thanh char* co so 10
	char *so_mu_char = bit_to_str10(so_mu_bits, Qfloat_Bits_Mu);

	free(so_mu_biased);
	free(so_mu_bits);

	return so_mu_char;
}

// Chuyen thap phan bits sang chuoi co so 10
char *chuyen_thaphan_bits(bool *bits, int so_mu)
{
	// Khoi tao phan thap phan
	bool *bits_thapphan =
	    (bool *)malloc(sizeof(bool) * Qfloat_Bits_ThapPhan);
	for (int i = 0; i < Qfloat_Bits_ThapPhan; ++i) {
		bits_thapphan[i] = 0;
	}
	// Kiem tra so_mu de dich bits
	if (so_mu > 0) {
		int j = 0;
		// Lay bits thap phan sau khi dich qua trai so_mu bits
		for (int i = so_mu; i < Qfloat_Bits_ThapPhan; ++i) {
			bits_thapphan[j++] = bits[i];
		}
	} else if (so_mu < 0) {
		int i = -so_mu;
		bits_thapphan[i - 1] = 1;
		int j = 0;
		for (; i < Qfloat_Bits_ThapPhan; ++i) {
			bits_thapphan[i] = bits[j++];
		}
	} else {
		// Lay toan bo bits thap phan khi so_mu == 0
		for (int i = 0; i < Qfloat_Bits_ThapPhan; ++i) {
			bits_thapphan[i] = bits[i];
		}
	}

	int max_size = (int)((Qfloat_Bits_ThapPhan * 3) / 10) + 1;
	// Tao chuoi thap phan str 10
	char *thapphan_str10 = (char *)malloc(sizeof(char) * max_size + 1);
	thapphan_str10[max_size] = '\0';
	for (int i = 0; i < max_size; ++i) {
		thapphan_str10[i] = '0';
	}

	for (int i = 0; i < Qfloat_Bits_ThapPhan; ++i) {
		if (bits_thapphan[i] == 1) {
			// lay 2^(-i)
			char *temp =
			    (char *)malloc(sizeof(char) * max_size + 1);
			temp[max_size] = '\0';

			temp[0] = '5';
			for (int j = 1; j < max_size; ++j) {
				temp[j] = '0';
			}

			for (int j = 0; j < i; ++j) {
				chia_2_str10_thapphan(temp, max_size);
			}

			cong_str10(thapphan_str10, temp);
			free(temp);
		}
	}
	free(bits_thapphan);
	return thapphan_str10;
}

// Chuyen phan nguyen bits sang chuoi co so 10
char *chuyen_nguyen_bits(bool *bits, int so_mu)
{
	// Khoi tao phan thap phan
	bool *bits_nguyen = (bool *)malloc(sizeof(bool) * Qfloat_Bits_ThapPhan);
	for (int i = 0; i < Qfloat_Bits_ThapPhan; ++i) {
		bits_nguyen[i] = 0;
	}

	// Kiem tra so_mu de dich bits
	// so_mu < 0 ==> phan nguyen = 0
	if (so_mu > 0) {
		int i = Qfloat_Bits_ThapPhan - so_mu;
		bits_nguyen[i - 1] = 1;

		// Lay bits thap phan sau khi dich qua trai so_mu bits
		int j = 0;
		for (; i < Qfloat_Bits_ThapPhan; ++i) {
			bits_nguyen[i] = bits[j++];
		}

	} else if (so_mu == 0) {
		// Phan_nguyen = 1
		bits_nguyen[Qfloat_Bits_ThapPhan - 1] = 1;
	}

	// Tao chuoi thap phan str 10
	char *nguyen_str10 = bit_to_str10(bits_nguyen, Qfloat_Bits_ThapPhan);

	free(bits_nguyen);
	return nguyen_str10;
}

void chia_2_str10_thapphan(char *num, int size)
{
	char *thuong = (char *)malloc(sizeof(char) * size + 1);
	thuong[size] = '\0';
	for (int k = 0; k < size; ++k) {
		thuong[k] = '0';
	}
	// index mang num
	int i = 0;
	if (num[i] == '-' || num[i] == '+')
		++i;

	// Tim so chu so != 0 dau tien trong day thap phan num
	for (; num[i] == '0'; ++i) {
	}

	int temp = num[i] - '0';
	// index mang thuong
	int j = i;

	if (num[i] - '0' < 2) {
		if (num[i + 1] == '\0') {
			strcpy(num, "0");
			free(thuong);
			return;
		}
		temp = temp * 10 + num[i + 1] - '0';
		++i;
		++j;
	}

	for (; num[i] != '\0'; ++i) {
		thuong[j++] = temp / 2 + '0';
		temp = (temp % 2) * 10 + num[i + 1] - '0';
	}
	// So du con lai
	if (temp == 1 && j < size) {
		thuong[j++] = '5';
	}
	strcpy(num, thuong);
	free(thuong);
}

// Chuyen chuoi co so 10 sang so nguyen co so 10
int str10_to_int(char *num)
{
	int laSoAm = 0;
	if (num[0] == '-') {
		++laSoAm;
	}
	int int_num = 0;
	for (int i = laSoAm; num[i] != '\0'; ++i) {
		int_num = int_num * 10 + (num[i] - '0');
	}
	return laSoAm ? -int_num : int_num;
}

// Chuyen Qfloat dang bit sang chuoi co so 10
char *Qfloat_bit_to_str10(bool *bits)
{

	// Kiem tra so am
	int laSoAm = 0;
	if (bits[Qfloat_bits_size - 1] == 1) {
		laSoAm = 1;
	}
	// chuyen so mu thanh char* co so 10
	char *so_mu = chuyen_so_mu_tu_biased(bits);

	int so_mu_int = str10_to_int(so_mu);
	// chuyen so nguyen thanh char* co so 10
	char *phan_nguyen = chuyen_nguyen_bits(bits, so_mu_int);

	// chuyen so thap phan thanh char* co so 10
	char *thap_phan = chuyen_thaphan_bits(bits, so_mu_int);

	bool so_0_thapphan = true;
	for (int i = 0; thap_phan[i] != '\0'; ++i) {
		if (thap_phan[i] != '0') {
			so_0_thapphan = false;
		}
	}

	char *new_num = (char *)malloc(sizeof(char) * Qfloat_MAX_STR10 + 1);
	new_num[Qfloat_MAX_STR10] = '\0';

	if (laSoAm)
		new_num[0] = '-';
	// index mang new_num
	int index = laSoAm;
	// copy phan_nguyen vao mang new_num
	for (int i = 0; phan_nguyen[i] != '\0'; ++i) {
		new_num[index++] = phan_nguyen[i];
	}
	// copy thap_phan vao mang new_num
	if (!so_0_thapphan) {
		new_num[index++] = '.';
		for (int i = 0; thap_phan[i] != '\0'; ++i) {
			new_num[index++] = thap_phan[i];
		}
	}
	new_num[index] = '\0';

	free(so_mu);
	free(phan_nguyen);
	free(thap_phan);
	return new_num;
}

void PrintQfloat(Qfloat q)
{

	printf("Xuat so thuc lon: ");
	// Xet so 0
	bool laSo0 = true;
	for (int i = 0; i < 3; ++i) {
		if (q.block[i] != 0) {
			laSo0 = false;
		}
	}
	if (laSo0 && (q.block[3] == 0 || q.block[3] == 1)) {
		printf("0");
	} else {
		bool *bits = DecToBin_float(q);
		char *str10 = Qfloat_bit_to_str10(bits);
		printf("%s", str10);
		free(bits);
		free(str10);
	}
}

void testScanQfloat()
{
	printf("Test input output\n");
	Qfloat q;
	ScanQfloat(q);
	PrintQfloat(q);
}