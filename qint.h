/* So nguyen lon 128-bit
 * bieu dien tu -2^127 den 2^127 - 1
 * YEUCAU ham yeu cau tu do an
 * TODO ke hoach can lam
 * "If it ain't broke, don't fix it"
 */
#ifndef QINT_INCLUDED
#define QINT_INCLUDED

struct QInt {
	int block[4];
};

const int QInt_Size = 128;

// Ham phu tro
void cong_1_bit(bool *bits, int size);
void tru_1_bit(bool *bits, int size);
void in_bit(bool *bits, int size);
void nghich_dao_bit(bool *bits, int size);
void doi_dau_bit(bool *bits, int size);
bool la_chu_so(char c, int radix);
bool la_hop_le_QInt(char *num, int radix);

/* Chuyen input -> QInt
 * cu the, input -> bit[128]
 * bit[128] chia ra 4 sequence dai 32 bit
 * moi sequence la mot block cua QInt
 */
int seq_to_int(bool *bits, int from, int to);
void chia_2_str10(char *num);
bool *str10_to_bit(char *num);
// TODO chuyen string dang 2-digits va 16-digits ve bit[128]
bool *str2_to_bit(char *num);
bool *str16_to_bit(char *num);

/* Chuyen QInt -> input
 * cu the, doi tung block cua QInt ve sequence dai 32 bit
 * gop 4 sequence -> bit[128]
 * bit[128] -> input (so dang string)
 */
void int_to_seq(int x, bool *bits, int from, int to);
void cong_str10(char *A, char *B);
void nhan_2_str10(char *num);
char *bit_to_str10(bool *bits, int size);
// TODO chuyen bit ve dang string 2-digits
char *bit_to_str2(bool *bit, int size);

// YEUCAU: Nhap xuat
void ScanQInt(QInt &q);
void PrintQInt(QInt q);

// YEUCAU: Chuyen doi, mac dinh bits la 128
bool *DecToBin(QInt q);
QInt BinToDec(bool *bits);
int seq_to_uint(bool *bits, int from, int to);
char *BinToHex(bool *bits);
char *DecToHex(QInt q);

/* YEUCAU: Xu ly toan tu + - * /
 * tran so cua cong: am + am = duong va duong + duong = am
 * tru la nguoc lai cua cong
 * nhan su dung booth
 */
QInt operator+(QInt a, QInt b);
QInt operator-(QInt a, QInt b);
QInt operator*(QInt a, QInt M);
QInt operator/(QInt Q, QInt M);

/* YEUCAUL Xu ly toan tu AND (&), OR(|), XOR(^), NOT(~)
 * dich trai va dich phai
 */
QInt operator&(QInt a, QInt b);
QInt operator|(QInt a, QInt b);
QInt operator^(QInt a, QInt b);
QInt operator~(QInt a);
void dich_trai_1_bit(bool *bits, int size);
void dich_phai_1_bit(bool *bits, int size);
QInt operator<<(QInt a, int count);
QInt operator>>(QInt a, int count);

// Cac ham kiem tra
void test_input_convert();
void test_cong_tru();
void test_nhan_chia();
void test_bit_operator();

#endif
