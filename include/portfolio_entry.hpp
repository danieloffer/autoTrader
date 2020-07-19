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
    /*
    *PortfolioEntry Ctor
    *param vec - a vector of strings representing the Entry
    *param timeStamp - the time the entry was registered
    */
    PortfolioEntry(vector<string> vec, time_t timeStamp = time(NULL));

    /*
    *PortfolioEntry Dtor
    */
    ~PortfolioEntry();

    /*
    *Returns a string representation of a PortfolioEntry
    */
    string toString();

    /*
    *Returns a string representation of a PortfolioEntry csv styled
    */
    string toCsvString();

    /*
    *Returns a PortfolioEntry as a vector of strings
    */
    vector<string> entryToVector();

    /*
    *Getter for the PortfolioEntry's ticker
    */
    string getTicker();
    
    /*
    *Getter for the PortfolioEntry's stockName
    */
    string getStockName();

    /*
    *Getter for the PortfolioEntry's position
    */
    int getPosition();

    /*
    *Getter for the PortfolioEntry's average price
    */
    float getAvgPrice();

    /*
    *Getter for the PortfolioEntry's PnL(%)
    */
    float getPnl();

    /*
    *Getter for the PortfolioEntry's PnL(cash)
    */
    float getCashPnl();

    /*
    *Getter for the PortfolioEntry's current stock price
    */
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