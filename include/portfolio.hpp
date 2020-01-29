/**
 * portfolio.hpp
 * This module's purpose is to manage the portfolio
 **/
#ifndef PORTFOLIO
#define PORTFOLIO

#include <string>
#include <time>
#include <logger.hpp>


using namespace std;

namespace autoTrader
{
    
class Portfolio
{
public:
    
private:
    class PortfolioEntry
    {
    public:
        PortfolioEntry(string stockName, string ticker, size_t amount, unsigned float latestPrice, unsigned float boughtPrice,
                        float changeFromPurchase, time_t firstTraded, time_t lastTraded);
    private:
        string stockName;
        string ticker;
        size_t amount;
        unsigned float latestPrice;
        unsigned float boughtPrice;
        float changeFromPurchase;
        time_t firstTraded;
        time_t lastTraded;
    }
    SingleLogger *log;
};

}//namespace autoTrader


#endif //PORTFOLIO
