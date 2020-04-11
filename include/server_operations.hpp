/**
 * server_operations.hpp
 * this module's purpose is to supply the server's action functions
 **/

#ifndef SERVER_OPERATIONS
#define SERVER_OPERATIONS

#include <client_server_types.hpp>

#define DEFAULT_MENU_OPTIONS_NUM 5
#define NUM_OF_SCREENS 5

typedef int (actionFunc)(void *param);


using namespace std;

namespace autoTrader
{
    struct UiNode {
        ClientServerUi uiScreen;
        actionFunc *actions[DEFAULT_MENU_OPTIONS_NUM];
    };

    int actionBuy(void *param);
	int actionSell(void *param);
	int actionSettings(void *param);
    int actiongetData(void *param);
	int actionVoid(void *param);
	int buyStock(void *param);
	int sellStock(void *param);
	int getLogs(void *param);
	int setInterval(void *param);
    int serverGetData(void *param);

    ClientServerUi mainUi = {"Please enter your selection:\n1:Buy\n2:Sell\n3:Settings\n4:get stock data\0", INT};
	UiNode main = {mainUi, {actionVoid, actionBuy, actionSell, actionSettings, actiongetData}};

	ClientServerUi buyUi = {"Enter stock symbol to buy:\n\0", STR};
	UiNode buy = {buyUi, {buyStock, actionVoid, actionVoid, actionVoid, actionVoid}};

	ClientServerUi sellUi = {"Enter stock symbol to sell:\n\0", STR};
	UiNode sell = {sellUi, {sellStock, actionVoid, actionVoid, actionVoid, actionVoid}};

	ClientServerUi settingsUi = {"Enter selection:\n1:get logs\n2:set check interval\0", INT};
	UiNode settings = {settingsUi, {actionVoid, getLogs, setInterval, actionVoid, actionVoid}};

    ClientServerUi getDataUi = {"Enter stock symbol you wish to get data for\0", STR};
	UiNode getData = {getDataUi, {serverGetData, actionVoid, actionVoid, actionVoid, actionVoid}};

    UiNode screens[NUM_OF_SCREENS] = {
					main, 
					buy,
					sell,
					settings,
                    getData
	};
}//namespace autoTrader

#endif //SERVER_OPERATIONS