#include "list.h"
#include "queue.h"
#include "RBTree.h"
#include "HaffmanTree.h"
#include <string>
#include <iostream>
using namespace std;
string to_binary_string(char n)
{
	string result;
	do
	{
		result += ('0' + (n % 2));
		n = n / 2;
	} while (n > 0);
	return result;
}
int main() {
	string str;
	list<HfTree*> HfList;
	RBTree<char, int> rbtree;
	cout << "Enter string:" << endl;
	getline(cin, str);
	if (str.length() == 0)
	{
		cout << "String must have at least one symbol!" << endl;
		return 0;
	}
	int t_value;
	for (int i = 0; i < str.length(); i++) {
		if (rbtree.find(str[i]) == 0) {
			rbtree.insert(str[i], 1);
		}
		else {
			t_value = rbtree.find(str[i]);
			rbtree.remove(str[i]);
			rbtree.insert(str[i], t_value + 1);
		}
	}
	RBTree<char, int>::iterator it(&rbtree);
	++it;
	cout << "\nsymbol frequency: \n";
	for (int i = 0; i < rbtree.getSize(); i++) {
		HfList.push(new HfTree(*it, it.getValue()));
		cout << *it << " " << it.getValue() << endl;
		++it;
	}
	while (HfList.getSize() != 1) {
		HfList.sort();
		HfList.push(new HfTree(HfList.pop(0), HfList.pop(1)));
	}
	HfTree* HaffTree = HfList.pop(0);
	cout << "\nInitial string: ";
	for (int i = 0; i < str.length(); i++) {
		cout << endl;
		for (int j = 0; j < (8 - to_binary_string(str[i]).length()); j++)
		{
			if (str[i] == ' ')
			{
				cout << "00" << to_binary_string(str[i]);
				j++;
			}
			else
				cout << "0" << to_binary_string(str[i]) + " " + str[i];
		}
	}
	HaffTree->Coder(HaffTree->getRoot());
	RBTree<char, string> Hf_chart;
	HaffTree->toRB(&Hf_chart, HaffTree->getRoot());
	cout << "\n\nInitial string weight: " << 8 * str.length() << " bits";
	string encode_str = "";
	cout << "\n\nResult string: ";
	for (int i = 0; i < str.length(); i++) {
		encode_str += Hf_chart.find(str[i]);
		cout << Hf_chart.find(str[i]);
		cout << " ";
	}
	cout << "\n\nResult string weight: " << encode_str.length() << " bits";
	cout << "\n\nDecode string: ";
	cout << HaffTree->decode(encode_str);
	cout << "\n\nCompression ratio: ";
	cout << float(8 * str.length()) / float(encode_str.length()) << endl;
	return 0;
}