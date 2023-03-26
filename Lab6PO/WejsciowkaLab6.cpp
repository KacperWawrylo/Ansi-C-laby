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
};

int licz_elementy(struct pomiar* head) {
	int n = 0;
	struct pomiar* current = head;
	while (current != NULL) {
		n++;
		current = current->nast;
	}
	return n;
}

void zapis_do_pliku(char* plik, struct pomiar* lista, char c) {
	struct pomiar* current = lista;
	char nazwa[50];
	char numer[2] = { c, '\0' };
	strcpy(nazwa, plik);
	strcat(nazwa, numer);
	strcat(nazwa, ".txt");
	FILE* f = fopen(nazwa, "w");
	
	while (current != NULL) {
		fprintf(f,"%u %u %s %lf\n", current->nr_pomiaru, current->nr_czujnika, current->data_i_czas, current->temp);
		current = current->nast;
	}
	fclose(f);
}

int main() {
	char nazwa_pliku[50], poczatek_nazwy[50];
	printf("Podaj nazwe pliku z danymi: ");
	scanf_s("%s", nazwa_pliku, 50);
	printf("Podaj poczatek nazwy plikow z danymi: ");
	scanf_s("%s", poczatek_nazwy, 50);
	
	FILE* plik = fopen(nazwa_pliku, "r");
	if (plik == NULL) {
		printf("Nie mozna otworzyc pliku\n");
		exit(1);
	}

	struct pomiar* glowa = NULL;
	struct pomiar* nowy = NULL;
	while (!feof(plik)) {
		nowy = (struct pomiar*)malloc(sizeof(struct pomiar));
		fscanf(plik, "%u %u %s %lf", &nowy->nr_pomiaru, &nowy->nr_czujnika, nowy->data_i_czas, &nowy->temp);
		nowy->nast = glowa;
		glowa = nowy;
	}
	fclose(plik);
	
	struct pomiar* lista1 = NULL;
	struct pomiar* lista2 = NULL;
	struct pomiar* lista3 = NULL;
	struct pomiar* lista4 = NULL;

	// przepisz elementy z listy do odpowiednich list dla czujników
	struct pomiar* biezacy = glowa;
	while (biezacy != NULL) {
		if (biezacy->nr_czujnika == 1) {
			nowy = biezacy;
			biezacy = biezacy->nast;
			nowy->nast = lista1;
			lista1 = nowy;
		}
		else if (biezacy->nr_czujnika == 2) {
			nowy = biezacy;
			biezacy = biezacy->nast;
			nowy->nast = lista2;
			lista2 = nowy;
		}
		else if (biezacy->nr_czujnika == 3) {
			nowy = biezacy;
			biezacy = biezacy->nast;
			nowy->nast = lista3;
			lista3 = nowy;
		}
		else if (biezacy->nr_czujnika == 4) {
			nowy = biezacy;
			biezacy = biezacy->nast;
			nowy->nast = lista4;
			lista4 = nowy;
		}
	}
	// lista Ÿród³owa jest pusta
	glowa = NULL;

	printf("Liczba pomiarow dla czujnika 1: %d\n", licz_elementy(lista1));
	printf("Liczba pomiarow dla czujnika 2: %d\n", licz_elementy(lista2));
	printf("Liczba pomiarow dla czujnika 3: %d\n", licz_elementy(lista3));
	printf("Liczba pomiarow dla czujnika 4: %d\n", licz_elementy(lista4));
	
	zapis_do_pliku(poczatek_nazwy, lista1, '1');
	zapis_do_pliku(poczatek_nazwy, lista1, '2');
	zapis_do_pliku(poczatek_nazwy, lista1, '3');
	zapis_do_pliku(poczatek_nazwy, lista1, '4');
	system("pause");
	return 0;
}