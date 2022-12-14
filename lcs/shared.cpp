//
//  shared.cpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 06/09/2022.
//

#include "shared.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace shared {
using namespace std;

string adjust(string const& text, int const length, bool const left) {
	auto const n = text.size();
	if (n >= length)
		return text;
	
	string prefix(length - n, ' ');
	return (left) ? text + prefix : prefix + text;
}

/**
 Znalezienie informacji o wspólnych liniach z użyciem algorytmu LCS
 w przesłanych dwóch zbiorach (A i B) linii tekstu.
 \param rows_a wektor linii tekstu zbioru A,
 \param rows_b wektor linii tekstu zbioru B
 \return tablica 2D (wektor wektorów) z informacji o wynikach porównania.
 */
Vector2D lcs(LinesVector const& rowsA, LinesVector const& rowsB) noexcept {
	auto const m = rowsA.size();
	auto const n = rowsB.size();

	Vector2D lens(m+1);
	for (auto i = 0; i < (m+1); i++)
		lens[i] = vector<int>(n+1);
	
	for (auto i = 0; i < m; i++)
		for (auto  j = 0; j < n; j++)
			if (rowsA[i] == rowsB[j])
				lens[i+1][j+1] = 1 + lens[i][j];
			else
				lens[i+1][j+1] = max(lens[i+1][j], lens[i][j+1]);

	return lens;
}

/**
 Odczyt całego pliku do stringa.
 UWAGA: na końcu tekstu dodajemy dodatkowy znak nowej linii.
 \param fpath ścieżka do pliku do odczytu.
 \return tekst zawierający zawartość wskazanego pliku.
 */
string file2str(string const& fpath) {
	ostringstream ss;
	
	if (ifstream f(fpath, ios::binary); f.is_open()) {
		try {
			ss << f.rdbuf() << '\n';
		}
		catch (ifstream::failure& err) {
			cerr << err.exception::what() << endl;
		}
		return ss.str();
	}
	throw std::runtime_error("can't open a file");
}
	
	

/**
 Podział tekstu na linie.
 \param text zawiera tekst do podziału na linie.
 \return wektor linii tekstu.
 */
LinesVector split(string const& text) noexcept {
	LinesVector tokens;
	std::string line; 
	
	for (int i = 0; i < text.size(); i++) {
		auto const c = text[i];
		if (c == '\n') {
			tokens.push_back(std::move(line));
			line.clear();	// nie mamy gwarancji co zawiera line po move
			continue;
		}
		line.push_back(c);
	}
	
	return tokens;
}

}
