#include "xulyfile.h"
#include "qint.h"
#include "share.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **chia_thanh_toan_hang(char *line, int &count);
bool *tinh_toan_2_ngoi(char **str, bool *bits_1, bool *bits_3);

void file_qint(char *input, char *output)
{
	FILE *f_in = fopen(input, "r");
	if (!f_in) {
		printf("Khong ton tai file %s\n", input);
		return;
	}
	FILE *f_out = fopen(output, "w");
	const int MAX = 200;
	char line[MAX];
	while (fgets(line, MAX, f_in)) {
		int count;
		char **str = chia_thanh_toan_hang(line, count);

		// o1 o2 o3 o4
		if (count == 4) {
			bool *bits_1, *bits_3;
			if (strcmp(str[0], "10") == 0) {
				bits_1 = str10_to_bit(str[1], QInt_Size);
				bits_3 = str10_to_bit(str[3], QInt_Size);
			} else if (strcmp(str[0], "2") == 0) {
				bits_1 = str2_to_bit(str[1], QInt_Size);
				bits_3 = str2_to_bit(str[3], QInt_Size);
			} else if (strcmp(str[0], "16") == 0) {
				bits_1 = str16_to_bit(str[1], QInt_Size);
				bits_3 = str16_to_bit(str[3], QInt_Size);
			}

			bool *bits_kq = tinh_toan_2_ngoi(str, bits_1, bits_3);
			char *chars_kq;
			if (strcmp(str[0], "10") == 0) {
				chars_kq = bit_to_str10(bits_kq, QInt_Size);
			} else if (strcmp(str[0], "2") == 0) {
				chars_kq = bit_to_str2(bits_kq, QInt_Size);
			} else if (strcmp(str[0], "16") == 0) {
				chars_kq = bit_to_str16(bits_kq, QInt_Size);
			}

			fprintf(f_out, "%s\n", chars_kq);
			if (bits_1)
				free(bits_1);
			if (bits_3)
				free(bits_3);
			if (bits_kq)
				free(bits_kq);
			if (chars_kq)
				free(chars_kq);
		} else if (count == 3) {
		}

		// free memory
		for (int i = 0; i < count; ++i) {
			free(str[i]);
		}
		if (str)
			free(str);
	}
	fclose(f_in);
	fclose(f_out);
}

char **chia_thanh_toan_hang(char *line, int &count)
{
	// line co dang o1 o2 o3 o4 (2 3 + 5)
	// hoac o1 o2 o3 (2 16 5)
	int len = strlen(line);
	int first_w = 0;
	int space = 0;
	char **str = NULL; // luu o1 o2 ...
	count = 0;	 // luu bao nhieu
	while (space < len) {
		if (isspace(line[space])) {
			str =
			    (char **)realloc(str, sizeof(char *) * (count + 1));
			str[count] = (char *)malloc(sizeof(char) *
						    (space - first_w + 1));
			for (int i = first_w; i < space; ++i) {
				str[count][i - first_w] = line[i];
			}
			str[count][space - first_w] = '\0';
			++count;
			first_w = space + 1;
		}
		++space;
	}
	return str;
}

bool *tinh_toan_2_ngoi(char **str, bool *bits_1, bool *bits_3)
{
	bool *bits_kq;
	if (strcmp(str[2], "+") == 0) {
		bits_kq = cong_bits(bits_1, bits_3, QInt_Size);
	} else if (strcmp(str[2], "-") == 0) {
		bits_kq = tru_bits(bits_1, bits_3, QInt_Size);
	}
	return bits_kq;
}