#pragma once
#include <stdlib.h>
#include <string>
#include "list.h"
#include "queue.h"
#include "RBTree.h"
using namespace std;
class HfTree {
private:
	class HfNode {
	public:
		HfNode* Parent;
		HfNode* Left;
		HfNode* Right;
		string Code;
		char Symbol;
		HfNode(HfNode* parent, HfNode* left, HfNode* right, char value) :
			Parent(parent), Left(left), Right(right), Symbol(value), Code("") {};
		void setParent(HfNode* parent) {
			Parent = parent;
		}
		void setCode(string code) {
			Code = code;
		}
	};
	int freq;
	HfNode* Root;
public:
	HfNode* getRoot() {
		return Root;
	}
	int get_freq() {
		return freq;
	}
	HfTree(char value, int power) :
		freq(power) {
		Root = new HfNode(nullptr, nullptr, nullptr, value);
	}
	HfTree(HfTree* leftTree, HfTree* rightTree) {
		freq = leftTree->get_freq() + rightTree->get_freq();
		Root = new HfNode(nullptr, leftTree->getRoot(), rightTree->getRoot(), NULL);
		Root->Left->setParent(Root);
		Root->Right->setParent(Root);
	}
	void Coder(HfNode* node)
	{
		if (node != nullptr)
		{
			if (node->Right != nullptr) {
				node->Right->Code = node->Code + "1";
				Coder(node->Right);
			}
			if (node->Left != nullptr) {
				node->Left->Code = node->Code + "0";
				Coder(node->Left);
			}
		}
	}
	void toRB(RBTree<char, string>* tree, HfNode* node)
	{
		if (node != nullptr)
		{
			if (node->Right != nullptr) {
				toRB(tree, node->Right);
			}
			if (node->Left != nullptr) {
				toRB(tree, node->Left);
			}
			if (node->Symbol != 0)
				tree->insert(node->Symbol, node->Code);

		}
	}
	string decode(string encode_str) {
		string out_str = "";
		HfNode* node = Root;
		for (int i = 0; i < encode_str.length(); i++) {
			if (encode_str[i] == '0')
				node = node->Left;
			else if (encode_str[i] == '1')
				node = node->Right;
			if (node->Symbol != 0) {
				out_str += node->Symbol;
				node = Root;
			}
		}
		return out_str;
	}
};