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


class MojaKlasa {
	char** email;
	int ile;

public:
	MojaKlasa* nast;
	MojaKlasa(int x);
	MojaKlasa(MojaKlasa& mk);	// konstruktor kopiuj¹cy
	void setemail(const char* adres, int idx) { strcpy(email[idx], adres); }
	char* getemail(int idx) { return email[idx]; }
	int getile() { return ile; }

};
MojaKlasa::MojaKlasa(int x) {
	nast = NULL;
	email = new char* [ile = x];
	for (int i = 0; i < ile; i++) email[i] = new char[100];
}

MojaKlasa::MojaKlasa(MojaKlasa& mk) {
	email = new char* [mk.ile];
	ile = mk.ile;
	nast = mk.nast;
	for (int i = 0; i < ile; i++) {
		email[i] = new char[100];
		strcpy(email[i], mk.email[i]);
	}
}



class Wykladowca {
	MojaKlasa* glowa;
public:
	Wykladowca() : glowa(NULL) {}
	Wykladowca(char* plik) : glowa(NULL) {
		dodaj_klase(plik);
	}
	Wykladowca(Wykladowca& w) {
		if (w.glowa == NULL) {
			glowa = NULL;
			return;
		}
		glowa = new MojaKlasa(*w.glowa);
		MojaKlasa* p = w.glowa->nast;
		MojaKlasa* q = glowa;
		while (p != NULL) {
			q->nast = new MojaKlasa(*p);
			p = p->nast;
			q = q->nast;
		}
	}
	~Wykladowca() {
		MojaKlasa* p = glowa;
		while (p != NULL) {
			MojaKlasa* q = p;
			p = p->nast;
			delete q;
		}
	}

	void dodaj_klase(char* plik) {
		FILE* f = fopen(plik, "r");
		if (f == NULL) {
			printf("failed to open a file\n");
			exit(0);
		}
		int n = 0, i = 0;
		while (!feof(f)) {
			char ff[100];
			fscanf(f, "%s", ff);
			n++;
		}
		rewind(f);
		glowa = new MojaKlasa(n);
		while (!feof(f)) {
			char buf[100];
			fscanf(f, "%s", buf);
			glowa->setemail(buf, i);
			i++;
		}
		fclose(f);
	}

	void wypisz() {
		MojaKlasa* p = glowa;
		while (p != NULL) {
			int n = p->getile();
			for (int i = 0; i < n; i++) {
				printf("%s\n", p->getemail(i));
			}
			p = p->nast;
		}
	}
};


int main() {
	/*MojaKlasa MK(3);
	MK.setemail("k.trojanowski@uksw.edu.pl", 0);
	MojaKlasa MK2(MK);
	printf("%s\n", MK2.getemail(0));
	MK.setemail("m.mikolajczyk@uksw.edu.pl", 0);
	printf("%s\n", MK2.getemail(0));*/

	char napis[] = "adresy.txt";
	Wykladowca* wykladowca = new Wykladowca(napis);
	wykladowca->wypisz();
	Wykladowca* w1 = new Wykladowca(*wykladowca);
	delete(wykladowca);
	w1->wypisz();
	delete(w1);


	system("pause");
	return 0;
}