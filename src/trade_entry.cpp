/**
 * trade_entry.cpp
 **/

#include <trade_entry.hpp>

using namespace std;

namespace autoTrader
{

    size_t getEntryId(string ticker, time_t doneAt) // complete function to produce hash
    {
        return 1;
    }

    TradeEntry::TradeEntry(vector<string> vec, time_t timeStamp, size_t entryId)
    {
        this->timeStamp = timeStamp;
        this->ticker = vec[0];
        this->stockName = vec[1];
        this->position = atoi(vec[2].c_str());
        this->price = atof(vec[3].c_str());
        this->entryId = entryId ? entryId : getEntryId(ticker, timeStamp);
    }

    TradeEntry::~TradeEntry()
    {
        
    }

    string TradeEntry::toString()
    {
        return ("ID: " + to_string(entryId) + 
                "\nticker: " + ticker + 
                "\nstockName: " + stockName + 
                "\nposition: " + to_string(position) + 
                "\nprice: " + to_string(price) + 
                "\ntimeStamp: " + asctime(gmtime(&timeStamp)));
    }

    string TradeEntry::toCsvString()
    {
        return (to_string(entryId) + "," + ticker + "," + stockName + "," 
                + to_string(position) + "," + to_string(price) + "," + to_string(timeStamp));
    }

    vector<string> TradeEntry::entryToVector()
    {
        vector<string> vec(6, "");

        vec[0] = to_string(entryId);
        vec[1] = ticker;
        vec[2] = stockName;
        vec[3] = to_string(position);
        vec[4] = to_string(price);
        vec[5] = to_string(timeStamp);

        return vec; 
    }
}//namespace autoTrader
