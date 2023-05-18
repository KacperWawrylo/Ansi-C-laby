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
	virtual void wypisz() {
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

class kamera : public urzadzenie_optyczne {
public:
	int maks_pracy;
	char symbol[20];
	void set_maks_pracy(int n) {
		if (n > 0) {
			maks_pracy = n;
		}
	}
	void set_symbol(char* symbol_) {
		strcpy(symbol, symbol_);
	}
	int get_maks_pracy() {
		return maks_pracy;
	}
	char* get_symbol() {
		return symbol;
	}
	void wypisz() override{
		printf("Urzadzenie optyczne kamera:\nzoom: %.2lf x\nwaga: %.2lf kg\nmaksymalny czas pracy: %d min\nformat: %s\n\n", zoom, waga, maks_pracy, symbol);
	}
	kamera() : urzadzenie_optyczne() {
		maks_pracy = 60;
		strcpy(symbol, "HDV");
	}
	kamera(double zoom_, double waga_, int czas, char* symbol_) : urzadzenie_optyczne(zoom_, waga_) {
		maks_pracy = czas;
		strcpy(symbol, symbol_);
	}
	kamera(kamera& mk) : urzadzenie_optyczne(mk) {
		maks_pracy = mk.maks_pracy;
		strcpy(symbol, mk.symbol);
	}
	~kamera(){
		delete nast;
	}
};

int main() {
	urzadzenie_optyczne* glowa1 = NULL;
	
	char wybor ='t';
	do {
		printf("Co chcesz dodac ? (K - Kamera , L - lornetka)\n");
		char u;
		cin >> u;
		if (u == 'K' || u == 'k') {
			printf("podaj wage, zoom, czas pracy (min), format\n");
			double waga, zoom;
			int czas;
			char format[20];
			cin >> waga >> zoom >> czas;
			scanf_s("%s", format, 20);
			if (glowa1 == NULL) {
				glowa1 = new kamera(waga, zoom, czas, format);
			}
			else {
				urzadzenie_optyczne* p = glowa1;
				while (p->nast!=NULL) {
					p = p->nast;
				}
				p->nast = new kamera(waga, zoom, czas, format);
			}
		}
		printf("czy cchesz jezcze cos dodac? t/n");
		cin >> wybor;
	} while (wybor != 'n');
	urzadzenie_optyczne* p = glowa1;
	while (p != NULL) {
		p->wypisz();
		p = p->nast;
	}
	
	system("pause");
	return 0;
}