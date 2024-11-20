#include <iostream>
#include <string>
#include <windows.h> // dla funkcji SetConsoleOutputCP i SetConsoleCP

using namespace std;

#define maxUczniow 10
#define liczbaPrzedmiotow 6
#define maxOcenNaPrzedmiot 10

struct Uczen
{
	string imie;
	string nazwisko;

	int oceny[liczbaPrzedmiotow][maxOcenNaPrzedmiot];

	Uczen()
	{
		imie.clear();
		nazwisko.clear();
		for (int i = 0; i < liczbaPrzedmiotow; i++)
		{
			for (int j = 0; j < maxOcenNaPrzedmiot; j++)
				oceny[i][j] = 0; // ustaw wszystie oceny na zero
		}
	}

	float SredniaOcen(int przedmiot)
	{
		int suma = 0, ileOcen = 0;
		for (int j = 0; j < maxOcenNaPrzedmiot; j++)
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

Uczen uczniowie[maxUczniow]; // tablica na 10-ciu uczniów
int nastepneWolneMiejsceNaUcznia = 0;

void DodajUczniow()
{
	if (nastepneWolneMiejsceNaUcznia >= maxUczniow)
	{
		cout << "<- --- Lista przepełniona --- ->" << endl;
		return;
	}

	while (nastepneWolneMiejsceNaUcznia < maxUczniow)
	{
		cout << "Wprowadź dane ucznia nr " << nastepneWolneMiejsceNaUcznia + 1 << ":\n";

		cout << "Imie: ";
		cin >> uczniowie[nastepneWolneMiejsceNaUcznia].imie;

		cout << "Nazwisko: ";
		cin >> uczniowie[nastepneWolneMiejsceNaUcznia].nazwisko;

		for (int k = 0; k < liczbaPrzedmiotow; k++)
		{
			cout << "\nPrzedmiot nr." << k + 1 << endl;

			cout << "Podaj oceny ucznia (maks. 10 ocen, wpisz 0, aby zakończyć):\n";
			for (int j = 0; j < maxOcenNaPrzedmiot; j++)
			{
				cout << "Ocena " << j + 1 << ": ";
				cin >> uczniowie[nastepneWolneMiejsceNaUcznia].oceny[k][j];
				if (uczniowie[nastepneWolneMiejsceNaUcznia].oceny[k][j] == 0) {
					break; // zakończ wprowadzanie ocen, jeśli wpisano 0
				}
			}
		}

		nastepneWolneMiejsceNaUcznia++;
		cout << "Uczeń zapisany.\n\n";

		if (nastepneWolneMiejsceNaUcznia < maxUczniow)
		{
			cout << "Kontynuowac? (y/n) [instrukcja: y - tak, n - nie]" << endl;

			string w;
			cin >> w;

			if (w == "n") break;

			cout << endl;
		}
		else
		{
			cout << "<- --- Lista przepełniona --- ->" << endl;
			break;
		}
	}
	cout << endl;
	return;
}

void WypiszListeUczniow()
{
	cout << "LISTA UCZNIÓW:\n";
	cout << "==============\n";
	if (!nastepneWolneMiejsceNaUcznia)
		cout << "- brak -\n";
	else
		for (int i = 0; i < nastepneWolneMiejsceNaUcznia; i++)
		{
			if (uczniowie[i].imie.empty() || uczniowie[i].nazwisko.empty())
			{
				continue; // Pomijamy puste wpisy
			}

			cout << i + 1 << "." << uczniowie[i].imie << " " << uczniowie[i].nazwisko << endl;
			cout << "PRZEDMIOTY:\n";
			for (int j = 0; j < liczbaPrzedmiotow; j++)
			{
				cout << j + 1 << ".Przedmiot: ";
				for (int k = 0; k < maxOcenNaPrzedmiot; k++)
				{
					cout << uczniowie[i].oceny[j][k] << " ";
				}
				cout << "[ Średnia: " << uczniowie[i].SredniaOcen(j) << " ]" << endl;
			}
			cout << endl;
		}
	cout << "==============" << endl;
	cout << endl;

	return;
}

void GenerujListeZagrozonychUczniow()
{
	cout << "Zagrożeni uczniowie:" << endl;
	if (!nastepneWolneMiejsceNaUcznia)
		cout << "- brak -";
	else
		for (int i = 0; i < nastepneWolneMiejsceNaUcznia; i++)
		{
			if (uczniowie[i].imie.empty() || uczniowie[i].nazwisko.empty())
				continue; // Pomijamy puste wpisy

			for (int j = 0; j < liczbaPrzedmiotow; j++)
			{
				double sredniaUcznia = uczniowie[i].SredniaOcen(j);
				if (sredniaUcznia <= 2 && sredniaUcznia > 0)
				{
					cout << i+1 << ". " << uczniowie[i].imie << " " << uczniowie[i].nazwisko << " ponieważ Przedmiot nr." << j + 1 << " ma średnią " << sredniaUcznia << endl;
					break;
				}
			}
		}
	cout << endl;

	return;
}

void UsunUcznia(int uczenDoUsunecia)
{
	int n = 0;
	cout << "Potwierdź (aby kontynuować wprowadź 1, aby anulować wprowadź 0):\n";
	cin >> n;

	if (!n || nastepneWolneMiejsceNaUcznia <= 0)
	{
		cout << "\nOperacja usuwania została anulowana!\n";
		return;
	}

	// Przesunięcie listy tak aby nie było luki dla żadnego ucznia
	for (int i = uczenDoUsunecia; i < maxUczniow - 2; i++)
	{
		uczniowie[i].imie = uczniowie[i + 1].imie;
		uczniowie[i].nazwisko = uczniowie[i + 1].nazwisko;

		// Wyzerowanie ocen na nieistniejącym już uczniu:
		for (int j = 0; j < liczbaPrzedmiotow; j++)
		{
			for (int k = 0; k < maxOcenNaPrzedmiot; k++)
			{
				uczniowie[i].oceny[j][k] = uczniowie[i + 1].oceny[j][k];
			}
		}
	}

	// Usuwanie ostatniego wpisanego indeksu i cofnięcie go:
	--nastepneWolneMiejsceNaUcznia;
	uczniowie[nastepneWolneMiejsceNaUcznia] = Uczen();

	//// Alternatywa
	//uczniowie[nastepneWolneMiejsceNaUcznia].imie.clear();
	//uczniowie[nastepneWolneMiejsceNaUcznia].nazwisko.clear();

	//// Wyzerowanie ocen na nieistniejącym już uczniu:
	//for (int i = 0; i < liczbaPrzedmiotow; i++)
	//{
	//	for (int j = 0; j < maxOcenNaPrzedmiot; j++)
	//	{
	//		uczniowie[nastepneWolneMiejsceNaUcznia].oceny[i][j] = 0;
	//	}
	//}

	return;
}

void UsunUcznia()
{
	int nrUcznia;
	cout << "Wprowadź index ucznia ktorego chcesz usunac (aby anulować operację wprowadź 0): " << endl;
	cin >> nrUcznia;

	if (!nrUcznia)
	{
		cout << "\nOperacja usuwania została anulowana pomyślnie!\n";
		return;
	}

	if (nrUcznia < 1 || nrUcznia > nastepneWolneMiejsceNaUcznia)
	{
		cout << "\nOperacja usuwania została anulowana!\nPodany index wyszedł poza zakres już dostępnych.\n";
		return;
	}

	UsunUcznia(nrUcznia-1);
}

void Menu()
{
menuLabel:
	cout << "-------------------------\n";
	cout << "Wybierz co chcesz zrobić:\n";
	cout << "-------------------------\n";
	cout << "1.Wypisz liste uczniow\n";
	cout << "2.Generuj liste zagrożonych uczniow\n";
	cout << "3.Dodaj uczniow\n";
	cout << "4.Usun ucznia\n";
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

	case 3:
		DodajUczniow();
		break;

	case 4:
		UsunUcznia();
		break;

	case 0:
		exit(0);
		break;

	default:
		cout << "Wybierz liczby z przedziału 0-4" << endl;
		goto menuLabel;
		break;
	}

	Menu();

	return;
}

int main()
{
	// Ustaw kodowanie konsoli na UTF-8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	// Wymuszenie polskiej lokalizacji
	setlocale(LC_ALL, "Polish");

	Menu();

	return 0;
}