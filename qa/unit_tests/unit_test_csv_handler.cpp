/*
* unit_test_data_scraper.cpp
*/

#include <csv_handler.hpp>
#include <iostream>

using namespace autoTrader;
using namespace std;

#define READ_FILE_NAME "/home/daniel/autoTrader/test.csv"
#define WRITE_FILE_NAME "/home/daniel/autoTrader/new_test.csv"

int main()
{
	CsvHandler *CsvHandlerReader = new CsvHandler(READ_FILE_NAME);
	vector<vector<string> > vec = {};
	vec = CsvHandlerReader->read();

	CsvHandler *CsvHandlerWriter = new CsvHandler(WRITE_FILE_NAME);
	CsvHandlerWriter->write(vec);

	string csvAsString = "id,name,height\n1,aaa,1.75\n2,bbb,1.85\n3,ccc,1.95";
	vec = CsvHandlerWriter->parseCsvString(csvAsString);

	delete CsvHandlerReader;
	delete CsvHandlerWriter;

	return 0;
}