#include "tree.hpp"
using namespace std;


/*********************************************************************
*                                                                    *
*                          P R I V A T E                             *
*                                                                    *
*********************************************************************/

std::pair<NodePtr, bool> Tree::insertR(NodePtr const root, int64_t const key, int64_t const value) noexcept {
	if (!root) {
		NodePtr node(new Node(root, key, value));
		if (node) count_ += 1;
		return std::make_pair(node, false);
	}
	
	if (root->data_.key_ == key) {
		root->data_.value_ = value;
		return std::make_pair(root, true);
	}
	
	int const dir = (root->data_.key_ < key) ? 1 : 0;
	auto const r = insertR(root->child_[dir], key, value);
	root->child_[dir] = r.first;
	root->child_[dir]->parent_ = root;
	if (r.second)
		return std::make_pair(root, true);
	
	root->balance_ += (2 * dir - 1);

	if (root->balance_ == 0)
		return std::make_pair(root, true);
	else if (root->balance_ == 1 || root->balance_ == -1)
		return std::make_pair(root, false);
	return std::make_pair(root->insert_balance(root, dir), true);
}

std::pair<NodePtr, bool> Tree::removeR(NodePtr const root, int64_t key) noexcept {
	if (!root) {
		return std::make_pair(nullptr, false);
	}
	
	if (root->data_.key_ == key) {
		count_ -= 1;
		if (!root->child_[0])
			return std::make_pair(root->child_[1], false);
		if (!root->child_[1])
			return std::make_pair(root->child_[0], false);
		
		auto node = root->child_[0];
		while (node->child_[1])
			node = node->child_[1];
		
		root->data_.key_ = node->data_.key_;
		key = node->data_.key_;
	}
	
	int const dir = (root->data_.key_ < key) ? 1 : 0;
	auto const r = removeR(root->child_[dir], key);
	root->child_[dir] = r.first;
	if (r.second)
		return std::make_pair(root, true);
	
	root->balance_ += (1 - 2 * dir);
	switch (root->balance_) {
		case -1:
		case 1:
			return std::make_pair(root, true);
		case 0:
			return std::make_pair(root, false);
	}
	return root->remove_balance(root, dir);
}

pair<int64_t, bool> Tree::value(int64_t const key) const noexcept {
    for (auto node = root_; node; ) {
        if (node->data_.key_ == key)
            return make_pair(node->data_.value_, true);
        
        node = node->child_[(key > node->data_.key_) ? 1 : 0];
    }
    return std::make_pair(0, false);
}

bool Tree::contains(int64_t const key) const noexcept {
    auto const [_, ok] = value(key);
    return ok;
}

NodePtr Tree::min_key_node() const noexcept {
    auto node = root_;
    while (node->child_[0])
        node = node->child_[0];
    return node;
}

NodePtr Tree::max_key_node() const noexcept {
    auto node = root_;
    while (node->child_[1])
        node = node->child_[1];
    return node;
}
