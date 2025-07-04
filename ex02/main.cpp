#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	if (ac <= 2)
	{
		std::cerr << "Error: Invalid number of arguments" << std::endl;
		return (1);
	}
	try
	{
		PmergeMe sort(av);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}