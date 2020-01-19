/*
* unit_test_data_scraper.cpp
*/

#include <avl_tree.hpp>
#include <iostream>

using namespace autoTrader;
using namespace std;

int cmpFunc(int *a, int *b, void *param)
{
	return a-b;
}

int main()
{
	AvlTree<int> *intTree = new AvlTree<int>(cmpFunc, NULL);
	string s = (intTree->isEmpty()) ? "The tree is empty" : "The tree is NOT empty";
	cout << s << endl;

	size_t size = intTree->size();
	cout << "The tree's size: " << size << endl;

	int i = 5;
	intTree->insert(&i);

	delete intTree;

	return 0;
}