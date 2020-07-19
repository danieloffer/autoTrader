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
    /*
    *DataManager Dtor. 
    */
    ~DataManager();

    /*
    *Returns a DataManager instance
    */
    DataManager *getInstance();

    /*
    *write an Entry to the appropriate database
    */
    void writeEntry();

    /*
    *Get an Entry from a database
    *Returns a pointer to an Entry if successful, NULL otherwise
    */
    Entry *getEntry();

private:
    /*
    *DataManager Ctor. Private so a user can't make an instance. meant to be a singleton 
    */
    DataManager();

    static DataManager *instance;
    Portfolio *portfolio;
    AvlTree<Entry *> *tradeBook;
    SingleLogger *log;
};

DataManager *instance = NULL;

}//namespace autoTrader


#endif //DATA_MANAGERIO
