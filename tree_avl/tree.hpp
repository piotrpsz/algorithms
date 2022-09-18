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

    // copy
    Tree(Tree const&) = delete;
    // move
    Tree(Tree&&) = delete;
    // copy assignment
    Tree& operator=(Tree const&) = delete;
    // move assignment
    Tree& operator=(Tree&&) = delete;
    
    void insert(int64_t const key, int64_t const value) noexcept {
        root_ = insertR(root_, key, value).first;
    }
    void remove(const int64_t key) noexcept {
	    root_ = removeR(root_, key).first;
    }
    std::pair<int64_t, bool> min_key() const noexcept {
        if (auto const node = min_key_node(); node)
            return std::make_pair(node->data_.key_, true);
        return std::make_pair(0, false);
    }

    std::pair<int64_t, bool> max_key() noexcept {
	    if (auto const node = max_key_node(); node)
		    return std::make_pair(node->data_.key_, true);
	
	    return std::make_pair(0, false);
    }

    std::pair<int64_t, bool> value(int64_t const) const noexcept;
    bool contains(int64_t const) const noexcept;
    
    void print() const noexcept {
        root_->print("", -1);
    }

private:
    std::pair<NodePtr, bool> insertR(NodePtr const, const int64_t, const int64_t) noexcept;
    std::pair<NodePtr, bool> removeR(NodePtr const, int64_t) noexcept;
    NodePtr min_key_node() const noexcept;
    NodePtr max_key_node() const noexcept;
};