//
//  token.cpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 04/09/2022.
//

/*------- include files:
-------------------------------------------------------------------*/
#include "token.hpp"
#include "shared.hpp"
#include <string>
#include <sstream>

using namespace std;

string Token::diffstr() const noexcept {
	stringstream ss;
	
	auto ra = a()->str();
	auto rb = b()->str();
	
	ss << ra << ' ' << action_marker(action_) << ' ' << rb;
	return ss.str();
	
}

ostream& operator<<(ostream& s, Token const& token) {
	stringstream ss;
	
	auto a = token.a()->str();
	auto b = token.b()->str();
	
	ss << adjust(a, 7, false) << " - " << adjust(b, 7, true);
	
	s << ss.str();
	return s;
}

ostream& operator<<(ostream& s, Token const * const token) {
	stringstream ss;
	
	auto ra = token->a()->str();
	auto rb = token->b()->str();
	
	ss << ra << ' ' << action_marker(token->action_) << ' ' << rb;
	s << ss.str();
	
	return s;
}
