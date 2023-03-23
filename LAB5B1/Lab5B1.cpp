#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct student {
	int nr_ID;
	char nazwisko[40];
	char imie[40];
	double punkty;
};

int policz_wiersze(FILE* f) {
	int licznik = 0;
	char c;
	while ((c = fgetc(f)) != EOF) {
		if (c == '\n') {
			licznik++;
		}
	}
	rewind(f);
	return licznik;
}

struct student_array {
	struct student* tablica;
	int rozmiar;
};

void wypisz_tab(struct student* tablica, int rozmiar);

struct student_array wczytywanie_do_tab(char* plik) {
	FILE* f = fopen(plik, "r");
	if (f == NULL) {
		exit(0);
	}
	int liczba_wierszy = policz_wiersze(f);
	struct student* tablica = (struct student*)malloc(liczba_wierszy * (sizeof(struct student)));
	for (int i = 0; i < liczba_wierszy; i++) {
		fscanf(f, "%d %s %s %lf", &tablica[i].nr_ID, tablica[i].nazwisko, tablica[i].imie, &tablica[i].punkty);
	}
	struct student_array wynik;
	wynik.tablica = tablica;
	wynik.rozmiar = liczba_wierszy;
	fclose(f);
	return wynik;
}

void wypisz_tab(struct student* tablica, int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		printf("%d %s %s %.2lf\n", tablica[i].nr_ID, tablica[i].nazwisko, tablica[i].imie, tablica[i].punkty);
	}
}

struct student_array usuwanie_i_nowa_tab(struct student* tablica, int liczba_wierszy) {
	liczba_wierszy = liczba_wierszy - 1;
	struct student* tablica2 = (struct student*)malloc(liczba_wierszy * (sizeof(struct student)));
	printf("\nPodaj id do usuniecia: ");
	int id;
	scanf_s("%d", &id);
	int indeks_do_usu = -1;
	int index_2 = 0;
	for (int i = 0; i < liczba_wierszy+1; i++) {
		if (tablica[i].nr_ID == id) {
			indeks_do_usu = i;
			continue;
		}
		tablica2[index_2] = tablica[i];
		index_2++;
	}
	if (indeks_do_usu == -1) {
		printf("zly indeks");
		exit(0);
	}
	free(tablica);
	struct student_array wynik2;
	wynik2.tablica = tablica2;
	wynik2.rozmiar = liczba_wierszy;
	return wynik2;

}

int main() {
	char tab[] = "plik.txt";
	struct student_array pierwsza = wczytywanie_do_tab(tab);
	wypisz_tab(pierwsza.tablica, pierwsza.rozmiar);
	struct student_array druga = usuwanie_i_nowa_tab(pierwsza.tablica, pierwsza.rozmiar);
	wypisz_tab(druga.tablica, druga.rozmiar);

	char zapis[40] = { NULL };
	printf("podaj plik: ");
	scanf_s("%s", &zapis,40);
	FILE* fp = fopen(zapis, "w");
	for (int i = 0; i < druga.rozmiar; i++) {
		fprintf(fp, "%d %s %s %.2lf\n", druga.tablica[i].nr_ID, druga.tablica[i].nazwisko, druga.tablica[i].imie, druga.tablica[i].punkty);
	}

	fclose(fp);

	system("pause");
	return 0;
}