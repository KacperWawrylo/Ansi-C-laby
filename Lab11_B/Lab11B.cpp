#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

class osoba_na_uczelni {
public:
	char imie[20];
	char nazwisko[20];
	char email[20];
	osoba_na_uczelni* nast;
	void set_imie(char* imie_) {
		strcpy(imie, imie_);
	}
	void set_nazwisko(char* nazwisko_) {
		strcpy(nazwisko, nazwisko_);
	}
	void set_email(char* email_) {
		strcpy(email, email_);
	}
	char* get_imie() {
		return imie;
	}
	char* get_nazwisko() {
		return nazwisko;
	}
	char* get_email() {
		return email;
	}
	virtual void wypisz() {
		printf("Osoba na uczelni:\nimie: %s\nnazwisko: %s\nemail: %s\n\n", imie, nazwisko, email);
	}
	osoba_na_uczelni() {
		strcpy(imie, "Jan");
		strcpy(nazwisko, "Kowalski");
		strcpy(email, "jan.kowalski@wp.pl");
		nast = NULL;
	}
	osoba_na_uczelni(char* imie_, char* nazwisko_, char* email_) {
		strcpy(imie, imie_);
		strcpy(nazwisko, nazwisko_);
		strcpy(email, email_);
		nast = NULL;
	}
	osoba_na_uczelni(osoba_na_uczelni& mk) {
		strcpy(imie, mk.imie);
		strcpy(nazwisko, mk.nazwisko);
		strcpy(email, mk.email);
		nast = mk.nast;
	}
	~osoba_na_uczelni() {
		delete nast;
	}
};

class student : public osoba_na_uczelni {
public:
	int nr_indeksu;
	int rok_rozpoczecia;
	void set_rok(int rok) {
		rok_rozpoczecia = rok;
	}
	void set_indeks(int indeks) {
		nr_indeksu = indeks;
	}
	int get_indeks() {
		return nr_indeksu;
	}
	int get_rok_rozpoczecia() {
		return rok_rozpoczecia;
	}
	void wypisz() override {
		printf("Osoba na uczelni Student:\nimie: %s\nnazwisko: %s\nemail: %s\n nr indeksu: %d\nrok rozpoczecia: %d\n\n", imie, nazwisko, email, nr_indeksu, rok_rozpoczecia);
	}
	student() : osoba_na_uczelni() {
		nr_indeksu = 124235;
		rok_rozpoczecia = 2022;
	}
	student(student& mk) : osoba_na_uczelni(mk) {
		nr_indeksu = mk.nr_indeksu;
		rok_rozpoczecia = mk.rok_rozpoczecia;
	}
	student(char* imie, char* nazwisko, char* email, int indeks, int rok) : osoba_na_uczelni(imie, nazwisko, email) {
		nr_indeksu = indeks;
		rok_rozpoczecia = rok;
	}
	~student() {
		delete nast;
	}
};

class pracownik : public osoba_na_uczelni {
public:
	int liczba_magis;
	char tab[10][7];
	void set_liczba_magis(int licz) {
		liczba_magis = licz;
	}
	void set_tab(int indeks, char kod) {
		tab[indeks][0] = kod;
	}
	int get_liczba_magis() {
		return liczba_magis;
	}
	char get_tablica(int indeks) {
		return tab[indeks][0];
	}
	void wypisz() override {
		printf("Osoba na uczelni pracownik:\nimie: %s\nnazwisko: %s\nemail: %s\nliczba magistrantow: %d\n", imie, nazwisko, email, liczba_magis);
		for (int i = 0; i < 10; i++) {
			printf("%s\n", tab[i]);
		}
		printf("\n");
	}
	pracownik() : osoba_na_uczelni() {
		liczba_magis = 3;
		char napis[] = "qazwsx";
		for (int i = 0; i < 10; i++) {
			strcpy(tab[i], napis);
		}

	}
	pracownik(char* imie_, char* nazwisko_, char* email_, int liczb, char tab_[][7]) : osoba_na_uczelni(imie_, nazwisko_, email_) {
		liczba_magis = liczb;
		for (int i = 0; i < 10; i++) {
			strcpy(tab[i], tab_[i]);
		}
	}
	pracownik(pracownik& mk) : osoba_na_uczelni(mk) {
		liczba_magis = mk.liczba_magis;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; i < 6; j++) {
				tab[i][j] = mk.tab[i][j];
			}
		}
	}
	~pracownik() {
		delete nast;
	}
};

int main() {
	osoba_na_uczelni* glowa = NULL;
	char wybor = 't';
	do {
		printf("podaj co chcesz dodac. (s - student, p- pracownik)\n");
		char o;
		cin >> o;
		if (o == 's') {
			printf("podaj : imie, nazwisko, email, nr indeksu, rok rozpoczecia\n");
			char imie[10];
			char nazwisko[10];
			char email[20];
			int indeks;
			int roz;
			cin >> imie;
			cin >> nazwisko;
			cin >> email;
			cin >> indeks;
			cin >> roz;
			if (indeks < 100000 || indeks > 999999 || roz > 2023 || roz < 2000) {
				printf("domyslny konstruktor\n");
				if (glowa == NULL) {
					glowa = new student();
				}
				else {
					osoba_na_uczelni* p = glowa;
					while (p->nast != NULL) {
						p = p->nast;
					}
					p->nast = new student();
				}
			}
			else {
				if (glowa == NULL) {
					glowa = new student(imie, nazwisko, email, indeks, roz);
				}
				else {
					osoba_na_uczelni* p = glowa;
					while (p->nast != NULL) {
						p = p->nast;
					}
					p->nast = new student(imie, nazwisko, email, indeks, roz);
				}
			}
		}
		if (o == 'p') {
			printf("podaj : imie, nazwisko, email, liczbe magistrantow, przedmioty\n");
			char imie[10];
			char nazwisko[10];
			char email[20];
			int liczb;
			char tab[10][7] = {NULL};
			cin >> imie;
			cin >> nazwisko;
			cin >> email;
			cin >> liczb;
			for (int i = 0; i < 10; i++) {
				printf("podaj kod znakow przedmiotu %d\n: ", i + 1);
				scanf_s("%s", tab[i], 6);
				tab[i][6] = '\0';
			}
			if (liczb < 0 || liczb > 8) {
				printf("domyslny konstruktor\n");
				if (glowa == NULL) {
					glowa = new pracownik();
				}
				else {
					osoba_na_uczelni* p = glowa;
					while (p->nast != NULL) {
						p = p->nast;
					}
					p->nast = new pracownik();
				}
			}
			else {
				if (glowa == NULL) {
					glowa = new pracownik(imie, nazwisko, email, liczb, tab);
				}
				else {
					osoba_na_uczelni* p = glowa;
					while (p->nast != NULL) {
						p = p->nast;
					}
					p->nast = new pracownik(imie, nazwisko, email, liczb, tab);
				}
			}
		}
		printf("chcesz dodac jeszcze ? t - tak, n-nie\n");
		cin >> wybor;
	} while (wybor != 'n');
	osoba_na_uczelni* p = glowa;
	while (p != NULL) {
		p->wypisz();
		p = p->nast;
	}
	delete glowa;

	system("pause");
	return 0;
}