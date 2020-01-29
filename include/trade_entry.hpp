/**
 * trade_entry.hpp
 * this module's purpose is to represent a single trade
 **/

#ifndef TRADE_ENTRY
#define TRADE_ENTRY

#include <entry.hpp>
#include <vector>
#include <string>

using namespace std;

namespace autoTrader
{

class TradeEntry : public Entry
{
public:
    TradeEntry();
    ~TradeEntry();
    string toString();
    Entry *csvToEntry(vector<vector<string> >entryAsCsv);
    Entry *stringToEntry(string entryAsString);

private:
    size_t entryId;
    string ticker;
    string stockName;
    int position;
    float price;
    time_t doneAt; 
};

}//namespace autoTrader

#endif //TRADE_ENTRY