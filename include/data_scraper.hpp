/**
 * data_scraper.hpp
 * This module's purpose is to get stock data
 **/

#ifndef DATA_SCRAPER
#define DATA_SCRAPER

#include <string>
#include <logger.hpp>

using namespace std;

namespace autoTrader
{
    
class DataScraper
{
public:
    enum E_OperationType
    {
        INTRA_DAY,
        DAILY,
        DAILY_ADJ,
        WEEKLY,
        WEEKLY_ADJ,
        MONTHLY,
        MONTHLY_ADJ,
        CURRENT_PRC,
        SEARCH
    };

    /*
    *DataScraper Ctor
    */
    DataScraper();

    /*
    *DataScraper Dtor
    */
    ~DataScraper();

    /*
    *Returns the data for a single stock according to the operation type
    *param stockName - the stock to get data for
    *param op - the type of data to get (E_OperationType)
    */
    string getStockData(string stockName, E_OperationType op);

    /*
    *Search for a stock ticker
    *param searchFor - the ticker to search for
    */
    string searchTicker(string searchFor);
private:
    string buildUrl(string request);
    string buildRequest(string func, string stockName);
    string getFuncFromOp(E_OperationType op);

    SingleLogger *log;
};

}//namespace autoTrader


#endif //DATA_SCRAPER
