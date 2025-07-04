#ifndef	PMERGEME_HPP
#define	PMERGEME_HPP

#include	<iostream>
#include	<algorithm>
#include	<utility>
#include	<deque>
#include	<vector>
#include	<ctime>
#include    <cmath>
#include 	<iomanip>
#include 	<cstdlib>
#include	<stdexcept>

class PmergeMe
{
	private:
		std::deque<std::deque<int> > _numbersDeque;
		std::vector<std::vector<int> > _numbersVector;
		PmergeMe();
	public:
		PmergeMe(char **av);
		~PmergeMe();

		void 	fillDeque(char **av);
		void 	fillVector(char **av);
		std::deque<std::deque<int> >	sortDeque(std::deque<std::deque<int> > &deq);
		std::vector<std::vector<int> > sortVector(std::vector<std::vector<int> > &vec);
};


bool isPositiv(char *str);

bool allIntegerPositiv(char **av);

double getTimeMs();

#endif