#ifndef QINT_INCLUDED
#define QINT_INCLUDED

struct QInt {
	int block[4];
};

// Ham phu tro
int power2(int i);
void cong1(int bits[], int size);
void tru1(int bits[], int size);
void inbit(int bits[], int size);
void nghichDao(int bits[], int size);
void doiDau(int bits[], int size);
int laChuSo(char c);
int laHopLe(char *num);
void chia2(char *num);
void strtobit(char *num, int bits[], int size);
int blocktoint(int bits[], int from, int to);
QInt b128toQInt(int bits[128]);

#endif