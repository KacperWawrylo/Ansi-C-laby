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

void zapis_do_pliku(char* plik, struct pomiar* lista, char c) {
	struct pomiar* current = lista;
	char nazwa[50];
	char numer[2] = { c, '\0' };
	strcpy(nazwa, plik);
	strcat(nazwa, numer);
	strcat(nazwa, ".txt");
	FILE* f = fopen(nazwa, "w");

	while (current != NULL) {
		fprintf(f, "%u %u %s %lf\n", current->nr_pomiaru, current->nr_czujnika, current->data_i_czas, current->temp);
		current = current->nast;
	}
	fclose(f);
}

void wypisz_liste(struct pomiar* glowa) {
	struct pomiar* current = glowa;
	while (current != NULL) {
		printf("%d %d %s %lf\n", current->nr_pomiaru, current->nr_czujnika, current->data_i_czas, current->temp);
		current = current->nast;
	}
}

void wypisz_liste_od_tylu(struct pomiar* glowa) {
	struct pomiar* current = glowa;
	while (current->nast != NULL) {
		current = current->nast;
	}
	while (current != NULL) {
		printf("%u %u %s %lf\n", current->nr_pomiaru, current->nr_czujnika, current->data_i_czas, current->temp);
		current = current->poprz;
	}
}

int policz_elementy(struct pomiar* glowa) {
	struct pomiar* p = glowa;
	int n = 0;
	while (p != NULL) {
		n++;
		p = p->nast;
	}
	return n;
}

void usuwanie_listy(struct pomiar* glowa) {
	struct pomiar* obecny = glowa;
	while (obecny != NULL) {
		struct pomiar* temp = obecny->nast;
		free(obecny);
		obecny = temp;
	}
}

void najw_najm(struct pomiar* glowa, int l) {
	struct pomiar* p = glowa;
	double max = p->temp, min = p->temp;
	while (p != NULL) {
		if (max < p->temp) {
			max = p->temp;
		}
		p = p->nast;
	}
	p = glowa;
	while (p != NULL) {
		if (min > p->temp) {
			min = p->temp;
		}
		p = p->nast;
	}
	printf("Najwieksza temp listy %d : %lf\nNajmiejsze temp listy %d : %lf\n", l, max, l, min);
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

	struct pomiar* wsk = NULL, * glowa = NULL, *ostatni = NULL;
	while (!feof(f))
	{
		wsk = (struct pomiar*)malloc(sizeof(struct pomiar));
		fscanf(f, "%u %u %s %lf", &wsk->nr_pomiaru, &wsk->nr_czujnika, wsk->data_i_czas, &wsk->temp);
		wsk->nast = NULL;
		if (glowa == NULL)
		{
			glowa = wsk;
			ostatni = wsk;
			wsk->poprz = NULL;
		}
		else
		{
			ostatni->nast = wsk;
			wsk->poprz = ostatni;
			ostatni = wsk;
		}
	}

	struct pomiar* lista1 = NULL;
	struct pomiar* lista2 = NULL;
	struct pomiar* lista3 = NULL;
	struct pomiar* lista4 = NULL;
	struct pomiar* lista = glowa;

	while (lista != NULL) {
		// zapamiêtanie wskaŸnika na nastêpny element
		struct pomiar* nastepny = lista->nast;
		
		if (lista->nr_czujnika == 1) {
			if (lista1 == NULL) {
				lista1 = lista;
				lista->poprz = NULL;
				lista->nast = NULL;
			}
			else {
				struct pomiar* p = lista1;
				while (p->nast != NULL) {
					p = p->nast;
				}
				p->nast = lista;
				lista->poprz = p;
				lista->nast = NULL;
			}
		}
		else if (lista->nr_czujnika == 2) {
			if (lista2 == NULL) {
				lista2 = lista;
				lista->poprz = NULL;
				lista->nast = NULL;
			}
			else {
				struct pomiar* p = lista2;
				while (p->nast != NULL) {
					p = p->nast;
				}
				p->nast = lista;
				lista->poprz = p;
				lista->nast = NULL;
			}
		}
		else if (lista->nr_czujnika == 3) {
			if (lista3 == NULL) {
				lista3 = lista;
				lista->poprz = NULL;
				lista->nast = NULL;
			}
			else {
				struct pomiar* p = lista3;
				while (p->nast != NULL) {
					p = p->nast;
				}
				p->nast = lista;
				lista->poprz = p;
				lista->nast = NULL;
			}
		}
		else if (lista->nr_czujnika == 4) {
			if (lista4 == NULL) {
				lista4 = lista;
				lista->poprz = NULL;
				lista->nast = NULL;
			}
			else {
				struct pomiar* p = lista4;
				while (p->nast != NULL) {
					p = p->nast;
				}
				p->nast = lista;
				lista->poprz = p;
				lista->nast = NULL;
			}
		}
		else {
			// jeœli numer czujnika jest niepoprawny, zwalniamy pamiêæ zajmowan¹ przez element
			free(lista);
		}
		lista = nastepny;
	}
	printf("Lista 1 : %d\nLista 2 : %d\nLista 3 : %d\nLista 4 : %d\n", policz_elementy(lista1), policz_elementy(lista2), policz_elementy(lista3), policz_elementy(lista4));
	najw_najm(lista1, 1);
	najw_najm(lista2, 2);
	najw_najm(lista3, 3);
	najw_najm(lista4, 4);
	fclose(f);
	printf("Podaj nazwe pliku do zapisu: ");
	char zapis[30];
	scanf_s("%s", zapis, 30);
	zapis_do_pliku(zapis, lista1, '1');
	zapis_do_pliku(zapis, lista2, '2');
	zapis_do_pliku(zapis, lista3, '3');
	zapis_do_pliku(zapis, lista4, '4');
	usuwanie_listy(lista1);
	usuwanie_listy(lista2);
	usuwanie_listy(lista3);
	usuwanie_listy(lista4);
	return 0;
}