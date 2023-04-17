#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <conio.h>

void log_message(const char* message, const char* player_name)
{
	time_t current_time;
	struct tm* time_info;
	char time_string[20];

	time(&current_time);
	time_info = localtime(&current_time);
	strftime(time_string, sizeof(time_string), "%d.%m.%Y %H:%M:%S", time_info);

	if (player_name != NULL)
	{
		fprintf(stderr, "%s %s, gracz: %s\n", time_string, message, player_name);
	}
	else
	{
		fprintf(stderr, "%s %s\n", time_string, message);
	}
}

void gra(char nick[], int liczba) {
	int correct = 0;
	double duration;

	char plik[100] = "gra-";
	strcat(plik, nick);
	strcat(plik, ".txt");
	printf("plik : %s\n", plik);
	FILE* file = fopen(plik, "a");
	if (file == NULL)
	{
		log_message("Nie uda³o siê otworzyæ pliku", nick);
		return;
	}
	log_message("Rozpoczêcie gry", nick);
	for (int i = 0; i < liczba; i++) {
		correct = 0;
		int a = rand() % 26 + 97;
		int b = rand() % 26 + 97;
		while (a == b || abs((a-b))<2) {
			b = rand() % 26 + 97;
		}
		if (a < b) {
			printf("%c-%c\n", char(a), char(b));
			char odp = _getch();
			while (isspace(odp)) {
				odp = _getch();
			}
			if (int(odp) > a && int(odp)<b) {
				correct = 1;
			}
			fprintf(file, "%c %c %c %d\n", a, b, odp, correct);
		}
		else {
			printf("%c-%c\n", char(b), char(a));
			char odp = _getch();
			while (isspace(odp)) {
				odp = _getch();
			}
			if (int(odp)<a && int(odp)>b) {
				correct = 1;
			}
			fprintf(file, "%c %c %c %d\n", b, a, odp , correct);
		}
	}
	log_message("Zakonczenie gry", nick);
}

int main() {
	char odp;
	int liczba = 0;
	char nick[20], log[] = "log.txt";

	if (freopen("log.txt", "a", stderr) == NULL)
	{
		fprintf(stderr, "Nie uda³o siê otworzyæ pliku log.txt\n");
		exit(1);
	}
	log_message("Start programu", NULL);

	srand(time(NULL));
	do {
		printf("Podaj nick: ");
		scanf_s("%s", &nick, 20);
		log_message("Podanie nicku", nick);
		printf("Podaj liczbe par: ");
		scanf_s("%d", &liczba);
		log_message("Podanie liczby", nick);
		
		gra(nick, liczba);

		printf("Czy chcesz zagrac jeszcze raz? (t/n): ");
		scanf(" %c", &odp);
	} while (odp == 't');

	return 0;
}