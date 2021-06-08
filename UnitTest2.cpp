#include "pch.h"
#include "CppUnitTest.h"
#include "../4sem_LR2/HaffmanTree.h"
#include "../4sem_LR2/list.h"
#include "../4sem_LR2/queue.h"
#include "../4sem_LR2/RBTree.h"
#include "../4sem_LR2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(Coder_Test)
		{
			string str = "omuamua";
			list<HfTree*> Hf_node;
			RBTree<char, int> tree;
			int t_val;
			for (int i = 0; i < str.length(); i++) {
				if (tree.find(str[i]) == 0) {
					tree.insert(str[i], 1);
				}
				else {
					t_val = tree.find(str[i]);
					tree.remove(str[i]);
					tree.insert(str[i], t_val + 1);
				}
			}
			RBTree<char, int>::iterator it(&tree);
			++it;
			for (int i = 0; i < tree.getSize(); i++) {
				Hf_node.push(new HfTree(*it, it.getValue()));
				++it;
			}
			while (Hf_node.getSize() != 1) {
				Hf_node.sort();
				Hf_node.push(new HfTree(Hf_node.pop(0), Hf_node.pop(1)));
			}
			HfTree* hfTree = Hf_node.pop(0);
			hfTree->Coder(hfTree->getRoot());
			RBTree<char, string> Hf_chart;
			hfTree->toRB(&Hf_chart, hfTree->getRoot());
			Assert::IsTrue(Hf_chart.find('o') == "00" && Hf_chart.find('m') == "01" && Hf_chart.find('u') == "10" && Hf_chart.find('a') == "11");
		}
		TEST_METHOD(Decode_Test)
		{
			string str = "Forget it";
			list<HfTree*> Hf_node;
			RBTree<char, int> tree;
			int t_value;
			for (int i = 0; i < str.length(); i++) {
				if (tree.find(str[i]) == 0) {
					tree.insert(str[i], 1);
				}
				else {
					t_value = tree.find(str[i]);
					tree.remove(str[i]);
					tree.insert(str[i], t_value + 1);
				}
			}
			RBTree<char, int>::iterator it(&tree);
			++it;
			for (int i = 0; i < tree.getSize(); i++) {
				Hf_node.push(new HfTree(*it, it.getValue()));
				++it;
			}
			while (Hf_node.getSize() != 1) {
				Hf_node.sort();
				Hf_node.push(new HfTree(Hf_node.pop(0), Hf_node.pop(1)));
			}
			HfTree* hfTree = Hf_node.pop(0);
			hfTree->Coder(hfTree->getRoot());
			RBTree<char, string> Hf_chart;
			hfTree->toRB(&Hf_chart, hfTree->getRoot());
			string encode_str = "";
			for (int i = 0; i < str.length(); i++) {
				encode_str += Hf_chart.find(str[i]);
			}
			Assert::IsTrue(hfTree->decode(encode_str) == "Forget it");
		}
	};
}