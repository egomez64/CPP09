#include "PmergeMe.hpp"

void fordjv(std::vector<int> &tab)
{
	for (size_t i = 0; i < tab.size() - 1; i+=2)
	{
		if (tab[i] > tab[i+1])
			std::swap(tab[i], tab[i+1]);
	}

	std::vector<std::vector<int> > min;
	for (size_t i = 0; i < tab.size() - 1; i+=2)
	{
		std::vector<int> pair;
		pair.push_back(tab[i]);
		pair.push_back(tab[i+1]);
		min.push_back(pair);
	}
	if (tab.size() % 2 == 1)
	{
        std::vector<int> last_elem;
        last_elem.push_back(tab[tab.size() - 1]);
        min.push_back(last_elem);
    }

	while(min.size() > 1)
	{
		std::vector<std::vector<int> > new_min;
		for (size_t i = 0; i < min.size() - 1; i+=2)
		{
			std::vector<int> merge;
			mergev(min[i], min[i+1], merge);
			new_min.push_back(merge);
		}
		if (min.size() % 2 == 1)
			new_min.push_back(min[min.size() - 1]);
		min = new_min;
	}

	tab = min[0];
}

void mergev(std::vector<int> &sub1, std::vector<int> &sub2, std::vector<int> &result)
{
	size_t i = 0, j = 0;

	while (i < sub1.size() && j < sub2.size())
	{
		if (sub1[i] <= sub2[j])
		{
			result.push_back(sub1[i]);
			++i;
		}
		else
		{
			result.push_back(sub2[j]);
			++j;
		}
	}
	while (i < sub1.size())
	{
		result.push_back(sub1[i]);
		++i;
	}
	while (j < sub2.size())
	{
		result.push_back(sub2[j]);
		++j;
	}
}

void fordjd(std::deque<int> &tab)
{
	for (size_t i = 0; i < tab.size() - 1; i+=2)
	{
		if (tab[i + 1] && tab[i] > tab[i+1])
			std::swap(tab[i], tab[i+1]);
	}

	std::deque<std::deque<int> > min;
	for (size_t i = 0; i < tab.size() - 1; i+=2)
	{
		std::deque<int> pair;
		pair.push_back(tab[i]);
		pair.push_back(tab[i+1]);
		min.push_back(pair);
	}
	if (tab.size() % 2 == 1)
	{
        std::deque<int> last_elem;
        last_elem.push_back(tab[tab.size() - 1]);
        min.push_back(last_elem);
    }

	while(min.size() > 1)
	{
		std::deque<std::deque<int> > new_min;
		for (size_t i = 0; i < min.size() - 1; i+=2)
		{
			std::deque<int> merge;
			merged(min[i], min[i+1], merge);
			new_min.push_back(merge);
		}
		if (min.size() % 2 == 1)
			new_min.push_back(min[min.size() - 1]);
		min = new_min;
	}

	tab = min[0];
}

void merged(std::deque<int> &sub1, std::deque<int> &sub2, std::deque<int> &result)
{
	size_t i = 0, j = 0;

	while (i < sub1.size() && j < sub2.size())
	{
		if (sub1[i] <= sub2[j])
		{
			result.push_back(sub1[i]);
			++i;
		}
		else
		{
			result.push_back(sub2[j]);
			++j;
		}
	}
	while (i < sub1.size())
	{
		result.push_back(sub1[i]);
		++i;
	}
	while (j < sub2.size())
	{
		result.push_back(sub2[j]);
		++j;
	}
}

void displayv(std::vector<int> &tab)
{
	for (size_t i = 0; i < tab.size(); i++)
        std::cout << tab[i] << " ";
    std::cout << std::endl;
}

void displayd(std::deque<int> &tab)
{
	for (size_t i = 0; i < tab.size(); i++)
        std::cout << tab[i] << " ";
    std::cout << std::endl;
}

bool parsing(char **lst, int ac)
{
	int i = 1;
	while (i < ac)
	{
		std::string line = lst[i];
		if (line.find_first_not_of("0123456789 ") != std::string::npos)
			return 0;
		i++;
	}
	return 1;
}

std::vector<int> initv(char **lst, int ac)
{
	std::vector<int> res;
	std::string num;
	int y = 1;

	while (y < ac)
	{
		std::string line = lst[y];
		for (size_t i = 0; i < line.size(); i++)
		{
			if (line.size() == 1)
			{
				res.push_back(std::atoi(line.c_str()));
				num.clear();
			}
			else if (line[i] == ' ')
			{
				if (num.size() > 0)
				{
					res.push_back(std::atoi(num.c_str()));
					num.clear();
				}
			}
			else
				num.push_back(line[i]);
		}
		if (num.size() > 0)
		{
			res.push_back(std::atoi(num.c_str()));
			num.clear();
		}
		y++;
	}
	return res;
}

std::deque<int> initd(char **lst, int ac)
{
	std::deque<int> res;
	std::string num;
	int y = 1;

	while (y < ac)
	{
		std::string line = lst[y];
		for (size_t i = 0; i < line.size(); i++)
		{
			if (line.size() == 1)
			{
				res.push_back(std::atoi(line.c_str()));
				num.clear();
			}
			else if (line[i] == ' ')
			{
				if (num.size() > 0)
				{
					res.push_back(std::atoi(num.c_str()));
					num.clear();
				}
			}
			else
				num.push_back(line[i]);
		}
		if (num.size() > 0)
		{
			res.push_back(std::atoi(num.c_str()));
			num.clear();
		}
		y++;
	}
	return res;
}