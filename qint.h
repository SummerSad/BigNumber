#ifndef QINT_INCLUDED
#define QINT_INCLUDED

struct QInt {
	int block[4];
};

// Ham phu tro
int power2(int i);
void cong1(int bits[128]);
void tru1(int bits[128]);
void in(int bits[128]);

#endif