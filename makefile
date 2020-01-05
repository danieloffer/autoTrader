autoTrader: src/* include/*
	g++ -g -Wall --pedantic -std=c++11 src/data_scraper.cpp src/logger.cpp qa/unit_tests/unit_test_data_scraper.cpp -I include/ -o $@ -lcurl

