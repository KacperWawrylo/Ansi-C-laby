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

#define N 2

using namespace std;

class Trapez {
private:
	double x1, y1, b, h, a;

public:
	Trapez* nast;
	Trapez() {
		x1 = 0;
		y1 = 0;
		b = 1;
		h = 1;
		a = 1;
		nast = NULL;
	}
	Trapez(double x_, double y_, double b_, double h_, double a_) {
		if (b_ > 0) {
			this->b = b_;
		}
		else {
			this->b = 1;
			cout << "Bok podstawy musi byc wiekszy od zera. Przyjeto wartosc domyslna: 1.\n";
		}
		if (a_ > 0 && a_ <= b) {
			a = a_;
		}
		else {
			this->a = b;
			cout << "Bok drugiej podstawy musi byc wiekszy od zera lub wiekszy od b. Przyjeto wartosc domyslna: b.\n";
		}
		if (h_ > 0) {
			this->h = h_;
		}
		else {
			this->h = 1;
			cout << "Wysokoœæ musi byæ wiêksza od zera. Przyjêto wartoœæ domyœln¹: 1.\n";
		}

		x1 = x_;
		y1 = y_;
		nast = NULL;
	}
	Trapez(Trapez& mk) {
		x1 = mk.x1;
		y1 = mk.y1;
		b = mk.b;
		h = mk.h;
		a = mk.a;
		nast = mk.nast;
	}
	~Trapez() {
		delete nast;
	}
	void set(double x, double y, double b_, double h_, double a_) {
		if (b_ > 0) {
			this->b = b_;
		}
		else {
			this->b = 1;
			cout << "Bok podstawy musi byc wiekszy od zera. Przyjeto wartosc domyslna: 1.\n";
		}
		if (a_ > 0 && a_ <= b) {
			a = a_;
		}
		else {
			this->a = b;
			cout << "Bok drugiej podstawy musi byc wiekszy od zera lub wiekszy od b. Przyjeto wartosc domyslna: b.\n";
		}
		if (h_ > 0) {
			this->h = h_;
		}
		else {
			this->h = 1;
			cout << "Wysokoœæ musi byæ wiêksza od zera. Przyjêto wartoœæ domyœln¹: 1.\n";
		}

		x1 = x;
		y1 = y;
	}

	void print() {
		double x2 = x1 + ((b - a) / 2);
		double y2 = y1 + h;
		double x3 = this->x1 + (this->b / 4);
		double y3 = this->y1 + this->h;

		double x4 = this->x1 + a;
		double y4 = this->y1 + this->h;
		cout << "\nTrapez\nWspolrzedne pierwszego wierzcholka: (" << x1 << ", " << y1 << ")\n";
		cout << "Wspolrzedne drugiego wierzcholka: (" << x2 << ", " << y2 << ")\n";
		cout << "Wspolrzedne trzeciego wierzcholka: (" << x3 << ", " << y3 << ")\n";
		cout << "Wspolrzedne czwartego wierzcholka: (" << x4 << ", " << y4 << ")\n";
		cout << "Dlugosc podstawy: " << this->b << "\n";
		cout << "Dlugosc 2 podstawy: " << this->a << "\n";
		cout << "Wysokosc: " << this->h << "\n";
	}

	void symetria_osiowa(double n) {
		x1 = 2 * n - x1 - b;
	}
};

