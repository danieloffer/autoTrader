/**
 * csv_handler.hpp
 * this module's purpose is to parse csv to data object and back
 **/

#ifndef CSV_HANDLER
#define CSV_HANDLER

#include <string>
#include <cstring>
#include <vector>
#include <logger.hpp>
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

namespace autoTrader
{
class CsvHandler
{
public:
    CsvHandler(string csvFileName);
    vector<vector<string> > read();
    vector<vector<string> > parseCsvString(string csvAsString);
    int write(vector<vector<string> > data);
private:
    string csvFileName;
    SingleLogger *log;
};

}//namespace autoTrader

#endif //CSV_HANDLER