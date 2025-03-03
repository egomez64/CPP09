#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	std::deque<int> deq;
	std::vector<int> vec;
	clock_t startd, endd, startv, endv;
	double v_time, d_time;

	if (ac <= 1)
	{
		std::cerr << "Error: too few argument." << std::endl;
		return 1;
	}

	if (!parsing(av, ac))
	{
		std::cerr << "Error: invalid arguments." << std::endl;
		return 1;
	}

	vec = initv(av, ac);
	deq = initd(av, ac);

	std::cout << "Vector before: ";
	displayv(vec);
	std::cout << "Deque before: ";
	displayd(deq);

	startd = clock();
	fordjd(deq);
	endd = clock();
	startv = clock();
	fordjv(vec);
	endv = clock();

	std::cout << "Vector after: ";
	displayv(vec);
	std::cout << "Deque after: ";
	displayd(deq);

	v_time = static_cast<double>(endv - startv) / (CLOCKS_PER_SEC / 1000);
	d_time = static_cast<double>(endd - startd) / (CLOCKS_PER_SEC / 1000);
	std::cout << "Time to process a range of " << ac - 1 << " elements with std::vector : " << v_time << "ms" << std::endl;
	std::cout << "Time to process a range of " << ac - 1 << " elements with std::deque : " << d_time << "ms" << std::endl;

    return 0;
}