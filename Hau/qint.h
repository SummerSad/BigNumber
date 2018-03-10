/* So nguyen lon 128-bit
 * bieu dien tu -2^127 den 2^127 - 1
 * YEAUCAU ham yeu cau tu do an
 * TODO ke hoach can lam
 */
#ifndef QINT_INCLUDED
#define QINT_INCLUDED

struct QInt {
	int block[4];
};

// Ham phu tro
int power_2(int i);
void cong_1(bool bits[], int size);
void tru_1(bool bits[], int size);
void in_bit(bool bits[], int size);
void nghichDao(bool bits[], int size);
void doiDau(bool bits[], int size);
int laChuSo(char c);
int laHopLe(char *num);
void chia_2(char *num);
int compare_bit(bool b1[], bool b2[], int size);

/* Chuyen input -> QInt
 * cu the, input -> bit[128]
 * bit[128] chia ra 4 block
 * moi block dua ve block cua QInt
 */
void str_to_bit(char *num, bool bits[], int size);
int block_to_int(bool bits[], int from, int to);
QInt b128_to_QInt(bool bits[128]);
void in_QInt(QInt x);

/* Chuyen QInt -> input
 * cu the, doi tung block cua QInt -> bit[128]
 * bit[128] -> input (so dang string)
 */
void in_block(bool bits[], int from, int to);
void int_to_block(int x, bool bits[], int from, int to);
void QInt_to_b128(QInt q, bool bits[128]);
// chuyen b128 -> input ban dau
void cong_str(char *A, char *B);
void nhan_2(char *num);
void bit_to_str(bool bits[], int size);

// Nhap xuat theo YEUCAU
void ScanQInt(QInt &q);
void PrintQInt(QInt q);

// Chuyen doi theo YEUCAU, mac dinh bits la 128
bool *DecToBin(QInt q);
QInt BinToDec(bool *bits);
int nibble_to_uint(bool bits[], int from, int to);
char *BinToHex(bool *bits);
char *DecToHex(QInt q);

/* Xu ly toan tu + - * /
 * tran so cua cong: am + am = duong va duong + duong = am
 * tru la nguoc lai cua cong
 * nhan su dung booth
 */
bool *cong(bool *bits_1, bool *bits_2, int size);

// Cac ham kiem tra
void test_input_convert();
void test_cong();

#endif