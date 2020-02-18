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
    TradeEntry(vector<string> vec, time_t timeStamp = time(NULL), size_t entryId = 0);
    ~TradeEntry();
    string toString();
    vector<string> entryToVector();

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