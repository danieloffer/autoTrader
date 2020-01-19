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
template <typename T>
class CsvConverter
{
public:
    CsvConverter(string csvFileName);
    ~CsvConverter();
    vector<T *> CsvToVector();
    AvlTree<T> *csvToAvlTree();
    int vectorToCsv(vector<T *> data);
    int avlTreeToCsv(AvlTree<T> *data);
private:
    fstream csvFile;
};

}//namespace autoTrader

#endif //CSV_CONVERTER