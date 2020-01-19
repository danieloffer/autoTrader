autoTrader: src/* include/* qa/unit_tests/*
	g++ -g -Wall --pedantic -std=c++11 src/data_scraper.cpp src/logger.cpp src/single_logger.cpp src/avl_tree.cpp qa/unit_tests/unit_test_avl_tree.cpp -I include/ -o $@ -lcurl

