#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <algorithm>

enum
{
	BAD_DATE,
	BAD_VALUE,
	NEGATIVE,
	TOO_LONG,
	FORMAT,
	GOOD
};

class Btc
{
	public:
		std::map<std::string, double> db;

	public:
		int check_format(const std::string &_base);
		int check_line_db(const std::string &line);
		int check_line_in(const std::string &line);
		bool check_date(const std::string &line);
		int check_value(const std::string &line);
		void display(const std::string &file);
		void convert(const std::string &line);

	public:
		Btc();
		Btc(const Btc &src);
		Btc &operator=(const Btc &src);
		~Btc();
};