/**
 * portfolio.hpp
 * this module's purpose is to represent a portfolio
 **/

#ifndef PORTFOLIO
#define PORTFOLIO

#include <entry.hpp>
#include <fstream>
#include <portfolio_entry.hpp>
#include <avl_tree.hpp>
#include <csv_handler.hpp>

#define PORTFOLIO_PERSISTANT_STORAGE "Portfolio.csv"

using namespace std;

namespace autoTrader
{

class Portfolio
{
public:
    Portfolio();
    ~Portfolio();
    PortfolioEntry *getPortfolioEntry(string tickerToFind);
    void writePortfolioEntry(PortfolioEntry *entry) throw();

private:
    AvlTree<PortfolioEntry> *portfolio;
    ofstream portfolioFile;
    CsvHandler *csvReader;
    SingleLogger *log;
};

}//namespace autoTrader

#endif //PORTFOLIO