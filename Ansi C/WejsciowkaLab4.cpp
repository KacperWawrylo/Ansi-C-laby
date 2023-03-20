#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


#define M 5
#define L 30

struct para {
    char napis[L];
    int liczba;
};

int jest_sam(char c) {
    char sam[] = { 'a', 'e', 'i', 'o', 'u' };
    for (int i = 0; i < strlen(sam); i++) {
        if (c == sam[i]) return 1;
    }
    return 0;
}

void szyforwanie(char napis[L]) {
    int str_lenght = strlen(napis);
    for (int i = 0; i < str_lenght; i++) {
        if (jest_sam(napis[i])) {
            napis[i] = '*';
        }
    }
}


int wiersz(FILE* f, struct para* p) {
    char nr_indeksu[M], nazwisko[L];
    int ocena;

    if (fscanf(f, "%s %s %d", nr_indeksu, nazwisko, &ocena) != 3) {
        return 1;
    }

    strcpy(p->napis, nazwisko);
    p->liczba = ocena;

    return 0;
}

int main() {
    char nazwa_wejscia[L], nazwa_wyjscia[L];
    struct para tablica[M];
    FILE* plik_wejsciowy, * plik_wyjsciowy;
    int wynik;

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

    int i = 0;
    while (i < M) {
        if (wiersz(plik_wejsciowy, &tablica[i]) == 1) {
            break;
        }
        //fprintf(plik_wyjsciowy, "%s %d\n", tablica[i].napis, tablica[i].liczba);
        i++;
    }

    for (int i = 0; i < M; i++) {
        szyforwanie(tablica[i].napis);
        fprintf(plik_wyjsciowy, "%s %d\n", tablica[i].napis, tablica[i].liczba);
    }

    fclose(plik_wejsciowy);
    fclose(plik_wyjsciowy);

    for (int j = 0; j < i; j++) {
        printf("%d. %s %d\n", j + 1, tablica[j].napis, tablica[j].liczba);
    }

    system("pause");
    return 0;
}