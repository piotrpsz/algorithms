//
//  parser.hpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 04/09/2022.
//

#ifndef parser_hpp
#define parser_hpp

/*------- include files:
-------------------------------------------------------------------*/
#include <stdio.h>
#include <vector>
#include <string>
#include "token.hpp"
#include "shared.hpp"

using TokensVector = std::vector<std::shared_ptr<Token>>;

class Parser final {
	enum class Set { A, B };
	
	std::vector<std::string> const stringsA_;
	std::vector<std::string> const stringsB_;
	TokensVector same_;
	TokensVector others_;
	
public:
	Parser(std::vector<std::string> const&, std::vector<std::string> const&);
	Parser(std::string const&, std::string const&);

	bool run();
	void print_diff() const noexcept;
	std::string print_lines(Set const, int const, int const) const noexcept;
	
private:
	TokensVector same_text(LinesVector const&, LinesVector const&) const noexcept;
	TokensVector diff_text(TokensVector const&) const noexcept;
	
	int dist(int const start, int const end) const noexcept {
		return (end >= start) ? (end - start + 1) : 0;
	}
};

#endif /* parser_hpp */
