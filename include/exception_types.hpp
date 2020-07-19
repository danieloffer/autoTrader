/**
 * exception_types.hpp
 * this module's purpose is to extend the exception class with custom exceptions
 **/

#ifndef EXCEPTION_TYPES
#define EXCEPTION_TYPES

#include <exception>
#include <error_codes.hpp>

using namespace std;

namespace autoTrader
{
class GeneralException : public exception
{
public:
    GeneralException(E_ErrorCodes inErrCode, int inLineNum, const char *inFuncName, const char *inFileName):errCode(inErrCode),
                                                                    line(inLineNum), funcName(inFuncName), fileName(inFileName){/*empty func body*/};
    virtual ~GeneralException();
    E_ErrorCodes getErrCode() {return errCode;}
    int getLine() {return line;}
    const char *getFuncName() {return funcName;}
    const char *getFileName() {return fileName;}
protected:
    E_ErrorCodes errCode;
    int line;
    const char *funcName;
    const char *fileName;
};

class ServerError : public GeneralException
{
    ServerError(E_ErrorCodes inErrCode, int inLineNum, const char *inFuncName, const char *inFileName): 
                                                GeneralException(inErrCode, inLineNum, inFuncName, inFileName)
    {
        //empty func body    
    }

    const char *what()
    {
        return "Server Error";
    }
};

}//namespace autoTrader

#endif //EXCEPTION_TYPES