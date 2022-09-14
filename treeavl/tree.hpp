#pragma once

#include <cstdio>
#include <memory>
#include "node.hpp"

class Tree final {
    NodePtr root_;
    int64_t count_;

public:
    Tree() = default;
    ~Tree() = default;

    Tree(Tree const&) = default;
    Tree& operator=(Tree&&) = delete;

    /*
	//copy
	Tree(Tree const& rhs) noexcept
    : root_(rhs.root_)
    , count_(rhs.count_)
	{}

    // move
    Tree(Tree&& rhs) noexcept
    : root_(std::move(rhs.root_))
    , count_(std::exchange(rhs.count_, 0))
    {}

    // copy assignment
	Tree& operator=(Tree const& rhs) noexcept {
		if (this != std::addressof(rhs)) {
			root_ = rhs.root_;
			count_ = rhs.count_;
		}
		return *this;
	}
    */
};