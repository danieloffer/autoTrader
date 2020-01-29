/**
 * entry.hpp
 * this module's purpose is to be an abstract class that all other entries will inherit from
 **/

#ifndef ENTRY
#define ENTRY

using namespace std;

namespace autoTrader
{

class Entry
{
public:
    virtual ~Entry();
    virtual string toString()=0;
    virtual Entry *csvToEntry(vector<vector<string> >entryAsCsv)=0;
    virtual Entry *stringToEntry(string entryAsString)=0;
};

}//namespace autoTrader

#endif //ENTRY