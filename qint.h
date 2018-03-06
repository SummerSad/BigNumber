#ifndef QINT_INCLUDED
#define QINT_INCLUDED

struct QInt {
	int block[4];
};

// Ham phu tro
int power2(int i);
void cong1(int bits[128]);
void tru1(int bits[128]);
void in128(int bits[128]);
void nghichDao(int bits[128]);
void doiDau(int bits[128]);
int laChuSo(char c);
int laHopLe(char *num);
void chia2(char *num);

#endif