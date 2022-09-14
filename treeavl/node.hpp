#pragma once

#include <cstdio>
#include <memory>
#include <iostream>

class Node; // forward declaration
using NodePtr = std::shared_ptr<Node>;

struct Data {
private:
    int64_t key_;
    int64_t value_;
public:
    Data(int64_t const key, int64_t value)
    : key_(key)
    , value_(value)
    {}
    ~Data() = default;
    Data(Data const&) = default;
    Data(Data&&) = default;
    Data& operator=(Data const&) = default;
    Data& operator=(Data&&) = delete;

    friend std::ostream& operator<<(std::ostream& s, Data const& data) {
        s << data.key_ << " => " << data.value_;
        return s;
    }
};



class Node {
    Data data_;
    int balance_;
    NodePtr parent_;
    NodePtr child_[2];

public:
    Node(std::shared_ptr<Node> const& parent, int64_t const key, int64_t const value)
    : data_{Data(key, value)}
    , balance_{0}
    , parent_{nullptr}
    , child_{nullptr, nullptr}
    {}

    ~Node() = default;
    Node(Node const&) = delete;
    Node(Node&&) = delete;
    Node& operator=(Node const&) = delete;
    Node& operator=(Node&&) = delete;

    NodePtr single_rotation(NodePtr const, int const) noexcept;
    NodePtr double_rotation(NodePtr const, int const) noexcept;
    void adjust_balance(NodePtr const, int const, int const) noexcept;
    NodePtr insert_balance(NodePtr const, int const) noexcept;
    std::pair<NodePtr, bool> remove_balance(NodePtr const, int const) noexcept;
    void print(std::string const&, int const) const noexcept;
};