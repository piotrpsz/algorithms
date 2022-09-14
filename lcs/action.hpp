//
//  action.hpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 04/09/2022.
//

#ifndef action_hpp
#define action_hpp

#include <stdio.h>
#include <string>

enum class Action {
	Same,
	Added,
	Deleted,
	Changed
};

extern std::string action_marker(Action a);


#endif /* action_hpp */
