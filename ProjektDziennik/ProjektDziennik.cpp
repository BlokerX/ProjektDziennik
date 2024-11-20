#include <iostream>
#include <windows.h> // dla funkcji SetConsoleOutputCP i SetConsoleCP

using namespace std;

struct Uczen
{
	string imie;
	string nazwisko;

	int oceny[5][5]; // 5 przedmiotów po 5 ocen

	Uczen()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
				oceny[i][j] = 0; // ustaw wszystie oceny na zero
		}
	}

	float SredniaOcen(int przedmiot)
	{
		int suma = 0, ileOcen = 0;
		for (int j = 0; j < 5; j++)
		{

			if (oceny[przedmiot][j] == 0) continue;
			suma += oceny[przedmiot][j];
			ileOcen++;
		}

		if (ileOcen == 0)
			return 0;

		return (float)suma / (float)ileOcen;
	}
};

Uczen uczniowie[10]; // tablica na 10-ciu uczniów

void UzupelnijUczniow()
{
	for (int i = 0; i < 10; i++)
	{
		cout << "Wprowadź dane ucznia nr " << i + 1 << ":\n";
		cout << "Imie: ";
		cin >> uczniowie[i].imie;
		cout << "Nazwisko: ";
		cin >> uczniowie[i].nazwisko;

		for (int k = 0; k < 5; k++)
		{
			cout << "\nPrzedmiot nr." << k + 1 << endl;

			cout << "Podaj oceny ucznia (maks. 10 ocen, wpisz 0, aby zakończyć):\n";
			for (int j = 0; j < 5; j++)
			{
				cout << "Ocena " << j + 1 << ": ";
				cin >> uczniowie[i].oceny[k][j];
				if (uczniowie[i].oceny[k][j] == 0) {
					break; // zakończ wprowadzanie ocen, jeśli wpisano 0
				}
			}
		}
		cout << "Uczeń zapisany.\n\n";
		cout << "Kontynuowac? (y/n) [instrukcja: y - tak, n - nie]" << endl;
		string w;
		cin >> w;
		if (w == "n") break;
		cout << endl;
	}
	cout << endl;
}

void WypiszListeUczniow()
{
	cout << "LISTA UCZNIÓW:\n";
	cout << "==============\n";
	for (int i = 0; i < 10; i++)
	{
		if (uczniowie[i].imie.empty() || uczniowie[i].nazwisko.empty())
			continue; // Pomijamy puste wpisy

		cout << i + 1 << "." << uczniowie[i].imie << " " << uczniowie[i].nazwisko << endl;
		cout << "PRZEDMIOTY:\n";
		for (int j = 0; j < 5; j++)
		{
			cout << j + 1 << ".Przedmiot: ";
			for (int k = 0; k < 5; k++)
			{
				cout << uczniowie[i].oceny[j][k] << " ";
			}
			cout << "[ Średnia: " << uczniowie[i].SredniaOcen(j) << " ]" << endl;
		}
		cout << endl;
	}
	cout << "==============" << endl;
	cout << endl;
}

void GenerujListeZagrozonychUczniow()
{
	cout << "Zagrożeni uczniowie:" << endl;
	int numerKolejnosci = 0;
	for (int i = 0; i < 10; i++)
	{
		if (uczniowie[i].imie.empty() || uczniowie[i].nazwisko.empty())
			continue; // Pomijamy puste wpisy

		for (int j = 0; j < 5; j++)
		{
			if (uczniowie[i].SredniaOcen(j) <= 2)
			{
				cout << ++numerKolejnosci << ". " << uczniowie[i].imie << " " << uczniowie[i].nazwisko << " ponieważ Przedmiot nr." << j + 1 << " ma średnią " << uczniowie[i].SredniaOcen(j) << endl;
				break;
			}
		}
	}
	cout << endl;
}


void Menu()
{
menuLabel:
	cout << "-------------------------\n";
	cout << "Wybierz co chcesz zrobić:\n";
	cout << "-------------------------\n";
	cout << "1.Wypisz liste uczniow\n";
	cout << "2.Generuj liste zagrożonych uczniow\n";
	cout << "0.Wyjdź\n";
	cout << "-------------------------\n";
	int wybor = -1;
	cin >> wybor;
	cout << "-------------------------\n";
	cout << endl;

	switch (wybor)
	{
	case 1:
		WypiszListeUczniow();
		break;

	case 2:
		GenerujListeZagrozonychUczniow();
		break;

	case 0:
		exit(0);
		break;

	default:
		cout << "Wybierz liczby z przedziału 0-2" << endl;
		goto menuLabel;
		break;
	}
	Menu();
}

int main()
{
	// Ustaw kodowanie konsoli na UTF-8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	// Wymuszenie polskiej lokalizacji
	setlocale(LC_ALL, "Polish");

	UzupelnijUczniow();

	Menu();

	return 0;
}