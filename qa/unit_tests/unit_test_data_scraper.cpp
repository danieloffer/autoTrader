/*
* unit_test_data_scraper.cpp
*/

#include <data_scraper.hpp>
#include <iostream>

using namespace autoTrader;
using namespace std;

int main()
{
	DataScraper ds;
	string res;
	string searchResult = ds.searchTicker("at&t");

	res = ds.getStockData(searchResult, DataScraper::DAILY_ADJ);

	cout << res;

	return 0;
}