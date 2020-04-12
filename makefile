autoTrader: src/* include/* qa/unit_tests/*
	g++ -g -Wall --pedantic -std=c++11 src/server.cpp src/server_operations.cpp src/control_server.cpp src/portfolio.cpp src/portfolio_entry.cpp src/trade_entry.cpp src/csv_handler.cpp src/data_scraper.cpp src/logger.cpp src/single_logger.cpp src/avl_tree.cpp qa/unit_tests/unit_test_control_server.cpp -I include/ -o $@ -lcurl
controlClient: src/* include/* qa/unit_tests/*
	g++ -g -Wall --pedantic -std=c++11 src/control_client.cpp -I include/ -o $@


