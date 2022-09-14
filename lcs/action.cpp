//
//  action.cpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 04/09/2022.
//

#include "action.hpp"
#include <string>

std::string action_name(Action a) {
	switch (a) {
		using enum Action;;
		case Same:
			return "Same";
		case Added:
			return "Added";
		case Deleted:
			return "Deleted";
		case Changed:
			return "Changed";
	}
}

std::string action_marker(Action a) {
	switch (a) {
		using enum Action;;
		case Added:
			return "a";
		case Deleted:
			return "d";
		case Changed:
			return "c";
		default:
			return "?";
	}
}
