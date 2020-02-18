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
    virtual ~Entry(){}
    virtual string toString()=0;
    virtual vector<string> entryToVector()=0;

protected:
    time_t timeStamp;
};

}//namespace autoTrader

#endif //ENTRY