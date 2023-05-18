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

class samochod {
public:
	double cena;
	char rodzaj_silnika[20];
	samochod* nast;
	void set_cena(double cena_) {
		if (cena_ > 0) {
			cena = cena_;
		}
	}
	void set_rodzaj_silnika(char* rodzaj_silnika_) {
		strcpy(rodzaj_silnika, rodzaj_silnika_);
	}
	double get_cena() {
		return cena;
	}
	char* get_rodzaj_silnika() {
		return rodzaj_silnika;
	}
	void wypisz() {
		printf("Samochod:\ncena : %.2lf zl\nrodzaj silnika: %s\n\n", cena, rodzaj_silnika);
	}

	samochod() {
		cena = 5000;
		strcpy(rodzaj_silnika, "benzyna");
		nast = NULL;
	}
	samochod(double cena_, char* rodzaj_silnika_) {
		if (cena_ > 0) {
			cena = cena_;
		}
		else {
			printf("ustawiona domyslna wartosc 5000\n");
			cena = 5000;
		}
		strcpy(rodzaj_silnika, rodzaj_silnika_);
		nast = NULL;
	}
	samochod(samochod& mk) {
		cena = mk.cena;
		strcpy(rodzaj_silnika, mk.rodzaj_silnika);
		nast = mk.nast;
	}
	~samochod() {
		delete nast;
	}
};

class urzadzenie_optyczne {
public:
	double zoom;
	double waga;
	urzadzenie_optyczne* nast;
	void set_zoom(double zoom_) {
		if (zoom_ > 0) {
			zoom = zoom_;
		}
	}
	void set_waga(double waga_) {
		if (waga_ > 0) {
			waga = waga_;
		}
	}
	double get_zoom() {
		return zoom;
	}
	double get_waga() {
		return waga;
	}
	void wypisz() {
		printf("Urzadzenie optyczne:\nzoom: %.2lf x\nwaga: %.2lf kg\n\n", zoom, waga);
	}
	urzadzenie_optyczne() {
		zoom = 1.5;
		waga = 25;
		nast = NULL;
	}
	urzadzenie_optyczne(double zoom_, double waga_) {
		zoom = zoom_;
		waga = waga_;
		nast = NULL;
	}
	urzadzenie_optyczne(urzadzenie_optyczne& mk) {
		zoom = mk.zoom;
		waga = mk.waga;
		nast = mk.nast;
	}
	~urzadzenie_optyczne() {
		delete nast;
	}
};

class student {
public:
	char imie[20];
	char nazwisko[20];
	char email[20];
	student* nast;
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
	void wypisz() {
		printf("Student:\nimie: %s\nnazwisko: %s\nemail: %s\n\n", imie, nazwisko, email);
	}
	student() {
		strcpy(imie, "Jan");
		strcpy(nazwisko, "Kowalski");
		strcpy(email, "jan.kowalski@wp.pl");
		nast = NULL;
	}
	student(char* imie_, char* nazwisko_, char* email_) {
		strcpy(imie, imie_);
		strcpy(nazwisko, nazwisko_);
		strcpy(email, email_);
		nast = NULL;
	}
	student(student& mk) {
		strcpy(imie, mk.imie);
		strcpy(nazwisko, mk.nazwisko);
		strcpy(email, mk.email);
		nast = mk.nast;
	}
	~student() {
		delete nast;
	}
};

int main() {
	samochod* glowa1 = new samochod();
	urzadzenie_optyczne* glowa2 = new urzadzenie_optyczne();
	student* glowa3 = new student();
	samochod* p1 = glowa1;
	urzadzenie_optyczne* p2 = glowa2;
	student* p3 = glowa3;
	for (int i = 0; i < 4; i++) {
		p1->nast = new samochod();
		p1 = p1->nast;
		p2->nast = new urzadzenie_optyczne();
		p2 = p2->nast;
		p3->nast = new student();
		p3 = p3->nast;
	}
	p1 = glowa1;
	p2 = glowa2;
	p3 = glowa3;
	for (int i = 0; i < 5; i++) {
		p1->wypisz();
		p1 = p1->nast;
		p2->wypisz();
		p2 = p2->nast;
		p3->wypisz();
		p3 = p3->nast;
	}
	delete glowa1;
	delete glowa2;
	delete glowa3;

	system("pause");
	return 0;
}