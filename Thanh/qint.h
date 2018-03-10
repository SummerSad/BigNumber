#ifndef QINT_INCLUDED
#define QINT_INCLUDED

struct QInt {
	int block[4];
};

// Ham phu tro
int power_2(int i);
void cong_1(int bits[], int size);
void tru_1(int bits[], int size);
void in_bit(int bits[], int size);
void nghichDao(int bits[], int size);
void doiDau(int bits[], int size);
int laChuSo(char c);
int laHopLe(char *num);
void chia_2(char *num);
int compare_bit(int b1[], int b2[], int size);

/* Chuyen input -> QInt
 * cu the, input -> bit[128]
 * bit[128] chia ra 4 block
 * moi block dua ve block cua QInt
 */
void str_to_bit(char *num, int bits[], int size);
int block_to_int(int bits[], int from, int to);
QInt b128_to_QInt(int bits[128]);
void in_QInt(QInt x);

/* Chuyen QInt -> input
 * cu the, doi tung block cua QInt -> bit[128]
 * bit[128] -> input (so dang string)
 */
void in_block(int bits[], int from, int to);
void int_to_block(int x, int bits[], int from, int to);
void QInt_to_b128(QInt q, int bits[128]);
// TODO: chuyen b128 -> so dang string

#endif