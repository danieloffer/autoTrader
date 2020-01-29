/*
* unit_test_data_scraper.cpp
*/

#include <avl_tree.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace autoTrader;
using namespace std;

int cmpFunc(int *a, int *b, void *param)
{
	return ((*a)-(*b));
}

int printFunc(int *a, void *param)
{
	cout << "pre order: " + to_string(*a) << endl;

	return 0;
}

int incrementFunc(int *a, void *param)
{
	*a += *((int*)param);

	return 0;
}

void test1()
{
	AvlTree<int> *intTree = new AvlTree<int>(cmpFunc, NULL);
	string s = (intTree->isEmpty()) ? "The tree is empty" : "The tree is NOT empty";
	cout << s << endl;

	size_t size = intTree->size();
	cout << "The tree's size: " << size << endl;

	int arr[10] = {5, 6, 5 ,3, 2, 1, 5, 8, 42, -5};
	for (int i = 0; i < 10; ++i)
	{
		intTree->insert(&arr[i]);

		s = (intTree->isEmpty()) ? "The tree is empty" : "The tree is NOT empty";
		cout << s << endl;	

		size = intTree->size();
		cout << "The tree's size: " << size << endl;
	}

	intTree->forEach(printFunc, NULL);

	vector<int *> vec = intTree->multiFind(&arr[0]);
	if (!vec.empty())
	{
		cout << "vec size " << vec.size() << endl;
		for (size_t i = 0; i < vec.size(); i++)
		{
			cout << "element " << i << " = " << *vec[i] << endl;
		}
	}
	else
	{
		cout << "vec returned empty" << endl;
	}
	int *found = NULL;
	for (int i = 0; i < 10; ++i)
	{
		found = intTree->find(&arr[i]);
		if (found)
		{
			cout << "found " << arr[i] << endl;
			(*found)++;
		}
	}

	int *notFound = NULL;
	for (int i = 50; i < 60; ++i)
	{
		found = intTree->find(&i);
		if (!notFound)
		{
			cout << "not found " << i << endl;
		}
		else
		{
			cout << "mistakenly found " << i << endl;
		}
	}

	intTree->forEach(printFunc, NULL);

	int inc = 3;
	intTree->forEach(incrementFunc, &inc);

	delete intTree;

}

void test2()
{
	AvlTree<int> *intTree = new AvlTree<int>(cmpFunc, NULL);
	int insertErr = 0;
	int rmvErr = 0;
	int arr[10000];

	srand (time(NULL));

	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		arr[i] = ((rand() % 10000) - 5000);
	}

	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		intTree->insert(&arr[i]);

		if (intTree->size() != (i +1))
		{
			insertErr++;
		}
	}

	if (insertErr)
	{
		cout << "Insert Error occurred" << endl;
	}

	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		intTree->remove(&arr[i]);

		if (intTree->size() != (sizeof(arr) / sizeof(arr[0]) - (i + 1)))
		{
			rmvErr++;
		}
	}

	if (rmvErr || !intTree->isEmpty())
	{
		cout << "Remove Error occurred" << endl;
	}


	delete intTree;
}

int main()
{
	test1();
	test2();	
	return 0;
}