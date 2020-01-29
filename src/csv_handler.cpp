/*
* csv_handler.cpp
*/

#include <csv_handler.hpp>
#include <sstream>

using namespace std;

namespace autoTrader
{
	CsvHandler::CsvHandler(string csvFileName): csvFileName(csvFileName) , log(Logger::getInstance())
{
    log->LOG("csvHandler ctor");
}

vector<vector <string> > CsvHandler::read()
{
    ifstream csvFileReader(csvFileName);
    vector<vector<string> > dataVec = {};
    string line = "";
    string lineBreak = "";

    if (csvFileReader.is_open())
    {
        while (getline(csvFileReader, line))
        {    
            vector<string> tempVec;
            boost::algorithm::split(tempVec, line, boost::is_any_of(","));
            dataVec.push_back(tempVec);
        }

        log->LOG("csvHandler read from file: " + csvFileName);

        csvFileReader.close();
    }

    return dataVec;
}

vector<vector<string> > CsvHandler::parseCsvString(string csvAsString)
{
    vector<vector<string> > dataVec = {};
    string line = "";
    char lineBreak = '\n';


    stringstream ss(csvAsString);
    string token;
    while (std::getline(ss, line, lineBreak)) {
        std::vector<std::string> tempVec;
        boost::algorithm::split(tempVec, line, boost::is_any_of(","));
        dataVec.push_back(tempVec);
    }

    log->LOG("csvHandler parsed csv from string");

    return dataVec;
}


int CsvHandler::write(vector<vector<string> > data)
{
    ofstream csvFileWriter(csvFileName);
    if (!csvFileWriter.is_open())
    {
        log->LOG("csvHandler write: couldn't open file for writing " + csvFileName);
        return 1;
    }

    size_t i;
    size_t j;
    for (i = 0; i < data.size(); ++i)
    {
        for (j = 0; j < (data[i].size() - 1); ++j)
        {
            csvFileWriter << data[i][j] << ",";
        }
        csvFileWriter << data[i][j];
        csvFileWriter << endl;
    }

    log->LOG("csvHandler wrote to file: " + csvFileName);

    csvFileWriter.close();

    return 0;
}
    
}//namespace autoTrader