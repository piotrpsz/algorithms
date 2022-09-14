//
//  parser.cpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 04/09/2022.
//

#include "parser.hpp"
#include "token.hpp"
#include "shared.hpp"
#include <sstream>
#include <fstream>

using namespace std;

Parser::Parser(std::vector<std::string> const& stringsA, std::vector<std::string> const& stringsB)
: stringsA_(stringsA), stringsB_(stringsB)
{}

/**
 Compare content of two files (a and B).
 \param path_a path of file A,
 \param path_b path of file B
 */
Parser::Parser(string const& path_a, string const& path_b) {
	auto const stringsA = shared::split(shared::file2str(path_a));
	auto const stringsB = shared::split(shared::file2str(path_b));

	this->~Parser();
	new (this) Parser(stringsA, stringsB);
}

bool Parser::run() {
	if (auto const same = same_text(stringsA_, stringsB_); !same.empty()) {
		same_ = same;
		if (auto const others = diff_text(same); !others.empty()) {
			others_ = others;
			return !others.empty();
		}
	}
	return false;
}

/**
 Drukowanie w konsoli informacji o liniach, które są różne.
 Drukowanie jest w sposób, tak jak robi to program diff.
 */
void Parser::print_diff() const noexcept {
	for (auto const& item : others_) {
		auto const token = item.get();
		cout << token << endl;
		switch (token->action()) {
			case Action::Changed:
				cout << print_lines(Set::A, token->a()->start(), token->a()->end()) << endl;
				cout << "---" << endl;
				cout << print_lines(Set::B, token->b()->start(), token->b()->end()) << endl;
				break;
			case Action::Deleted:
				cout << print_lines(Set::A, token->a()->start(), token->a()->end()) << endl;
				break;
			case Action::Added:
				cout << print_lines(Set::B, token->b()->start(), token->b()->end()) << endl;
				break;
			default:
				// do nothing
				break;
		}
	}
}

/**
 Drukowanie w konsoli wkazanego zakresu linii ze wskazanego zbioru.
 \param set wskazanie zbioru linii,
 \param start numer pierwszej linii w zbiorze,
 \param end numer ostatniej linii w zbiorze
 */
string Parser::print_lines(Set const set, int const start, int const end) const noexcept {
	stringstream ss;
	
	auto const is_a = (set == Set::A);
	auto const& data = is_a ? stringsA_ : stringsB_;
	auto const prefix = is_a ? "< " : "> ";
	
	for (int i = start; i < end; i++)
		ss << prefix << data[i] << endl;
	ss << prefix << data[end];
	
	return ss.str();
}

/**
 Wyznaczenie różnych linii i określenie ich statusu (dodana, usunieta, zmieniona).
 \param same wektor tokenów opisujących linie wspólne.
 \return wektor tokenów opisujących linie różne.
 */
TokensVector Parser::diff_text(TokensVector const& same) const noexcept {
	TokensVector tokens;	// result container
	Token* prv = nullptr;	// previous token
	
	for (int i = 0; i < same.size(); i++) {
		auto& token = same[i];
		
		auto const startA = prv ? (prv->a()->end() + 1) : 0;
		auto const endA = token->a()->start() - 1;
		auto const nA = dist(startA, endA);
		
		auto const startB = prv ? (prv->b()->end() + 1) : 0;
		auto const endB = token->b()->start() - 1;
		auto const nB = dist(startB, endB);
		
		if (nA > 0 || nB > 0) {
			if (nA == 0 && nB > 0) {
				auto rangeA = shared_ptr<Range>(i ? new Range(same[i-1]->a()->end()) : new Range());
				auto rangeB = shared_ptr<Range>(new Range(startB, endB));
				tokens.emplace_back(new Token(rangeA, rangeB, Action::Added));
			}
			else if (nA > 0 && nB == 0) {
				auto const rangeA = shared_ptr<Range>(new Range(startA, endA));
				auto const rangeB = shared_ptr<Range>(i ? new Range(same[i-1]->b()->end()) : new Range());
				tokens.emplace_back(new Token(rangeA, rangeB, Action::Deleted));
			}
			else {
				const auto rangeA = make_shared<Range>(startA, endA);
				const auto rangeB = make_shared<Range>(startB, endB);
				tokens.emplace_back(new Token(rangeA, rangeB, Action::Changed));
			}
		}
		
		prv = token.get();
	}
	
	return tokens;
}

/**
 Wyszukanie wspólnych linii tekstu w dwóch zbiorach (A i B).
 \param rows_a wektor linii tekstu zbioru A
 \param rows_b wektor linii tekstu zbioru B
 \return wektor obiektów 'Token' zawierających informacje o wspólnych liniach.
 */
TokensVector Parser::same_text(LinesVector const& rows_a, LinesVector const& rows_b) const noexcept {
	TokensVector tokens;
	
	auto const lens = shared::lcs(rows_a, rows_b);
	auto i = static_cast<int>(rows_a.size()) - 1;
	auto j = static_cast<int>(rows_b.size()) - 1;
	
	while (i >= 0 && j >= 0) {
		if (stringsA_[i] == stringsB_[j]) {
			if (!tokens.empty()) {
				const auto token = tokens.back().get();
				if (token->a()->is_below(i) && token->b()->is_below(j)) {
					token->a()->start(i);
					token->b()->start(j);
				}
				else {
					const auto a = make_shared<Range>(i);
					const auto b = make_shared<Range>(j);
					tokens.push_back(make_shared<Token>(a, b));
				}
			}
			else {
				const auto a = make_shared<Range>(i);
				const auto b = make_shared<Range>(j);
				tokens.push_back(make_shared<Token>(a, b));
			}
			--i;
			--j;
		}
		else if (lens[i+1][j] > lens[i][j+1])
			--j;
		else
			--i;
	}
	reverse(tokens.begin(), tokens.end());
	return tokens;
}






