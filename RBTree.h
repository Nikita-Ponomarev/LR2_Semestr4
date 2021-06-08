#pragma once
#include <iostream>
#include <string>
#include "queue.h"
#include "list.h"
using namespace std;
template <class T_key, class T_value>
class RBTree {
	class Node;
protected:
	Node* NIL;
	Node* root;
private:
	enum class Color {
		Black,
		Red
	};
	class Node {
	public:
		Color color;
		T_key key;
		Node* left;
		Node* right;
		Node* parent;
		T_value value;
		Node()
		{
			color = Color::Black;
			key = 0;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}
		Node(Node* node)
		{
			color = node->color;
			key = node->key;
			left = node->left;
			right = node->right;
			parent = node->parent;
			value = node->value;
		}
		Node(Color color, T_key key, Node* left, Node* right, Node* parent, T_value value)
		{
			Node::color = color;
			Node::key = key;
			Node::left = left;
			Node::right = right;
			Node::parent = parent;
			Node::value = value;
		}
	};
	void left_turn(Node* cur) {
		Node* y = cur->right;
		cur->right = y->left;

		if (y->left != NIL)
			y->left->parent = cur;

		if (y != NIL)
			y->parent = cur->parent;

		if (cur->parent == NIL)
			root = y;
		else if (cur == cur->parent->left)
			cur->parent->left = y;
		else
			cur->parent->right = y;

		y->left = cur;
		if (cur != NIL)
			cur->parent = y;
	}
	void right_turn(Node* y) {
		Node* cur = y->left;
		y->left = cur->right;

		if (cur->right != NIL)
			cur->right->parent = y;

		if (cur != NIL)
			cur->parent = y->parent;

		if (y->parent == NIL)
			root = cur;
		else if (y == y->parent->right)
			y->parent->right = cur;
		else
			y->parent->left = cur;

		cur->right = y;
		if (y != NIL)
			y->parent = cur;
	}
	void tree_repair(Node* z) {
		while (z != root && z->parent->color == Color::Red) {
			if (z->parent == z->parent->parent->left) {
				Node* y = z->parent->parent->right;
				if (y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->right) {
						z = z->parent;
						left_turn(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					right_turn(z->parent->parent);
				}
			}
			else {
				Node* y = z->parent->parent->left;
				if (y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left) {
						z = z->parent;
						right_turn(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					left_turn(z->parent->parent);
				}
			}
		}
		root->color = Color::Black;
	}
	void insert_node(Node* z) {
		Node* y = NIL;
		Node* cur = root;

		while (cur != NIL) {
			y = cur;
			if (z->key < cur->key)
				cur = cur->left;
			else
				cur = cur->right;
		}
		z->parent = y;

		if (y == NIL)
			root = z;
		else if (z->key < y->key)
			y->left = z;
		else
			y->right = z;

		z->left = NIL;
		z->right = NIL;
		z->color = Color::Red;
		tree_repair(z);
	}
	void delete_repair(Node* cur) {
		while (cur != root && cur->color == Color::Black) {
			if (cur == cur->parent->left) {
				Node* w = cur->parent->right;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					cur->parent->color = Color::Red;
					left_turn(cur->parent);
					w = cur->parent->right;
				}
				if (w->left->color == Color::Black && w->right->color == Color::Black) {
					w->color = Color::Red;
					cur = cur->parent;
				}
				else {
					if (w->right->color == Color::Black) {
						w->left->color = Color::Black;
						w->color = Color::Red;
						right_turn(w);
						w = cur->parent->right;
					}
					w->color = cur->parent->color;
					cur->parent->color = Color::Black;
					w->right->color = Color::Black;
					left_turn(cur->parent);
					cur = root;
				}
			}
			else {
				Node* w = cur->parent->left;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					cur->parent->color = Color::Red;
					right_turn(cur->parent);
					w = cur->parent->left;
				}
				if (w->right->color == Color::Black && w->left->color == Color::Black) {
					w->color = Color::Red;
					cur = cur->parent;
				}
				else {
					if (w->left->color == Color::Black) {
						w->right->color = Color::Black;
						w->color = Color::Red;
						left_turn(w);
						w = cur->parent->left;
					}
					w->color = cur->parent->color;
					cur->parent->color = Color::Black;
					w->left->color = Color::Black;
					right_turn(cur->parent);
					cur = root;
				}
			}
		}
		cur->color = Color::Black;
	}
	void deleteNode(Node* z) {
		Node* cur, * y;
		if (z == NIL)
			return;
		if (z->left == NIL || z->right == NIL)
			y = z;
		else {
			y = z->right;
			while (y->left != NIL) y = y->left;
		}
		if (y->left != NIL)
			cur = y->left;
		else
			cur = y->right;
		cur->parent = y->parent;
		if (y->parent != NIL) {
			if (y == y->parent->left)
				y->parent->left = cur;
			else
				y->parent->right = cur;
		}
		else
			root = cur;
		if (y != z) {
			z->key = y->key;
			z->value = y->value;
		}
		if (y->color == Color::Black)
			delete_repair(cur);

		delete y;
	}
	Node* findNode(T_key key) {
		Node* it = root;
		while (it->key != key && it != NIL) {
			if (it->key < key)
				it = it->right;
			else
				it = it->left;
		}
		if (it == NIL)
			return(nullptr);
		return it;
	}
	void recursionForClear(Node* cur) {
		if (cur->left != NIL)
			recursionForClear(cur->left);
		if (cur->right != NIL)
			recursionForClear(cur->right);
		delete cur;
	}
public:
	class iterator : public RBTree {
	private:
		queue<Node*> Q_Iter;
		T_value value;
		T_key key;
		Node* iter;
		Node* NIL;
	public:
		iterator(RBTree* tree) : iter(NULL),
			value(tree->root->value), key(tree->root->key), NIL(tree->NIL) {
			Q_Iter.push(tree->root);
		}
		const T_value& operator++() {
			if (Q_Iter.getSize() == 0)
				return NULL;
			iter = Q_Iter.front();
			Q_Iter.pop();
			if (iter->left != NIL)
				Q_Iter.push(iter->left);
			if (iter->right != NIL)
				Q_Iter.push(iter->right);
			value = iter->value;
			key = iter->key;
			return iter->value;
		}
		const T_key& operator*() {
			return key;
		}
		const T_value& getValue() {
			return value;
		}
	};
	RBTree() {
		NIL = new Node();
		root = NIL;
	}
	void insert(T_key key, T_value value) {
		Node* node = new Node(Color::Red, key, nullptr, nullptr, nullptr, value);
		insert_node(node);
	}
	T_value find(T_key key) {
		if (findNode(key))
			return findNode(key)->value;
		return 0;
	}
	void remove(T_key key) {
		deleteNode(findNode(key));
	}
	void clear() {
		recursionForClear(root);
		root = NIL;
	}
	int getSize() {
		int i = 0;
		iterator it(this);
		while (++it != NULL) {
			i++;
		}
		return i;
	}
};