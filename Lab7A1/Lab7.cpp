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

struct pom {
	struct pomiar* lista1;
	struct pomiar* lista2;
	struct pomiar* lista3;
	struct pomiar* lista4;
};

struct pomiar* zapis_list_dyn(char* plik){
	FILE* f = fopen(plik, "r");
	if (f == NULL) {
		printf("pusty plik");
		exit(0);
	}
	struct pomiar* wsk = NULL, * glowa = NULL, * ostatni = NULL;
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
	fclose(f);
	return glowa;
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

void funkcja_druga(struct pomiar* glowa) {
	int n = policz_elementy(glowa);
	printf("Ilosc elementow: %d\n\n", n);
	wypisz_liste(glowa);
	printf("\n");
	wypisz_liste_od_tylu(glowa);
	printf("\n");
}

struct pom nowe_listy(struct pomiar* glowa) {
	struct pomiar* p = glowa;
	struct pom wynik = { NULL,NULL,NULL,NULL };
	while (p != NULL) {
		struct pomiar* nowy = (struct pomiar*)malloc(sizeof(struct pomiar));
		nowy->nr_pomiaru = p->nr_pomiaru;
		nowy->nr_czujnika = p->nr_czujnika;
		strcpy(nowy->data_i_czas, p->data_i_czas);
		nowy->temp = p->temp;
		nowy->nast = NULL;
		if (p->nr_czujnika == 1) {
			if (wynik.lista1 == NULL) {
				wynik.lista1 = nowy;
				nowy->poprz = NULL;
			}
			else {
				struct pomiar* q = wynik.lista1;
				while (q->nast != NULL) {
					q = q->nast;
				}
				nowy->poprz = q;
				q->nast = nowy;
			}
		}
		else if (p->nr_czujnika == 2) {
			if (wynik.lista2 == NULL) {
				wynik.lista2 = nowy;
				nowy->poprz = NULL;
			}
			else {
				struct pomiar* q = wynik.lista2;
				int n = 0;
				while (q->nast != NULL) {
					n++;
					q = q->nast;
				}
				nowy->poprz = q;
				q->nast = nowy;
			}
		}
		else if (p->nr_czujnika == 3) {
			if (wynik.lista3 == NULL) {
				wynik.lista3 = nowy;
				nowy->poprz = NULL;
			}
			else {
				struct pomiar* q = wynik.lista3;
				int n = 0;
				while (q->nast != NULL) {
					n++;
					q = q->nast;
				}
				nowy->poprz = q;
				q->nast = nowy;
			}
		}
		else if (p->nr_czujnika == 4) {
			if (wynik.lista4 == NULL) {
				wynik.lista4 = nowy;
				nowy->poprz = NULL;
			}
			else {
				struct pomiar* q = wynik.lista4;
				int n = 0;
				while (q->nast != NULL) {
					n++;
					q = q->nast;
				}
				nowy->poprz = q;
				q->nast = nowy;
			}
		}
		p = p->nast;
	}
	return wynik;
}

void usuwanie_listy(struct pomiar* glowa) {
	struct pomiar* obecny = glowa;
	while (obecny != NULL) {
		struct pomiar* temp = obecny->nast;
		free(obecny);
		obecny = temp;
	}
}

struct pomiar* najw_najm(struct pomiar* glowa) {
	struct pomiar* p = glowa;
	struct pomiar* max = glowa;
	struct pomiar* min = glowa;
	while (p != NULL) {
		if (max->temp < p->temp) {
			max = p;
			
		}
		p = p->nast;
	}
	p = glowa;
	while (p != NULL) {
		if (min->temp > p->temp) {
			min = p;
		}
		p = p->nast;
	}
	printf("Najwieksza temp w elemencie listy : %u %u %s %lf\n", max->nr_pomiaru, max->nr_czujnika, max->data_i_czas, max->temp);
	printf("Najmniejsza temp w elemencie listy : %u %u %s %lf\n\n", min->nr_pomiaru, min->nr_czujnika, min->data_i_czas, min->temp);


	struct pomiar* nowy = (struct pomiar*)malloc(sizeof(struct pomiar));
	p = glowa;
	nowy->nr_pomiaru = max->nr_pomiaru;
	nowy->nr_czujnika = max->nr_czujnika;
	strcpy(nowy->data_i_czas, max->data_i_czas);
	nowy->temp = max->temp;
	nowy->nast = NULL;
	while (p->nast != NULL) {
		p = p->nast;
	}
	nowy->poprz = p;
	p->nast = nowy;
	nowy = (struct pomiar*)malloc(sizeof(struct pomiar));
	nowy->nr_pomiaru = min->nr_pomiaru;
	nowy->nr_czujnika = min->nr_czujnika;
	strcpy(nowy->data_i_czas, min->data_i_czas);
	nowy->temp = min->temp;
	nowy->nast = NULL;
	nowy->poprz = p->nast;
	p->nast->nast = nowy;
	return glowa;
}

int main() {
	printf("Podaj nazwe do pliku: ");
	char plik[30];
	scanf_s("%s", plik, 30);

	struct pomiar* glowa = zapis_list_dyn(plik);
	funkcja_druga(glowa);
	
	struct pom listy = nowe_listy(glowa);
	usuwanie_listy(glowa);
	printf("\n");
	funkcja_druga(listy.lista1);
	funkcja_druga(listy.lista2);
	funkcja_druga(listy.lista3);
	funkcja_druga(listy.lista4);
	najw_najm(listy.lista1);
	najw_najm(listy.lista2);
	najw_najm(listy.lista3);
	najw_najm(listy.lista4);
	printf("\n");
	funkcja_druga(listy.lista1);
	funkcja_druga(listy.lista2);
	funkcja_druga(listy.lista3);
	funkcja_druga(listy.lista4);

	return 0;
}