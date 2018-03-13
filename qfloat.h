/* So cham dong lon 128-bit
 * YEUCAU ham yeu cau tu do an
 * TODO ke hoach can lam
 * "If it ain't broke, don't fix it"
 */

struct Qfloat {
	int block[4];
};

// YEUCAU: Nhap xuat
void ScanQfloat(Qfloat &x);
void PrintQfloat(Qfloat x);

// YEUCAU: Chuyen doi, mac dinh bits la 128
Qfloat BinToDec(bool *bit);
bool *DecToBin(Qfloat x);
