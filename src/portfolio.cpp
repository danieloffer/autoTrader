/**
 * portfolio.cpp
 **/

#include <iostream>
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
        UNUSED(param);

        int res = 0;
        string entryAsString = entry->toCsvString();
        CsvHandler writer(PORTFOLIO_PERSISTANT_STORAGE);

        if (entryAsString.empty())
        {
            res = 1;
        }

        writer.write(writer.parseCsvString(entryAsString));

        return res;
    }

    Portfolio::Portfolio(): 
        portfolio(new AvlTree<PortfolioEntry>(compFunc, NULL)),
        csvReader(new CsvHandler(PORTFOLIO_PERSISTANT_STORAGE)),
        log(Logger::getInstance())
    {
        vector<vector<string> > portfolioVec = {};
        portfolioFile.open(PORTFOLIO_PERSISTANT_STORAGE, ios::in);

        log->LOG("Portfolio Ctor");
        
        portfolioVec = csvReader->read();

        for (int i = 1; i < (int)portfolioVec.size(); ++i)
        {
            time_t doneAt = stoul(portfolioVec[i][7]);
            PortfolioEntry *entry = new PortfolioEntry(portfolioVec[i], doneAt);

            log->LOG("calling writePortfolioEntry with " + entry->getTicker()); 
            
            writePortfolioEntry(entry);

            delete entry;
        }

        portfolioFile.close();
    }

    Portfolio::~Portfolio()
    {
        string csvHeader;
        ifstream inputStream(PORTFOLIO_PERSISTANT_STORAGE);
        
        log->LOG("Portfolio Dtor");

        getline(inputStream, csvHeader);
        inputStream.close();

        portfolioFile.open(PORTFOLIO_PERSISTANT_STORAGE, ios::trunc | ios::out);
        portfolioFile << csvHeader << '\n';
        portfolioFile.close();

        if (portfolio->forEach(writeEntryToCsv, NULL))
        {
            log->LOG("Failed to write portfolio to file");    
        }
        else
        {
            log->LOG("Successfully wrote portfolio to file");
        }

        delete portfolio;
        delete csvReader;
    }

    PortfolioEntry *Portfolio::getPortfolioEntry(string tickerToFind)
    {
        vector<string> tempEntry = {tickerToFind};
        PortfolioEntry entry(tempEntry);

        log->LOG("Portfolio::getPortfolioEntry - " + tickerToFind);

        return portfolio->find(&entry);
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