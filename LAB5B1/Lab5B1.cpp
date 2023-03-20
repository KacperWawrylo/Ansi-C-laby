#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct student {
    int nr_ID;
    char nazwisko[40];
    char imie[40];
    double punkty;
};

int policz_wiersze(FILE* plik) {
    int licznik = 0;
    char c;
    while ((c = getc(plik)) != EOF) {
        if (c == '\n') {
            licznik++;
        }
    }
    rewind(plik);
    return licznik;
}

struct student_array {
    struct student* tablica;
    int rozmiar;
};

void wypisz_tablice(struct student* tablica, int rozmiar);
struct student_array usun_studenta(struct student* tablica, int rozmiar);

struct student_array wczytaj_z_pliku(char* nazwa_pliku) {
    FILE* plik = fopen(nazwa_pliku, "r");
    if (plik == NULL) {
        printf("Blad otwarcia pliku.\n");
        exit(0);
    }
    int liczba_wierszy = policz_wiersze(plik);
    if (liczba_wierszy == 0) {
        printf("Plik jest pusty.\n");
        exit(0);
    }
    struct student* tablica = (struct student*)malloc(sizeof(struct student) * liczba_wierszy);
    if (tablica == NULL) {
        printf("Blad alokacji pamieci.\n");
        exit(0);
    }
    int i;
    for (i = 0; i < liczba_wierszy; i++) {
        fscanf(plik, "%d %s %s %lf", &tablica[i].nr_ID, tablica[i].nazwisko, tablica[i].imie, &tablica[i].punkty);
    }
    fclose(plik);
    struct student_array wynik;
    wynik.tablica = tablica;
    wynik.rozmiar = liczba_wierszy;
    wypisz_tablice(tablica, wynik.rozmiar);
    usun_studenta(tablica, wynik.rozmiar);
    return wynik;
}

void wypisz_tablice(struct student* tablica, int rozmiar) {
    int i;
    for (i = 0; i < rozmiar; i++) {
        printf("%d %s %s %.2lf\n", tablica[i].nr_ID, tablica[i].nazwisko, tablica[i].imie, tablica[i].punkty);
    }
}

struct student_array usun_studenta(struct student* tablica, int rozmiar) {
    int n = rozmiar - 1; 
    printf("podaj id studenta do wyrzucenia: ");
    int id;
    scanf_s("%d", &id);
    int indeks_do_usuniecia = -1;
    struct student* nowa_tablica = (struct student*)malloc(sizeof(struct student) * (rozmiar - 1));
    for (int i = 0, j = 0; i < rozmiar; i++) {
        if (tablica[i].nr_ID == id) {
            indeks_do_usuniecia = i;
            break;
        }
        else {
            nowa_tablica[j++] = tablica[i];
        }
    }
    free(tablica);
    struct student_array wynik;
    wynik.tablica = nowa_tablica;
    wynik.rozmiar = rozmiar-1;
    wypisz_tablice(nowa_tablica, wynik.rozmiar);
    return wynik;
}

int main() {
    char tab[] = "plik.txt";
    struct student_array wynik = wczytaj_z_pliku(tab);

    printf("podaj nazwe pliku w ktorym chcesz zapisac: ");
    char taba[40]{NULL};
    scanf_s("%s", &tab, 40);
    
    FILE* plik = fopen(taba, "w");
    int rozmiar = wynik.rozmiar - 1;
    struct student* tablica = wynik.tablica;
    for (int i = 0; i < rozmiar; i++) {
        fprintf(plik,"%d %s %s %.2lf\n", tablica[i].nr_ID, tablica[i].nazwisko, tablica[i].imie, tablica[i].punkty);
    }

    fclose(plik);

	return 0;
}