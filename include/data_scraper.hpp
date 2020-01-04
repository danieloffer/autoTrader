/**
 * data_scraper.hpp
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

    DataScraper();
    ~DataScraper();
    string getStockData(string stockName, E_OperationType op);
    string searchTicker(string searchFor);
private:
    string buildUrl(string request);
    string buildRequest(string func, string stockName);
    string getFuncFromOp(E_OperationType op);

    Logger *log;
};

}//namespace autoTrader


#endif //DATA_SCRAPER
