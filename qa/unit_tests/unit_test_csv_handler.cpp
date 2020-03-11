/*
* unit_test_data_scraper.cpp
*/

#include <csv_handler.hpp>
#include <iostream>
#include <entry.hpp>
#include <trade_entry.hpp>
#include <portfolio_entry.hpp>

using namespace autoTrader;
using namespace std;

#define READ_FILE_NAME "/home/daniel/autoTrader/qa/unit_tests/test.csv"
#define WRITE_FILE_NAME "/home/daniel/autoTrader/qa/unit_tests/new_test.csv"

int main()
{
	CsvHandler *CsvHandlerReader = new CsvHandler(READ_FILE_NAME);
	vector<vector<string> > vec = {};
	vec = CsvHandlerReader->read();

	time_t doneAt = time(NULL) - 100;

	Entry *portfolioEntry = new PortfolioEntry(vec[1], doneAt);
	cout << portfolioEntry->toString() << endl;
	vector<string> vec1 = portfolioEntry->entryToVector();

	Entry *portfolioEntry1 = new PortfolioEntry(vec[1]);
	cout << portfolioEntry1->toString() << endl;

	// Entry *tradeEntry2 = new PortfolioEntry(vec[1], doneAt, 5);
	// cout << tradeEntry2->toString() << endl;

	CsvHandler *CsvHandlerWriter = new CsvHandler(WRITE_FILE_NAME);
	CsvHandlerWriter->write(vec);

	string csvAsString = "id,name,height\n1,aaa,1.75\n2,bbb,1.85\n3,ccc,1.95";
	vec = CsvHandlerWriter->parseCsvString(csvAsString);

	delete CsvHandlerReader;
	delete CsvHandlerWriter;
	delete portfolioEntry;
	delete portfolioEntry1;
	// delete tradeEntry2;

	return 0;
}