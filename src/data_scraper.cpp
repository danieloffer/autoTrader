/*
* data_scraper.cpp
*/

#include <data_scraper.hpp>
#include <string.h>
#include <iostream>

using namespace std;

namespace autoTrader
{

#define DATA_SOURCE "https://www.alphavantage.co/"
#define API_KEY "5BCBTE0J2VNKLJ6N"

void DataScraper::getStockData(string stockName, E_OperationType op)
{
    string cmd = buildCommand(stockName, DATA_SOURCE, buildRequest(getFuncFromOp(op), stockName));
    if (system(cmd.data()) == -1)
    {
        cout << "command failed" << endl;
        return;
    }
}

string DataScraper::buildCommand(string stockName, string hostName, string request)
{
    string cmdBase("curl -i -o ");
    return cmdBase + stockName + ".json" + " \"" + hostName + request + "\"";

}

string DataScraper::buildRequest(string func, string stockName)
{
    string cmdBase("query?function=");
    return cmdBase + func + "&symbol=" + stockName + "&apikey=" + API_KEY;

}

string DataScraper::getFuncFromOp(E_OperationType op)
{
    string res;
    switch(op)
    {
        case INTRA_DAY:
            res = "TIME_SERIES_INTRADAY";
            break;
        case DAILY:
            res = "TIME_SERIES_DAILY";
            break;
        case DAILY_ADJ:
            res = "TIME_SERIES_DAILY_ADJUSTED";
            break;
        case WEEKLY:
            res = "TIME_SERIES_WEEKLY";
            break;
        case WEEKLY_ADJ:
            res = "TIME_SERIES_WEEKLY_ADJUSTED";
            break;
        case MONTHLY:
            res = "TIME_SERIES_MONTHLY";
            break;
        case MONTHLY_ADJ:
            res = "TIME_SERIES_MONTHLY_ADJUSTED";
            break;
        case CURRENT_PRC:
            res = "GLOBAL_QUOTE";
            break;
        case SEARCH:
            res = "SYMBOL_SEARCH";
            break;
        default:
            res = "TIME_SERIES_DAILY";
    }

    return res;
}

}//namespace autoTrader


