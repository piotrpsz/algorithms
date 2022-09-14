//
//  range.hpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 04/09/2022.
//

#ifndef range_hpp
#define range_hpp

#include <stdio.h>
#include <string>
#include <iostream>


class Range final {
	int start_;
	int end_;
	
public:
	Range() : start_(), end_()
	{}
	explicit Range(int const pos) : start_(pos), end_(pos)
	{}
	explicit Range(int const pos1, int const pos2) : start_(pos1), end_(pos2)
	{}
	
	Range(Range const&) = delete;
	Range(Range&&) = delete;
	Range& operator=(Range const&) = delete;
	Range& operator=(Range&&) = delete;
	~Range() = default;
	
	int start() const noexcept { return start_; }
	int end() const noexcept { return end_; }
	
	void start(int const value) noexcept { start_ = value; }
	void end(int const value) noexcept { end_ = value; }
	
	bool is_below(int const pos) const noexcept {
		return ((start_ - 1) == pos);
	}
	
	std::string str() const noexcept;

	friend std::ostream& operator<<(std::ostream&, Range const&);
};


#endif /* range_hpp */
