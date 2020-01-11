/**
 * csv_converter.hpp
 * this module's purpose is to parse csv to data object and back
 **/

#ifndef CSV_CONVERTER
#define CSV_CONVERTER

#include <string>
#include <vector>
#include <logger.hpp>
#include <avl_tree.hpp>
#include <fstream>

using namespace std;

namespace autoTrader
{

class CsvConverter
{
public:
    CsvConverter(string csvFileName);
    ~CsvConverter();
    vector<void *> CsvToVector();
    AvlTree *csvToAvlTree();
    int vectorToCsv(vector<void *> data);
    int avlTreeToCsv(AvlTree *data);
private:
    fstream csvFile;
};

}//namespace autoTrader

#endif //CSV_CONVERTER