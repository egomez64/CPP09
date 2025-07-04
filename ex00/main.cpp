#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: too many or too few arguments." << std::endl;
		return 1;
	}
	Btc wallet;
	if (!wallet.check_format("data.csv"))
		return 1;
	wallet.display(av[1]);
	return 0;
}