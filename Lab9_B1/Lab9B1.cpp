#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <cmath>

using namespace std;

class Prostokat {
private:
	double x1, y1, a, b; // a podstawa b wysokosc
public:
	void set(double x, double y, double a_, double b_) {
		if (x <= 0) {
			printf("Zla dlugosc x, ustawiam domyslna 1\n");
			x = 1;
		}
		if (y <= 0) {
			printf("Zla dlugosc y, ustawiam domyslna 1\n");
			y = 1;
		}
		if (a_ <= 0) {
			printf("Zla dlugosc a, ustawiam domyslna 1\n");
			a_ = 1;
		}
		if (b_ <= 0) {
			printf("Zla dlugosc b, ustawiam domyslna 1\n");
			b_ = 1;
		}
		x1 = x;
		y1 = y;
		a = a_;
		b = b_;

	}
	void wypisz() {
		double x2 = x1;
		double y2 = y1 + b;

		double x3 = x1 + a;
		double y3 = y2;

		double x4 = x3;
		double y4 = y1;
		cout << "Wspolrzedne pierwszego wierzcholka: (" << x1 << ", " << y1 << ")\n";
		cout << "Wspolrzedne drugiego wierzcholka: (" << x2 << ", " << y2 << ")\n";
		cout << "Wspolrzedne trzeciego wierzcholka: (" << x3 << ", " << y3 << ")\n";
		cout << "Wspolrzedne czwartego wierzcholka: (" << x4 << ", " << y4 << ")\n";
		cout << "Dlugosc podstawy: " << a << "\n";
		cout << "Wysokosc: " << b << "\n";
	}
	void symetria_osiowa(double n) {
		x1 = 2 * n - x1 - a;
	}
	void skalowanie(double k) {
		if (k > 0) {
			a *= k;
			b *= k;
		}
	}
};

class Trojkat {
private:
	double x1, y1, a, b; // a jeden bok przyprostokatny z ox, b drugi bok przyprostokatny z oy
public:
	void set(double x, double y, double a_, double b_) {
		if (x <= 0) {
			printf("Zla dlugosc x, ustawiam domyslna 1\n");
			x = 1;
		}
		if (y <= 0) {
			printf("Zla dlugosc y, ustawiam domyslna 1\n");
			y = 1;
		}
		if (a_ <= 0) {
			printf("Zla dlugosc a, ustawiam domyslna 1\n");
			a_ = 1;
		}
		if (b_ <= 0) {
			printf("Zla dlugosc b, ustawiam domyslna 1\n");
			b_ = 1;
		}
		x1 = x;
		y1 = y;
		a = a_;
		b = b_;
	}
	void wypisz() {
		double x2 = x1 + a;
		double y2 = y1;

		double x3 = x1;
		double y3 = y1 + b;

		cout << "Wspolrzedne A wierzcholka: (" << x1 << ", " << y1 << ")\n";
		cout << "Wspolrzedne B wierzcholka: (" << x2 << ", " << y2 << ")\n";
		cout << "Wspolrzedne C wierzcholka: (" << x3 << ", " << y3 << ")\n";
		cout << "Dlugosc przyprostokatnej z ox:" << a << "\n";
		cout << "Dlugosc przyprostokatnej z oy: " << b << "\n";
	}
	void symetria_osiowa(double n) {
		x1 = 2 * n - x1 - a;
		x1 = x1 + a;
		a = -a;
	}
	void skalowanie(double k) {
		if (k > 0) {
			a *= k;
			b *= k;
		}
	}
};

int main() {
	Prostokat tablica_pros[2];
	Trojkat tablica_troj[2];
	double x, y, a, b;
	for (int i = 0; i < 2; i++) {
		cout << "Podaj wspolrzedne wierzcholka: " << endl;
		cin >> x >> y;
		cout << "Podaj wysokosc i szerokosc: " << endl;
		cin >> a >> b;
		tablica_pros[i].set(x, y, a, b);
	}
	for (int i = 0; i < 2; i++) {
		tablica_pros[i].wypisz();
	}

	for (int i = 0; i < 2; i++) {
		cout << "Podaj wspolrzedne wierzcholka: " << endl;
		cin >> x >> y;
		cout << "Podaj a i b: " << endl;
		cin >> a >> b;
		tablica_troj[i].set(x, y, a, b);
	}
	for (int i = 0; i < 2; i++) {
		tablica_troj[i].wypisz();
	}


	printf("czy chcesz dokonac zmian (skalowanie)/(symetria)? t/n\n");
	char c = 'n';
	cin >> c;
	if (c == 't') {
		printf("Ktorej metody: 3/4 ?\n");
		int m = 0;
		cin >> m;
		if (m == 3) {
			cout << "Na ktorym obiekcie? (t = trojkat, p = prostokat)";
			char obiekt;
			cin >> obiekt;
			if (obiekt == 'p') {
				cout << "Podaj indeks obiektu: ";
				int indeks;
				cin >> indeks;
				cout << "Podaj n do metody: ";
				int n;
				cin >> n;
				tablica_pros[indeks].skalowanie(n);
				tablica_pros[indeks].wypisz();
			}
			else if (obiekt == 't') {
				cout << "Podaj indeks obiektu: ";
				int indeks;
				cin >> indeks;
				cout << "Podaj n do metody: ";
				int n;
				cin >> n;
				tablica_troj[indeks].skalowanie(n);
				tablica_troj[indeks].wypisz();
			}
		}
		else if (m == 4) {
			cout << "Na ktorym obiekcie? (t = trojkat, p = prostokat)";
			char obiekt;
			cin >> obiekt;
			if (obiekt == 'p') {
				cout << "Podaj indeks obiektu: ";
				int indeks;
				cin >> indeks;
				cout << "Podaj n do metody: ";
				int n;
				cin >> n;
				tablica_pros[indeks].symetria_osiowa(n);
				tablica_pros[indeks].wypisz();
			}
			else if (obiekt == 't') {
				cout << "Podaj indeks obiektu: ";
				int indeks;
				cin >> indeks;
				cout << "Podaj n do metody: ";
				int n;
				cin >> n;
				tablica_troj[indeks].symetria_osiowa(n);
				tablica_troj[indeks].wypisz();
			}
		}
	}
	return 0;
}