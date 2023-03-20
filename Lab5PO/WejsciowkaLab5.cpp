#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int bin2int(char* t) {
    int liczba = 0;
    int dlugosc = (int)strlen(t);
    int potega = dlugosc - 2;
    for (int i = 0; i < dlugosc; i++)
    {
        if (t[i] == '1')
        {
            int temp = (int)pow(2, potega);
            liczba += temp;
            potega--;
        }
        else
        {
            potega--;
        }
    }
    
    return liczba;
}


void wypisz_tab(char** tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", tab[i]);
        printf("\n");
    }
}

void sortowanie_przez_wybor(char** tab, int n) {
    for (int j = 0; j < n; j++) {
        int min = j;
        for (int i = j + 1; i < n; i++) {
            if (bin2int(tab[i]) < bin2int(tab[min])) {
                min = i;
            }
            if (min != i) {
                char* pomocnicza = tab[i];
                tab[i] = tab[min];
                tab[min] = pomocnicza;
            }
        }
    }


}

int main() {
    int n, m;
    printf("Podaj liczbe wierszy i kolumn: ");
    scanf_s("%d %d", &m, &n);

    char** tab = (char**)malloc(m * sizeof(char*));
    for (int i = 0; i < m; i++) {
        tab[i] = (char*)malloc(n * sizeof(char));
        memset(tab[i], 0, n * sizeof(char));
    }

    FILE* fp = fopen("plik.txt", "r");
    if (fp == NULL) {
        printf("Nie udalo sie otworzyc pliku.\n");
        return 1;
    }
    int itab = 0;
    while (fgets(tab[itab], n, fp) != NULL) {
        itab++;
        if (itab == m) {
            break;
        }
    }

    for(int i = 0; i < itab ; i++){
        printf("liczba %s %d",tab[i], bin2int(tab[i]));
        printf("\n");
    }

    sortowanie_przez_wybor(tab, itab);
    printf("\nnowy porzadek:\n\n");
    for (int i = 0; i < itab; i++) {
        printf("liczba %s  %d", tab[i], bin2int(tab[i]));
        printf("\n");
    }

    for (int i = 0; i < m; i++) {
        free(tab[i]);
    }
    free(tab);
    fclose(fp);
    return 0;
}
