/**
 * data_scraper.hpp
 **/

#ifndef DATA_SCRAPER
#define DATA_SCRAPER

#include <string>

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
        SEARCH,
    };

    void getStockData(string stockName, E_OperationType op);
private:
    string buildCommand(string stockName, string hostName, string request);
    string buildRequest(string func, string stockName);
    string getFuncFromOp(E_OperationType op);
};

}//namespace autoTrader


#endif //DATA_SCRAPER
