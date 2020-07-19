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
    /*
    *Portfolio Ctor
    */
    Portfolio();

    /*
    *Portfolio Dtor
    */
    ~Portfolio();

    /*
    *Get an Entry from the Portfolio
    *param tickerToFind - the ticker name of the Entry
    Returns a pointer to a PortfolioEntry on success, NULL pointer otherwise
    */
    PortfolioEntry *getPortfolioEntry(string tickerToFind);


    /*
    *Write a PortfolioEntry to the Portfolio
    *param entry - the Entry to write.
    *Throws an exception on failure
    */
    void writePortfolioEntry(PortfolioEntry *entry) throw();

private:
    AvlTree<PortfolioEntry> *portfolio;
    ofstream portfolioFile;
    CsvHandler *csvReader;
    SingleLogger *log;
};

}//namespace autoTrader

#endif //PORTFOLIO