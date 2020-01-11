/*
* data_scraper.cpp
*/

#include <data_scraper.hpp>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <curl/curl.h>

using namespace std;

namespace autoTrader
{

#define DATA_SOURCE "https://www.alphavantage.co/"
#define API_KEY "5BCBTE0J2VNKLJ6N"

/*
* this struct is to pass a buffer and a current position to the write callback
* so that it can handle multiple callbacks
*/
struct memoryStruct
{
    public:
    memoryStruct(char *buff, size_t currPosition): buff(buff), currPosition(currPosition){}
    char *buff;
    size_t currPosition;
};

/* writes the data recieved from the https response to the buffer in the userData*/
static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userData)
{
    SingleLogger *log = Logger::getInstance();
    
    log->LOG("writing " + to_string(nmemb) + " bytes to buffer");
    memoryStruct *mem = (memoryStruct*)userData;
    memcpy(mem->buff + mem->currPosition, ptr, nmemb);
    mem->currPosition += nmemb;
    
    return nmemb;
} 

string DataScraper::getStockData(string stockName, E_OperationType op)
{
    CURL *curl;
    CURLcode res;
    memoryStruct mem(NULL, 0);
    string ret;

    mem.buff = (char*)calloc(100000,1);
    mem.currPosition = 0;
 
    log->LOG("init curl");
    curl = curl_easy_init();
    if (curl) 
    {
        string cmd = buildUrl(buildRequest(getFuncFromOp(op), stockName));
        log->LOG("setting url : " + cmd);
        curl_easy_setopt(curl, CURLOPT_URL, cmd.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &mem); 
    /* Perform the request, res will get the return code */ 
    log->LOG("perform curl call");
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
    {
        log->LOG("curl_easy_perform() failed: " + string(curl_easy_strerror(res)));
    }

    /* always cleanup */ 
    log->LOG("perform curl cleanup");
    curl_easy_cleanup(curl);

    ret = string(mem.buff);
    free(mem.buff);

    return ret;
}

string DataScraper::searchTicker(string searchFor)
{
    return string("T");
}


string DataScraper::buildUrl(string request)
{
    return DATA_SOURCE + request + "\"";
}

string DataScraper::buildRequest(string func, string stockName)
{
    string cmdBase("query?function=");
    return cmdBase + func + "&symbol=" + stockName + "&datatype=csv" + "&apikey=" + API_KEY;

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

DataScraper::DataScraper() : log(Logger::getInstance())
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    log->LOG("DataScraper constructor");
}

DataScraper::~DataScraper()
{
    curl_global_cleanup();
    log->LOG("DataScraper destructor");
}

}//namespace autoTrader


