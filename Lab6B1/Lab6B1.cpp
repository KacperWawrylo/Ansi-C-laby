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

struct pom {
	struct pomiar* lista1;
	struct pomiar* lista2;
	struct pomiar* lista3;
	struct pomiar* lista4;
};

void funkcja_2(struct pomiar* lista) {
	int czujnik_1 = 0, czujnik_2 = 0, czujnik_3 = 0, czujnik_4 = 0;
	struct pomiar* p = lista;
	while (p != NULL) {
		if (p->nr_czujnika == 1) czujnik_1++;
		else if (p->nr_czujnika == 2) czujnik_2++;
		else if (p->nr_czujnika == 3) czujnik_3++;
		else if (p->nr_czujnika == 4) czujnik_4++;
		p = p->nast;
	}
	printf("Liczba pomiarow czujnika 1: %d\n", czujnik_1);
	printf("Liczba pomiarow czujnika 2: %d\n", czujnik_2);
	printf("Liczba pomiarow czujnika 3: %d\n", czujnik_3);
	printf("Liczba pomiarow czujnika 4: %d\n", czujnik_4);
	
	p = lista;
	if (p != NULL) {
		printf("Pierwszy pomiar w liscie: %d %d %s %.2lf\n", p->nr_pomiaru, p->nr_czujnika, p->data_i_czas, p->temp);
	}
	while ((p != NULL) && (p->nast != NULL) && (p->nast->nast != NULL)) {
		p = p->nast;
	}
	if ((p != NULL) && (p->nast != NULL)) {
		printf("Przedostatni pomiar: %d %d %s %2.lf\n", p->nr_pomiaru, p->nr_czujnika, p->data_i_czas, p->temp);
		printf("Ostatni pomiar: %d %d %s %.2lf\n", p->nast->nr_pomiaru, p->nast->nr_czujnika, p->nast->data_i_czas, p->nast->temp);
	}
}

struct pom nowe_listy(struct pomiar* lista) {
	struct pomiar* p = lista;
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
			}
			else {
				struct pomiar* q = wynik.lista1;
				while (q->nast != NULL) {
					q = q->nast;
				}
				q->nast = nowy;
			}
		}
		else if (p->nr_czujnika == 2) {
			if (wynik.lista2 == NULL) {
				wynik.lista2 = nowy;
			}
			else {
				struct pomiar* q = wynik.lista2;
				while (q->nast != NULL) {
					q = q->nast;
				}
				q->nast = nowy;
			}
		}
		else if (p->nr_czujnika == 3) {
			if (wynik.lista3 == NULL) {
				wynik.lista3 = nowy;
			}
			else {
				struct pomiar* q = wynik.lista3;
				while (q->nast != NULL) {
					q = q->nast;
				}
				q->nast = nowy;
			}
		}
		else if (p->nr_czujnika == 4) {
			if (wynik.lista4 == NULL) {
				wynik.lista4 = nowy;
			}
			else {
				struct pomiar* q = wynik.lista4;
				while (q->nast != NULL) {
					q = q->nast;
				}
				q->nast = nowy;
			}
		}
		p = p->nast;
	}
	return wynik;
}

struct pomiar* czwarta(struct pomiar* lista) {
	if (!lista) { // lista jest pusta
		printf("Lista jest pusta\n");
		return NULL;
	}
	struct pomiar* max = lista;
	struct pomiar* min = lista;
	struct pomiar* temp = lista;
	while (temp != NULL) { // szukanie elementu z najwy¿sz¹ temperatur¹
		if (temp->temp > max->temp) {
			max = temp;
		}
		temp = temp->nast;
	}
	temp = lista;
	while (temp != NULL) { // szukanie elementu z najni¿sz¹ temperatur¹
		if (temp->temp < min->temp) {
			min = temp;
		}
		temp = temp->nast;
	}
	if (max == min) { // jeœli mamy tylko jeden element na liœcie
		printf("Lista ma tylko jeden element\n");
		return lista;
	}
	if (min == lista) { // jeœli min jest pierwszym elementem na liœcie
		lista = min->nast;
		min->nast = NULL;
		temp = lista;
		while (temp->nast != NULL) {
			temp = temp->nast;
		}
		temp->nast = min;
	}
	else {
		temp = lista;
		while (temp->nast != min) {
			temp = temp->nast;
		}
		temp->nast = min->nast;
		min->nast = NULL;
		temp = lista;
		while (temp->nast != NULL) {
			temp = temp->nast;
		}
		temp->nast = min;
	}
	// przeniesienie elementu z najwy¿sz¹ temperatur¹ na pocz¹tek listy
	if (max == lista) { // jeœli max jest pierwszym elementem na liœcie
		printf("Najwyzsza temperatura: %u %u %s %.2f\n", max->nr_pomiaru, max->nr_czujnika, max->data_i_czas, max->temp);
		printf("Najnizsza temperatura: %u %u %s %.2f\n", min->nr_pomiaru, min->nr_czujnika, min->data_i_czas, min->temp);
		return lista;
	}
	else {
		temp = lista;
		while (temp->nast != max) {
			temp = temp->nast;
		}
		temp->nast = max->nast;
		max->nast = lista;
		lista = max;
		printf("Najwyzsza temperatura: %u %u %s %.2f\n", max->nr_pomiaru, max->nr_czujnika, max->data_i_czas, max->temp);
		printf("Najnizsza temperatura: %u %u %s %.2f\n", min->nr_pomiaru, min->nr_czujnika, min->data_i_czas, min->temp);
		return lista;
	}
}


struct pomiar* lista_dynamiczna(char* plik) {
	FILE* f = fopen(plik, "r");
	if (plik == NULL) {
		printf("Nie mozna otworzyc pliku\n");
		return NULL;
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
			wsk = wsk->nast;
		}
		fscanf(f, "%d %d %s %lf", &wsk->nr_pomiaru, &wsk->nr_czujnika, wsk->data_i_czas, &wsk->temp);
		wsk->nast = NULL;
	}
	fclose(f);
	return glowa;
}

int main() {
	char plik[] = "pomiary.txt";
	struct pomiar* glowa = lista_dynamiczna(plik);
	funkcja_2(glowa);
	printf("\n");
	struct pom nowy = nowe_listy(glowa);
	funkcja_2(nowy.lista1);
	printf("\n");
	nowy.lista1 = czwarta(nowy.lista1);
	printf("\n");
	funkcja_2(nowy.lista1);

	system("pause");
	return 0;
}