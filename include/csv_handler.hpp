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
   
    /*
    *CsvHandler Ctor. Does not actually open the file for reading yet
    *param csvFileName - the csv file to handle.(full path)
    *Since the file is opened and close per read/write action which is performed in the entire file,
    *no Dtor is required to close resources. A default Dtor is enough
    */
    CsvHandler(string csvFileName);

    /*
    *reads the csv file line by line from the file specified in the Ctor
    *Returns the csv as a vector of vectors of strings (table of string values)
    */
    vector<vector<string> > read();

    /*
    *reads a csv file sent as a string
    *Returns the csv as a vector of vectors of strings (table of string values)
    */
    vector<vector<string> > parseCsvString(string csvAsString);

    /*
    *Writes the csv file line by line back to the file name specified in the Ctor
    *Returns 0 for success, 1 otherwise
    */
    int write(vector<vector<string> > data);
private:
    string csvFileName;
    SingleLogger *log;
};

}//namespace autoTrader

#endif //CSV_HANDLER