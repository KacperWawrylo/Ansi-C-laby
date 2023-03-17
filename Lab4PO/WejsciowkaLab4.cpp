#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define L 30

void szyfrowanie(FILE* f, FILE* s) {
	char napis[L];
	fscanf(f, "%s", napis);
	int n = strlen(napis);
	for (int i = 0; i < n; i++) {
		napis[i] = toupper(napis[i]);
		if (napis[i] == 'Z') {
			napis[i] = 'A';
		}
		else {
			napis[i]++;
		}
	}
	fprintf(s, "%s\n", napis);
}

int main() {
	char nazwa_wejscia[L], nazwa_wyjscia[L];

	FILE* plik_wejsciowy, * plik_wyjsciowy;

	printf("Podaj nazwe pliku z danymi: ");
	scanf_s("%s", nazwa_wejscia, L);
	printf("Podaj nazwe pliku wyjsciowego: ");
	scanf_s("%s", nazwa_wyjscia, L);

	plik_wejsciowy = fopen(nazwa_wejscia, "r");
	plik_wyjsciowy = fopen(nazwa_wyjscia, "w");

	if (plik_wejsciowy == NULL || plik_wyjsciowy == NULL) {
		printf("Blad otwarcia pliku\n");
		exit(1);
	}

	while (!feof(plik_wejsciowy)) {
		szyfrowanie(plik_wejsciowy, plik_wyjsciowy);
	}

	fclose(plik_wejsciowy);
	fclose(plik_wyjsciowy);

	return 0;
}