//
//  shared.hpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 06/09/2022.
//

#ifndef shared_hpp
#define shared_hpp

#include <stdio.h>
#include <vector>
#include <string>

using Vector2D = std::vector<std::vector<int>>;
using LinesVector = std::vector<std::string>;

namespace shared {

extern std::string adjust(std::string const&, int const, bool const);
extern Vector2D lcs(LinesVector const&, LinesVector const&) noexcept;
extern std::string file2str(std::string const&);
extern LinesVector split(std::string const&) noexcept;

}

#endif /* shared_hpp */
