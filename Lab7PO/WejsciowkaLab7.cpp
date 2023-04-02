#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct pomiar {
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar* nast;
	struct pomiar* poprz;
};

void wypisz(struct pomiar* glowa) {
	struct pomiar* current = glowa;
	while (current != NULL) {
		printf("%d %d %s %lf\n", current->nr_pomiaru, current->nr_czujnika, current->data_i_czas, current->temp);
		current = current->nast;
	}
}

int main() {
	printf("Podaj nazwe do pliku: ");
	char plik[30];
	scanf_s("%s", plik, 30);

	FILE* f = fopen(plik, "r");
	if (f == NULL) {
		printf("pusty plik");
		exit(0);
	}
	else {
		printf("otwarto plik\n");
	}
	struct pomiar* wsk = NULL, * glowa = NULL;
	while (!feof(f))
	{
		if (glowa == NULL)
		{
			glowa = wsk = (struct pomiar*)malloc(sizeof(struct pomiar));
		}
		else
		{
			wsk->nast = (struct pomiar*)malloc(sizeof(struct pomiar));
			struct pomiar* p = wsk;
			wsk = wsk->nast;
			wsk->poprz = p;

		}
		fscanf(f, "%d %d %s %lf", &wsk->nr_pomiaru, &wsk->nr_czujnika, wsk->data_i_czas, &wsk->temp);
		wsk->nast = NULL;
		wsk->poprz = NULL;
	}
	wypisz(glowa);

	fclose(f);

	return 0;
}