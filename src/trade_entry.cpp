/**
 * trade_entry.cpp
 **/

#include <trade_entry.hpp>

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
    size_t id;
    string ticker;
    string stockName;
    int position;
    unsigned float price;
    time_t doneAt; 
};

}//namespace autoTrader

#endif //TRADE_ENTRY