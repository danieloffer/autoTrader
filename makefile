autoTrader: src/* include/*
	g++ -g -Wall --pedantic -ansi src/data_scraper.cpp src/logger.cpp qa/unit_tests/unit_test_data_scraper.cpp -I include/ -o $@ -lcurl

