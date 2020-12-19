#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 10


int strlength(char* str) {
	int i = 0;
	for (i = 0; str[i] != '\n' && str[i] != 0; i++);
	return i;
}

int strlen1(int* str) {
	int i = 0;
	for (i = 0; str[i] != 0; i++);
	return i;
}

void poisk(char* str, char* substr, int* mas, int* boo, int n) {
	int c = 0;
	int i=0,j=0,k=0;
	for (i = 0; str[i] != '\n'&&str[i]!=0; i++) {
		for (j = i, k = 0; substr[k] != '\0' && substr[k] != '\n' && str[j] == substr[k];) {
			if (j != 0 && !(str[j-1] == ' ' || str[j-1] == '\n'||str[j-1]=='\t')&&k==0&&substr[k]!=0) { 
				break; 
			}
			else if ((substr[k + 1] == 0 || substr[k + 1] == '\n') && !(str[j + 1] == ' ' || str[j + 1] == '\n' || str[j + 1] == 0||str[j+1]=='\t')) { 
				break; 
			}
			j++;
			k++;
		}
		if (k > 0 && substr[k] == '\0')
		{
			if (*boo == 0) *boo = 1;
			mas[c] = i;
			c++;
			break;
		}
	}
}


void prisv(char* str, int strl, int substrl, int* mas, int b, int* boo) {
	int j = 0;//index of out
	int n = 0;//index of mas
	char* out = (char*)malloc(strl * sizeof(char));
	for (int j = 0; j < strl; j++) out[j] = 0;
	for (int i = 0; i < strl; i++) {
		if (i == mas[n] && strlen1(mas) > 0) {
			switch (b) {
			case 0:
				out[j] = '0';
				break;
			case 1:
				out[j] = '1';
				break;
			case 2:
				out[j] = '2';
				break;
			case 3: 
				out[j] = '3';
				break;
			case 4: 
				out[j] = '4';
				break;
			case 5: 
				out[j] = '5';
				break;
			case 6:
				out[j] = '6';
				break;
			case 7:
				out[j] = '7';
				break;
			case 8:
				out[j] = '8';
				break;
			case 9: 
				out[j] = '9';
				break;
			}
			i += substrl - 1;
			n++;
			j++;
		}
		else if (*boo == 1 && i == mas[n]) {
			out[j] = (char)(b + 48);
			i += substrl - 1;
			n++;
			j++;
		}
		else {
			out[j] = str[i];
			j++;
		}
	}
	for (int i = 0; str[i] != 0&&str[i]!='\n'; i++) {
		if (out[i] == 0) str[i] = 0;
		else
			str[i] = out[i];
	}
	free(out);
}

int main() {

	FILE* fin;
	FILE* fout = fopen("Fout.txt", "w");


	if ((fin = fopen("Fin.txt", "r")) == NULL)
	{
		printf("Error");
		return 0;
	}
	else printf("Success");

	char* x[N] = { 0 };

	char ch = 0;
	int v = 0, n = 5;
	char* str = (char*)malloc(n * sizeof(char));
	do {
		fscanf(fin,"%c", &ch);
		str[v] = ch;
		v++;
		if (v == n - 2) {
			n *= 2;
			str =realloc(str, n * sizeof(char));
		}
	} while (!feof(fin));
	str[v-1] = 0;

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

	int* mas = (int*)malloc(strl * sizeof(int));
	int boo = 0;
		for (int i = 0; i < N; i++) {
			int substrl = strlength(x[i]);
			for (int j = 0; j < strl; j++) {
				mas[j] = 0;
			}
			poisk(str, x[i], mas, &boo,i);
			prisv(str, strl, substrl, mas, i, &boo);
			boo = 0;
		}
	for (int i = 0; i < strl; i++) {
		fprintf(fout,"%c", str[i]);
	}

	fclose(fout);
	fclose(fin);
	free(str);
	free(mas);
	return 0;
}	