class Prostokat {
private:
	double x1, y1, a, b; //a dlugosc boku rownoleglego z ox , b z oy
public:
	Prostokat* nast;
	Prostokat() {
		x1 = 0;
		y1 = 0;
		a = 1;
		b = 1;
		nast = NULL;
	}
	void set(double x, double y, double a_, double b_) {
		if (x < 0) {
			cout << "Zla wartosc x, ustawiam domyslna 1" << endl;
			x = 1;
		}
		if (y < 0) {
			cout << "Zla wartosc y, ustawiam domyslna 1" << endl;
			y = 1;
		}
		if (a_ < 0) {
			cout << "Zla wartosc a, ustawiam domyslna 1" << endl;
			a_ = 1;
		}
		if (b_ < 0) {
			cout << "Zla wartosc b, ustawiam domyslna 1" << endl;
			b_ = 1;
		}
		x1 = x;
		y1 = y;
		a = a_;
		b = b_;
	}
	Prostokat(double x, double y, double a_, double b_) {
		if (x < 0) {
			cout << "Zla wartosc x, ustawiam domyslna 1" << endl;
			x = 1;
		}
		if (y < 0) {
			cout << "Zla wartosc y, ustawiam domyslna 1" << endl;
			y = 1;
		}
		if (a_ < 0) {
			cout << "Zla wartosc a, ustawiam domyslna 1" << endl;
			a_ = 1;
		}
		if (b_ < 0) {
			cout << "Zla wartosc b, ustawiam domyslna 1" << endl;
			b_ = 1;
		}
		x1 = x;
		y1 = y;
		a = a_;
		b = b_;
		nast = NULL;
	}
	Prostokat(Prostokat& mk) {
		x1 = mk.x1;
		y1 = mk.y1;
		a = mk.a;
		b = mk.b;
		nast = mk.nast;
	}
	~Prostokat() {
		delete nast;
	}
	void print() {
		double x2 = x1 + a;
		double y2 = y1;

		double x3 = x1;
		double y3 = y1 + b;

		double x4 = x1 + a;
		double y4 = y1 + b;

		cout << "\nProstokat\nWspolrzedne pierwszego wierzcholka: (" << x1 << ", " << y1 << ")\n";
		cout << "Wspolrzedne drugiego wierzcholka: (" << x2 << ", " << y2 << ")\n";
		cout << "Wspolrzedne trzeciego wierzcholka: (" << x3 << ", " << y3 << ")\n";
		cout << "Wspolrzedne czwartego wierzcholka: (" << x4 << ", " << y4 << ")\n";
		cout << "Dlugosc podstawy: " << a << "\n";
		cout << "Wysokosc: " << b << "\n";
		cout << "Pole powierzchni: " << a * b << "\n";
	}
	void symetria_osiowa(double n) {
		x1 = 2 * n - x1 - a;
	}
	void skalowanie(double k) {
		if (k > 0) {
			a = a * k;
			b = b * k;
		}
	}
};

class blejtram {
public:
	Trapez* trapez;
	Prostokat* prostokat;

	blejtram() {
		trapez = NULL;
		prostokat = NULL;
	}

	~blejtram() {
		delete trapez;
		delete prostokat;
	}
	Trapez* dodaj_trapez(Trapez* t) {
		if (trapez == NULL) {
			trapez = t;
			return t;
		}
		Trapez* glowa = trapez;
		while (glowa->nast != NULL) {
			glowa = glowa->nast;
		}
		glowa->nast = t;
		t->nast = NULL;
		return t;
	}
	Prostokat* dodaj_prostakat(Prostokat* t) {
		if (prostokat == NULL) {
			prostokat = t;
			return t;
		}
		Prostokat* glowa = prostokat;
		while (glowa->nast != NULL) {
			glowa = glowa->nast;
		}
		glowa->nast = t;
		t->nast = NULL;
		return t;
	}

	void symetria_osiowa(double n) {
		if (trapez != NULL) {
			Trapez* glowa = trapez;
			while (glowa != NULL) {
				glowa->symetria_osiowa(n);
				glowa = glowa->nast;
			}
		}
		if (prostokat != NULL) {
			Prostokat* glowa = prostokat;
			while (glowa != NULL) {
				glowa->symetria_osiowa(n);
				glowa = glowa->nast;
			}
		}
	}

	void wypisz() {
		if (trapez != NULL) {
			Trapez* glowa = trapez;
			while (glowa != NULL) {
				glowa->print();
				glowa = glowa->nast;
			}
		}
		if (prostokat != NULL) {
			Prostokat* glowa = prostokat;
			while (glowa != NULL) {
				glowa->print();
				glowa = glowa->nast;
			}
		}
	}
};

int main() {
	Trapez* t1 = new Trapez;
	Trapez* t = new Trapez(0, 0, 4, 4, 2);
	Trapez* z = new Trapez(*t);
	Prostokat* pro = new Prostokat(1, 1, 2, 5);
	delete t;
	blejtram* bt = new blejtram();
	bt->dodaj_trapez(t1);
	bt->dodaj_prostakat(pro);
	bt->dodaj_trapez(z);
	bt->wypisz();
	bt->symetria_osiowa(-1);
	bt->wypisz();

	delete bt;

	

	system("pause");
	return 0;
}