/**
 * entry.hpp
 * this module's purpose is to be an abstract class that all other entries will inherit from
 **/

#ifndef ENTRY
#define ENTRY

#include <string>
#include <vector>

using namespace std;

namespace autoTrader
{

class Entry
{
public:

    /*
    *Entry Dtor
    */
    virtual ~Entry(){}

    /*
    *Returns the Entry as a string
    */
    virtual string toString()=0;
    
    /*
    *Returns the Entry as a string csv styled
    */
    virtual string toCsvString()=0;

    /*
    *Returns the Entry vector of strings
    */
    virtual vector<string> entryToVector()=0;

protected:
    time_t timeStamp;
};

}//namespace autoTrader

#endif //ENTRY