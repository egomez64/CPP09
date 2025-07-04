#include "BitcoinExchange.hpp"

int Btc::check_format(const std::string &_base)
{
	std::ifstream base(_base.c_str());
	std::string line;
	bool first_line = true;

	if (!base.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 0;
	}
	while (std::getline(base, line))
	{
		if (first_line)
		{
			if (line != "date,exchange_rate")
			{
				std::cout << "Error: first line of database should be: date,exchange_rate ." << std::endl;
				return 0;
			}
			first_line = false;
			continue;
		}
		if (!check_line_db(line))
		{
			std::cout << "Error: invalid database." << std::endl;
			return 0;
		}
		this->db.insert(std::make_pair(line.substr(0, line.find(',')), std::atof(line.substr(line.find(',') + 1).c_str())));
	}
	return 1;
}

int Btc::check_line_db(const std::string &line)
{
	int i = 0;

	if (line.find(',') && (line.find_first_of(',') != line.find_last_of(',')))
		return 0;
	if (line.find('.') && line.find_first_of('.') != line.find_last_of('.'))
		return 0;

	while (line[i] != 0)
	{
		if (i < 4 || (i >= 5 && i < 7) || (i >= 8 && i < 10))
		{
			if (line[i] < '0' || line[i] > '9')
				return 0;
		}
		if ((i == 4 || i == 7) && line[i] != '-')
			return 0;
		if (i == 10 && line[i] != ',')
			return 0;
		if (i > 10 && ((line[i] < '0' || line[i] > '9') && line[i] != '.'))
			return 0;
		i++;
	}
	if (!check_date(line))
		return 0;
	double val = std::atof(line.substr(11, 11 - i).c_str());
	if (val < 0)
		return 0;
	return 1;
}

int Btc::check_line_in(const std::string &line)
{
	int i = 0;

	if (line.find_first_of('|') != line.find_last_of('|'))
		return FORMAT;
	if (line.find_first_of('.') != line.find_last_of('.'))
		return FORMAT;
	while (line[i] != 0)
	{
		if (i < 4 || (i >= 5 && i < 7) || (i >= 8 && i < 10))
		{
			if (line[i] < '0' || line[i] > '9')
				return BAD_DATE;
		}
		if ((i == 4 || i == 7) && line[i] != '-')
			return BAD_DATE;
		if ((i == 10 || i == 12) && line[i] != ' ')
			return FORMAT;
		if (i == 11 && line[i] != '|')
			return FORMAT;
		if (i > 12 && ((line[i] < '0' || line[i] > '9') && (line[i] != '.' && line[i] != '-')))
			return BAD_VALUE;
		i++;
	}
	if (!check_date(line))
		return BAD_DATE;
	if (line.find_first_of('|') == std::string::npos)
		return FORMAT;
	if (line.substr(13, 13 - line.size()).compare("2147483648") == 0)
		return TOO_LONG;
	double val = std::atof(line.substr(13, 13 - line.size()).c_str());
	if (val < 0)
		return NEGATIVE;
	if (val > 1000)
		return TOO_LONG;
	return GOOD;
}

void Btc::display(const std::string &file)
{
	std::string line;
	bool first_line = true;
	std::ifstream input(file.c_str());
	if (!input.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}

	while (std::getline(input, line))
	{
		if (first_line)
		{
			if (line != "date | value")
			{
				std::cout << "Error: first line of input file should be: date | value ." << std::endl;
				return ;
			}
			first_line = false;
			continue;
		}
		switch (check_line_in(line))
		{
		case BAD_DATE:
			std::cout << "Error: bad input => " << std::atoi(line.substr(0, 4).c_str()) << "-" << std::atoi(line.substr(5, 7).c_str()) << '-' << std::atoi(line.substr(8, 10).c_str()) << std::endl;
			break;
		case BAD_VALUE:
			std::cout << "Error: bad input => " << line.substr(12, 12 - line.size()) << std::endl;
			break;
		case NEGATIVE:
			std::cout << "Error: not a positive number." << std::endl;
			break;
		case TOO_LONG:
			std::cout << "Error: too large a number." << std::endl;
			break;
		case FORMAT:
			std::cout << "Error: bad format." << std::endl;
			break;
		
		default:
			convert(line);
			break;
		}
	}
}

bool Btc::check_date(const std::string &line)
{
	tm time;
	tm copy;

	std::memset(&time, 0, sizeof(time));
	time.tm_year = std::atoi(line.substr(0, 4).c_str()) - 1900;
	time.tm_mon = std::atoi(line.substr(5, 7).c_str()) - 1;
	time.tm_mday = std::atoi(line.substr(8, 10).c_str());
	time.tm_hour = 1;
	time.tm_min = 0;
	time.tm_sec = 0;
	copy = time;
	mktime(&time);
	if (copy.tm_year != time.tm_year || copy.tm_mon != time.tm_mon || copy.tm_mday != time.tm_mday)
		return 0;
	return 1;
}

void Btc::convert(const std::string &line)
{
	double val = std::atof(line.substr(13, 13 - line.size()).c_str());
	std::string date = line.substr(0, 10);
	std::map<std::string, double>::iterator it = this->db.lower_bound(date);
	if (date != it->first)
	{
		if (it != this->db.begin())
			--it;
	}
	std::cout << std::atoi(line.substr(0, 4).c_str()) << "-" << "0" << std::atoi(line.substr(5, 7).c_str()) << '-' << "0" << std::atoi(line.substr(8, 10).c_str()) << " => ";
	std::cout << val << " = ";
	val *= it->second;
	std::cout << val << std::endl;
}

Btc::Btc(){}

Btc::Btc(const Btc &src){*this = src;}

Btc &Btc::operator=(const Btc &src)
{
	if (this != &src)
		*this = src;
	return *this;
}

Btc::~Btc(){}