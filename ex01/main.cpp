#include "RPN.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 2)
			throw(std::invalid_argument("Error: Too many or too few argument"));
		RPN result(av[1]);
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}