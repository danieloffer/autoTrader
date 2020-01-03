/*
* unit_test_data_scraper.cpp
*/

#include <data_scraper.hpp>

using namespace autoTrader;

int main()
{
	DataScraper ds;
	ds.getStockData("T", DataScraper::E_OperationType::DAILY_ADJ);

	return 0;
}