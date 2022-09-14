//
//  range.cpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 04/09/2022.
//

#include "range.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

string Range::str() const noexcept {
	stringstream ss;
	
	if (start_ == end_)
		ss << (start_ + 1);
	else
		ss << (start_ + 1) << "," << (end_ + 1);
	
	return ss.str();
}

//*******************************************************************
//*                                                                 *
//*                         F R I E N D S                           *
//*                                                                 *
//*******************************************************************

std::ostream& operator<<(std::ostream& s, Range const& range) {
	std::stringstream ss;
	
	ss << range.str();
	s << ss.str();
	return s;
}

