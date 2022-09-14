//
//  token.hpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 04/09/2022.
//

#ifndef token_hpp
#define token_hpp

/*------- include files:
-------------------------------------------------------------------*/
#include <stdio.h>
#include "range.hpp"
#include "action.hpp"

class Token {
	std::shared_ptr<Range> a_;
	std::shared_ptr<Range> b_;
	Action action_;
	
public:
	Token()
	: a_(), b_(), action_(Action::Same)
	{}
	Token(std::shared_ptr<Range> a, std::shared_ptr<Range> b, Action const action = Action::Same)
	: a_(a), b_(b), action_(action)
	{}
	
	Token(Token const&) = delete;
	Token(Token&&) = delete;
	Token& operator=(Token const&) = delete;
	Token& operator=(Token&&) = delete;
	~Token() = default;
	
	Range* a() const noexcept { return a_.get(); }
	Range* b() const noexcept { return b_.get(); }
	Action action() const noexcept { return action_; }
	
	std::string diffstr() const noexcept;
	
	friend std::ostream& operator<<(std::ostream&, Token const&);
	friend std::ostream& operator<<(std::ostream&, Token const * const);
};

#endif /* token_hpp */
