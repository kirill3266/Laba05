#include <stdio.h>
#include <stdlib.h>
#define N 10

void preBmBc(char* str, int substrl, int* d) {
	int i;
	for (i = 0; i < 256; ++i) {
		d[i] = substrl;
	}
	for (i = 0; i < substrl - 1; ++i)
		d[str[i]] = substrl - 1 - i;
}

int strlength(char* str) {
	int i = 0;
	for (i = 0; str[i] != '\n'&&str[i]!=0; i++);
	return i;
}

int strlen1(int* str) {
	int i = 0;
	for (i = 0; str[i] != 0; i++);
	return i;
}

void boyerMoore(char* str, char* substr,int *mas, int* boo) {
	int substrl = strlength(substr);
	int d[256];
	int c=0;
	preBmBc(substr, substrl, d);
	for (int i = 0; i < (1000 - substrl) && str[i] != '\n'&&str[i]!=0;) {
		int flag = 1;
		for (int j = 0; substr[j] != '\n'&&substr[j]!=0; ++j) {
			if ((str[i + j] != substr[j]) || (i + j > 999)) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			if (*boo == 0) *boo = 1;
			mas[c] = i;
			c++;
		}
		if ((i + substrl) >= strlength(str))			
			break;
		i += d[str[i + substrl - 1]];
	}
}

void func(char* str, int strl, int substrl, int* mas, int b, int* boo) {
	printf("Boo= %d\n", *boo);
	int j = 0;//index of out
	int n = 0;//index of mas
	char* out = (char*)malloc(strl * sizeof(char));
	for (int j = 0; j < strl; j++) out[j] = 0;
	for (int i = 0; i < strl; i++) {
		if (i == mas[n] && strlen1(mas)>0) {
			switch (b) {
			case 0: out[j] = '0';
				break;
			case 1: out[j] = '1';
				break;
			case 2: out[j] = '2';
				break;
			case 3: out[j] = '3';
				break;
			case 4: out[j] = '4';
				break;
			case 5: out[j] = '5';
				break;
			case 6: out[j] = '6';
				break;
			case 7: out[j] = '7';
				break;
			case 8: out[j] = '8';
				break;
			case 9: out[j] = '9';
				break;
			}
			i += substrl - 1;
			n++;
			j++;
		}
		else if (*boo == 1&&i==mas[n]) {
			out[j] = (char)(b + 48);
			i += substrl-1;
			n++;
			j++;
		}
		else {
			out[j] = str[i];
			j++;
		}
	}
	for (int i = 0; str[i] != 0; i++) {
		if (out[i] == 0) str[i] = 0;
		else
			str[i] = out[i];
	}
	free(out);
}

int main() {

	char str[1000];
	char* x[N] = { 0 };

	printf("Vvedite stroku:");
	fgets(str, 1000, stdin);

	int strl = strlength(str);

	char substr0[] = "zero";
	x[0] = substr0;
	char substr1[] = "one";
	x[1] = substr1;
	char substr2[] = "two";
	x[2] = substr2;
	char substr3[] = "three";
	x[3] = substr3;
	char substr4[] = "four";
	x[4] = substr4;
	char substr5[] = "five";
	x[5] = substr5;
	char substr6[] = "six";
	x[6] = substr6;
	char substr7[] = "seven";
	x[7] = substr7;
	char substr8[] = "eight";
	x[8] = substr8;
	char substr9[] = "nine";
	x[9] = substr9;

	int* mas = (int*)malloc(strl*sizeof(int));
	int boo = 0;
	for (int i = 0; i < N; i++) {
		int substrl = strlength(x[i]);
		for (int j = 0; j < strl; j++) {
			mas[j] = 0;
		}
		boyerMoore(str, x[i], mas, &boo);
		func(str, strl, substrl, mas, i,&boo);
		boo = 0;
	}

	for (int i = 0; i < strl; i++) {
		printf("%c", str[i]);
	}
	free(mas);
	return 0;
}