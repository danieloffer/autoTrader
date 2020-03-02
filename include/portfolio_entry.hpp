/**
 * portfolio_entry.hpp
 * this module's purpose is to represent a single position in a portfolio
 **/

#ifndef PORTFOLIO_ENTRY
#define PORTFOLIO_ENTRY

#include <entry.hpp>

using namespace std;

namespace autoTrader
{

class PortfolioEntry : public Entry
{
public:
    PortfolioEntry(vector<string> vec, time_t timeStamp = time(NULL));
    ~PortfolioEntry();
    string toString();
    vector<string> entryToVector();
    string getTicker();
    string getStockName();
    int getPosition();
    float getAvgPrice();
    float getPnl();
    float getCashPnl();
    float getCurrentPrice();

private:
    string ticker;
    string stockName;
    int position;
    float avgPrice;
    float pnl;
    float cashPnl;
    float currentPrice;
    // vector<TradeEntry> tradeEntry; //should have Cctor for avlTree?
};

}//namespace autoTrader

#endif //PORTFOLIO_ENTRY