/**
 * portfolio.cpp
 **/

#include <exception>
#include <portfolio.hpp>

#define UNUSED(x) (void)(x)

using namespace std;

namespace autoTrader
{

    static int compFunc(PortfolioEntry *a, PortfolioEntry *b, void *param)
    {
        UNUSED(param);

        return a->getTicker().compare(b->getStockName());
    }

    static int writeEntryToCsv(PortfolioEntry *entry, void *param)
    {
        //continue!!
    }

    Portfolio::Portfolio(): 
        portfolio(new AvlTree<PortfolioEntry>(compFunc, NULL)),
        portfolioFile(PORTFOLIO_PERSISTANT_STORAGE),
        csvReader(new CsvHandler(PORTFOLIO_PERSISTANT_STORAGE)),
        log(Logger::getInstance())
    {
        log->LOG("Portfolio Ctor");
    }

    Portfolio::~Portfolio()
    {
        log->LOG("Portfolio Dtor");

        if (portfolio->forEach(writeEntryToCsv, NULL))
        {
            log->LOG("Failed to write portfolio to file"); 
            throw 1;   
        }

        log->LOG("Successfully wrote portfolio to file");
        delete portfolio;
        portfolioFile.close();
        delete csvReader;
    }

    PortfolioEntry *Portfolio::getPortfolioEntry(string tickerToFind)
    {
        vector<string> tempEntry = {tickerToFind};
        return portfolio->find(&PortfolioEntry(tempEntry));
    }

    void Portfolio::writePortfolioEntry(PortfolioEntry *entry) throw()
    {
        log->LOG("writePortfolioEntry");

        if (portfolio->insert(entry))
        {
            log->LOG("Failed to add entry to portfolio");
            throw 1;
        }

        log->LOG("Successfully added entry to portfolio");
    }
}//namespace autoTrader