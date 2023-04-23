#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <cmath>
#include <corecrt_math_defines.h>

using namespace std;

class Trapez {
private:
    double x1, y1, x2, y2, b, h;

public:
    void set(double x, double y, double b, double h) {
        if (b > 0) {
            this->b = b;
        }
        else {
            this->b = 1;
            cout << "Bok podstawy musi byæ wiêkszy od zera. Przyjêto wartoœæ domyœln¹: 1.\n";
        }

        if (h > 0) {
            this->h = h;
        }
        else {
            this->h = 1;
            cout << "Wysokoœæ musi byæ wiêksza od zera. Przyjêto wartoœæ domyœln¹: 1.\n";
        }

        this->x1 = x;
        this->y1 = y;
        this->x2 = x + b;
        this->y2 = y;
    }

    void print() {
        cout << "Wspolrzedne pierwszego wierzcholka: (" << x1 << ", " << y1 << ")\n";
        //cout << "Wspolrzedne drugiego wierzcholka: (" << this->x2 << ", " << this->y2 << ")\n";
        printf("Wspolrzedne drugiego wierzcholka: (%.2lf,%.2lf)\n", x2, y2);
        cout << "Dlugosc podstawy: " << this->b << "\n";
        cout << "Wysokosc: " << this->h << "\n";

        double s = sqrt(pow(this->b / 2, 2) + pow(this->h, 2)); // d³ugoœæ boku skoœnego

        double x3 = this->x1 + (this->b / 4);
        double y3 = this->y1 + this->h;

        double x4 = this->x1 + (3 * this->b / 4);
        double y4 = this->y1 + this->h;

        cout << "Wspolrzedne trzeciego wierzcholka: (" << x3 << ", " << y3 << ")\n";
        cout << "Wspolrzedne czwartego wierzcholka: (" << x4 << ", " << y4 << ")\n";
        cout << "Dlugosc boku skosnego: " << s << "\n";
    }

    void symetria_osiowa(double n) {
        x1 = 2 * n - x1;
    }
};

int main() {
    Trapez trapez;
    double x, y, b, h;
    cout << "Podaj x: ";
    cin >> x;
    cout << "Podaj y: ";
    cin >> y;
    cout << "Podaj b: ";
    cin >> b;
    cout << "Podaj h: ";
    cin >> h;
    trapez.set(x, y, b, h);
    trapez.print();
    double n;
    cout << "Podaj argument dla metody symetrii" << endl;
    cin >> n;
    trapez.symetria_osiowa(n);
    trapez.print();

    return 0;
}