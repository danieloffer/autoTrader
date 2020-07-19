/**
 * trade_entry.hpp
 * this module's purpose is to represent a single trade
 **/

#ifndef TRADE_ENTRY
#define TRADE_ENTRY

#include <entry.hpp>

using namespace std;

namespace autoTrader
{

class TradeEntry : public Entry
{
public:
    /*
    *TradeEntry Ctor
    *param vec - a vector representing the TradeEntry
    *param timeStamp - the time of the trade
    *param entryId - a unique id of the trade
    */
    TradeEntry(vector<string> vec, time_t timeStamp = time(NULL), size_t entryId = 0);

    /*
    *TradeEntry Dtor
    */
    ~TradeEntry();

    /*
    *Returns a string representation of a TradeEntry
    */
    string toString();

    /*
    *Returns a string representation of a TradeEntry csv styled
    */
    string toCsvString();

    /*
    *Returns a TradeEntry as a vector of strings
    */
    vector<string> entryToVector();

    /*
    *Getter for the TradeEntry's id
    */
    size_t getEntryId();

    /*
    *Getter for the TradeEntry's ticker
    */
    string getTicker();

    /*
    *Getter for the TradeEntry's stock name
    */
    string getStockName();

    /*
    *Getter for the TradeEntry's position
    */
    int getPosition();

    /*
    *Getter for the TradeEntry's price
    */
    float getPrice();

private:
    size_t entryId;
    string ticker;
    string stockName;
    int position;
    float price;
    // PortfolioEntry portfolioEntry; 
};

}//namespace autoTrader

#endif //TRADE_ENTRY