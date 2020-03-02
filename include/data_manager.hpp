/**
 * data_manager.hpp
 * This module's purpose is to manage the portfolio and tradebook
 **/
#ifndef DATA_MANAGER
#define DATA_MANAGER

#include <string>
#include <logger.hpp>
#include <entry.hpp>
#include <avl_tree.hpp>
#include <portfolio.hpp>

#define TRADEBOOK_PERSISTANT_STORAGE "./TradeBook.csv"

using namespace std;

namespace autoTrader
{
    
class DataManager
{
public:
    ~DataManager();
    DataManager *getInstance();
    void writeEntry();
    Entry *getEntry();

private:
    DataManager();

    static DataManager *instance;
    Portfolio *portfolio;
    AvlTree<Entry *> *tradeBook;
    SingleLogger *log;
};

DataManager *instance = NULL;

}//namespace autoTrader


#endif //DATA_MANAGERIO
