#include "node.hpp"

using namespace std;

NodePtr Node::single_rotation(NodePtr const root, int const dir) noexcept {
	int const opp = 1 - dir;
	auto const parent = root->parent_;
	auto const node = root->child_[opp];
	
	root->child_[opp] = node->child_[dir];
	if (root->child_[opp])
		root->child_[opp]->parent_ = root;
	
	node->child_[dir] = root;
	if (node->child_[dir])
		node->child_[dir]->parent_ = node;
	
	node->parent_ = parent;
	return node;
}


NodePtr Node::double_rotation(NodePtr const root, int const dir) noexcept {
	int const opp = 1 - dir;
	auto const parent = root->parent_;

	auto node = root->child_[opp]->child_[dir];
	
	root->child_[opp]->child_[dir] = node->child_[opp];
	if (root->child_[opp]->child_[dir])
		root->child_[opp]->child_[dir]->parent_ = root->child_[opp];

	node->child_[opp] = root->child_[opp];
	if (node->child_[opp])
		node->child_[opp]->parent_ = node;
	
	root->child_[opp] = node;
	if (root->child_[opp])
		root->child_[opp]->parent_ = root;
	
	
	node = root->child_[opp];
	
	root->child_[opp] = node->child_[dir];
	if (root->child_[opp])
		root->child_[opp]->parent_ = root;
	
	node->child_[dir] = root;
	if (node->child_[dir])
		node->child_[dir]->parent_ = node;
	
	node->parent_ = parent;
	return node;
}

void Node::adjust_balance(NodePtr const root, int const dir, int const balance) noexcept {
	const int opp = 1 - dir;
	auto const n = root->child_[dir];
	auto const nn = n->child_[opp];
	
	if (nn->balance_ == 0) {
		root->balance_ = 0;
		n->balance_ = 0;
	} else if (nn->balance_ == balance) {
		root->balance_ = -balance;
		n->balance_ = 0;
	} else {
		root->balance_ = 0;
		n->balance_ = balance;
	}
	nn->balance_ = 0;
}

NodePtr Node::insert_balance(NodePtr const root, int const dir) noexcept {
	const int opp = 1 - dir;
	const int balance = 2 * dir - 1;
	auto const n = root->child_[dir];
	
	if (n->balance_ == balance) {
		root->balance_ = 0;
		n->balance_ = 0;
		return single_rotation(root, opp);
	}
	adjust_balance(root, dir, balance);
	return double_rotation(root, opp);
}

pair<NodePtr, bool> Node::remove_balance(NodePtr const root, int const dir) noexcept {
	const int opp = 1 - dir;
	const int balance = 2 * dir - 1;
	auto const n = root->child_[opp];
	
	if (n->balance_ == -balance) {
		root->balance_ = 0;
		n->balance_ = 0;
		return make_pair(single_rotation(root, dir), false);
	}
	
	if (n->balance_ == balance) {
		adjust_balance(root, opp, -balance);
		return std::make_pair(double_rotation(root, dir), false);
	}
	
	root->balance_ = -balance;
	n->balance_ = balance;
	return std::make_pair(single_rotation(root, dir), true);
}

void Node::print(string const& prefix, int const dir) const noexcept {
    if (dir == -1)
        cout << prefix << "(" << this << ")" << data_ << " (parent: " << parent_ << ")" << endl;
    else
        cout << prefix << "[" << dir << "]" << " (" << this << ")" << " : " << data_ << " (parent: " << parent_ << ")" << endl;

	if (child_[0])
		child_[0]->print(prefix + "   ", 0);
	if (child_[1])
		child_[1]->print(prefix + "   ", 0);
}