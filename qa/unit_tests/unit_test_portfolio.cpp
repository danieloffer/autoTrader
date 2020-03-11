/*
* unit_test_data_scraper.cpp
*/

#include <csv_handler.hpp>
#include <iostream>
#include <entry.hpp>
#include <portfolio.hpp>
#include <portfolio_entry.hpp>

using namespace autoTrader;
using namespace std;

#define READ_FILE_NAME "/home/daniel/autoTrader/qa/unit_tests/portfolio.csv"
#define WRITE_FILE_NAME "/home/daniel/autoTrader/qa/unit_tests/portfolio.csv"

int main()
{
	Portfolio *portfolio = new Portfolio();

	delete portfolio;
	
	return 0;
}