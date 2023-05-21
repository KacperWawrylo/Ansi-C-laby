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
	osoba_na_uczelni(const char* imie_, const char* nazwisko_, const char* email_) {
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

	osoba_na_uczelni& operator+=(const osoba_na_uczelni& other) {
		strcat(imie, other.imie);
		return *this;
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
	student(const char* imie, const char* nazwisko, const char* email, int indeks, int rok) : osoba_na_uczelni(imie, nazwisko, email) {
		nr_indeksu = indeks;
		rok_rozpoczecia = rok;
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
};
int main() {
	osoba_na_uczelni* lista[5];

	lista[0] = new osoba_na_uczelni("Jan", "Kowalski", "jan.kowalski@example.com");
	lista[1] = new osoba_na_uczelni("Anna", "Nowak", "anna.nowak@example.com");
	lista[2] = new student("Adam", "Smith", "adam.smith@example.com", 123456, 2019);
	lista[3] = new student("Maria", "Johnson", "maria.johnson@example.com", 654321, 2020);
	lista[4] = new student("Robert", "Brown", "robert.brown@example.com", 987654, 2021);

	osoba_na_uczelni suma;
	for (int i = 0; i < 5; i++) {
		suma += *lista[i];
	}

	suma.wypisz();

	for (int i = 0; i < 5; i++) {
		delete lista[i];
	}

	system("pause");
	return 0;
}