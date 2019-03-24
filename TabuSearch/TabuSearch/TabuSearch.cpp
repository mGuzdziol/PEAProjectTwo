// TabuSearch.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "ReadFile.h"
#include "TabS.h"
#include <string>

int main()
{
	int m_size;
	int **cities;
	int opt=0;
	int stop = 240;
	int choice = 1;
	int hood = 1;
	std::string fileName = "Brak wczytanego pliku!";

	std::cout << "PEA-Tabu Search, Maksymilian Guzdziol 233534\n\n";
	std::cout << "Nazwa otwartego pliku: " << fileName << "\n";
	std::cout << "Najlepsze znane rozwiazanie: " << opt << "\n";
	std::cout << "Kryterium stopu: " << stop << "\n";
	std::cout << "Wybrane sasiedztwo: ";
	if (hood == 1)
		std::cout << "SWAP\n";
	if (hood == 2)
		std::cout << "INSERT\n";
	if (hood == 3)
		std::cout << "INVERT\n";
	std::cout << "\nWybierz opcje:\n" <<"1. Wczytaj graf z pliku\n" << "2. Wybierz definicje sasiedztwa\n" << "3. Wprowadz kryterium stopu\n" << "4. Wykonaj przeszukiwanie Tabu\n" << "0. Wyjscie\n\n";
	std::cout << "Twoj wybor: "; std::cin >> choice; std::cout << "\n\n";

	ReadFile file;

	cities = 0;

	while (choice != 0) {
		switch (choice)
		{
		case 1: {
			std::cout << "Podaj nazwe pliku: "; std::cin >> fileName;
			cities = file.openFile(m_size, opt, fileName); 
			system("cls");
		}
				break;

		case 2:
		{
			std::cout << "1. SWAP\n" << "2. INSERT\n" << "3. INVERT\n";
			std::cout << "Wybor: "; std::cin >> hood;
			system("cls");
		}
				break;

		case 3: {
			std::cout << "Wprowadz czas wykonywania algorytmu: "; std::cin >> stop; 
			system("cls"); 
		}
				break;

		case 4:
		{
			TabS ts(m_size, cities, opt, stop, hood);

			ts.tabuSearch();

		//	ts.printBestCost();
		}
		default:
			break;
		}

		std::cout << "\n\nPEA-Tabu Search, Maksymilian Guzdziol 233534\n\n";
		std::cout << "Nazwa otwartego pliku: " << fileName << "\n";
		std::cout << "Najlepsze znane rozwiazanie: " << opt << "\n";
		std::cout << "Kryterium stopu: " << stop << "\n";
		std::cout << "Wybrane sasiedztwo: ";
		if (hood == 1)
			std::cout << "SWAP\n";
		if (hood == 2)
			std::cout << "INSERT\n";
		if (hood == 3)
			std::cout << "INVERT\n";
		std::cout << "\nWybierz opcje:\n" << "1. Wczytaj graf z pliku\n" << "2. Wybierz definicje sasiedztwa\n" << "3. Wprowadz kryterium stopu\n" << "4. Wykonaj przeszukiwanie Tabu\n" << "0. Wyjscie\n\n";
		std::cout << "Twoj wybor: "; std::cin >> choice; std::cout << "\n\n";
	}

	

	/*for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			std::cout << cities[i][j];
			std::cout << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";*/

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
