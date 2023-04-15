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

int is_file_exist(char* plik) {
	FILE* f = fopen(plik, "r");
	if (f) {
		fclose(f);
		return 1;
	}
	return 0;
}

void log_message(const char* filename, const char* msg) {
	FILE* log_file;
	time_t now;
	struct tm* tm_info;
	char timestamp[20];

	time(&now);
	tm_info = localtime(&now);
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

	log_file = fopen(filename, "a");
	if (log_file == NULL) {
		perror("Error opening log file");
		exit(EXIT_FAILURE);
	}

	fprintf(log_file, "%s: %s\n", timestamp, msg);
	fclose(log_file);
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	char nick[20], log[]="log.txt";
	int liczba, correct=0;
	time_t start, end;
	double duration;
	char sciezka[256];
	strcpy(sciezka, argv[0]);

	char* last_slash = strrchr(sciezka, '\\'); 
	if (last_slash != NULL) {
		*(last_slash + 1) = '\0';  // kasujemy nazwê pliku wykonywalnego
	}
	else {
		sciezka[0] = '\0';  
	}


	printf("Podaj nick: ");
	log_message(log, "Pobranie nicku.");
	scanf_s("%s", &nick,20);
	printf("Podaj liczbe: ");
	log_message(log, "Pobranie liczby.");
	while (scanf_s("%d", &liczba) < 1 || liczba > 10) {
		printf("Zly przedzial, podaj inna: ");
		while (getchar() != '\n')
			;
	}
	start = time(NULL);
	for (int i = 0; i < liczba; i++) {
		int n = rand() % 26 + 97;
		printf("%c\n", char(n));
		log_message(log, "Wylosowanie litery.");
		char odp = _getch();
		while (isspace(odp)) {
			odp = _getch();
		}
		if (odp == char(n)) {
			correct++;
			log_message(log, "Poprawne wcisniecie.");
			continue;
		}
		printf("zle!\n");
		log_message(log, "Nieprawidlowe wcisniecie.");
	}
	end = time(NULL);
	duration = difftime(end, start);
	printf("liczba poprawnych : %d, czas : %.2lf sec\n", correct, duration);

	strcat(nick, ".txt"); 
	if (is_file_exist(nick)!=1) {
		strcat(sciezka, nick);
		printf("plik nie istnieje, plik jest zakladany w %s\n", sciezka);
	}
	FILE* f = fopen(nick, "a");
	fprintf(f, "czas : %0.2lf ilosc trafien : %d\n", duration, correct);
	fclose(f);

	return 0;
}