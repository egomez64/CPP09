#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av) {
	if (!allIntegerPositiv(av))
		throw std::runtime_error("Error: At least one number is too big or negative");

	double startDeque = getTimeMs();
	fillDeque(av);
	if (this->_numbersDeque.size() < 2)
		throw std::runtime_error("Error: Too few numbers");	
	_numbersDeque = sortDeque(_numbersDeque);
	double endDeque = getTimeMs();

	double start = getTimeMs();
	fillVector(av);
	_numbersVector = sortVector(_numbersVector);
	double end = getTimeMs();
	
	std::cout << std::endl << "Deque after :   ";
	int i = 0;
	for (std::deque<std::deque<int> >::const_iterator it = _numbersDeque.begin(); it != _numbersDeque.end(); ++it , i++) {
		for (std::deque<int>::const_iterator itDeque = it->begin(); itDeque != it->end(); ++itDeque) {
			std::cout << *itDeque << " ";
		}
		if (i == 50){
			std::cout << "[...]";
			break;
		}
	}
	std::cout << std::endl << "Vector after :   ";
	i = 0;
	for (std::vector<std::vector<int> >::const_iterator it = _numbersVector.begin(); it != _numbersVector.end(); ++it , i++) {
		for (std::vector<int>::const_iterator itVector = it->begin(); itVector != it->end(); ++itVector) {
			std::cout << *itVector << " ";
		}
		if (i == 50){
			std::cout << "[...]";
			break;
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << std::fixed << std::setprecision(5) <<  "Time to process a range of " << _numbersDeque.size() << " elements with std::deque: " << (endDeque - startDeque) << " us" << std::endl;
	std::cout << std::fixed << std::setprecision(5) <<  "Time to process a range of " << _numbersVector.size() << " elements with std::vector: " << (end - start) << " us" << std::endl;
}

void PmergeMe::fillDeque(char **av) {
	std::cout << "Deque before :   ";
	for (size_t i = 1; av[i]; i++) {
		std::deque<int> tmp;
		char *endptr;
		tmp.push_back((int)std::strtoll(av[i], &endptr, 10));
		std::cout << av[i] << " ";
		this->_numbersDeque.push_back(tmp);
	}
	std::cout << std::endl;
}

void PmergeMe::fillVector(char **av) {
	std::cout << "Vector before :   ";
	for (size_t i = 1; av[i]; i++) {
		std::vector<int> tmp;
		char *endptr;
		tmp.push_back((int)std::strtoll(av[i], &endptr, 10));
		std::cout <<  av[i] << " ";
		this->_numbersVector.push_back(tmp);
	}
	std::cout << std::endl;
}

static void JacobSthalDeq(std::deque<std::deque<int> > &pend, std::deque<std::deque<int> > &main) {
 	static const size_t jacobsthal[] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531};

    std::vector<bool> used(pend.size(), false);

    for (size_t i = 1; jacobsthal[i] < pend.size(); ++i) {
        size_t index = jacobsthal[i];
        if (index >= pend.size())
            break;
        if (used[index])
            continue;
        used[index] = true;

        std::deque<int> element = pend[index];
        std::deque<std::deque<int> >::iterator pos = main.begin();
        while (pos != main.end() && pos->back() < element.back())
            ++pos;
        main.insert(pos, element);
    }
    for (size_t i = 0; i < pend.size(); ++i) {
        if (used[i])
            continue;
        std::deque<int> element = pend[i];
        std::deque<std::deque<int> >::iterator pos = main.begin();
        while (pos != main.end() && pos->back() < element.back())
            ++pos;
        main.insert(pos, element);
    }
}

static void JacobSthalVec(std::vector<std::vector<int> > &pend, std::vector<std::vector<int> > &main) {
	static const size_t jacobsthal[] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531};

    std::vector<bool> used(pend.size(), false);

    for (size_t i = 1; jacobsthal[i] < pend.size(); ++i) {
        size_t index = jacobsthal[i];
        if (index >= pend.size())
            break;
        if (used[index])
            continue;
        used[index] = true;

        std::vector<int> element = pend[index];
        std::vector<std::vector<int> >::iterator pos = main.begin();
        while (pos != main.end() && pos->back() < element.back())
            ++pos;
        main.insert(pos, element);
    }

    for (size_t i = 0; i < pend.size(); ++i) {
        if (used[i])
            continue;
        std::vector<int> element = pend[i];
        std::vector<std::vector<int> >::iterator pos = main.begin();
        while (pos != main.end() && pos->back() < element.back())
            ++pos;
        main.insert(pos, element);
    }
}

static std::deque<std::deque<int> > unpairDeque(std::deque<std::deque<int> > &original) {
	std::deque<std::deque<int> > result;
	for (std::deque<std::deque<int> >::iterator it = original.begin(); it != original.end(); ++it) {
		std::deque<int> firstHalf, secondHalf;
		size_t mid = it->size() / 2;
		size_t i = 0;
		for (std::deque<int>::iterator jt = it->begin(); jt != it->end(); ++jt, ++i) {
			if (i < mid)
				firstHalf.push_back(*jt);
			else
				secondHalf.push_back(*jt);
		}
		if (!firstHalf.empty())
			result.push_back(firstHalf);
		if (!secondHalf.empty())
			result.push_back(secondHalf);
	}
	return result;
}

static std::vector<std::vector<int> > unpairVector(std::vector<std::vector<int> > &original) {
    std::vector<std::vector<int> > result;

    for (std::vector<std::vector<int> >::iterator it = original.begin(); it != original.end(); ++it) {
        std::vector<int> firstHalf, secondHalf;
        size_t mid = it->size() / 2;

        for (size_t i = 0; i < it->size(); ++i) {
            if (i < mid)
                firstHalf.push_back((*it)[i]);
            else
                secondHalf.push_back((*it)[i]);
        }
        if (!firstHalf.empty())
            result.push_back(firstHalf);
        if (!secondHalf.empty())
            result.push_back(secondHalf);
    }

    return result;
}

std::vector<std::vector<int> > PmergeMe::sortVector(std::vector<std::vector<int> > &vec) {
	if (vec.size() <= 1)
		return vec;

	std::vector<std::vector<int> > main;
	std::vector<std::vector<int> > pend;
	std::vector<std::vector<int> > last;

	size_t i = 0;
	while (i < vec.size()) {
		std::vector<int> first = vec[i++];
		if (i < vec.size()) {
			std::vector<int> second = vec[i++];
			int nb1 = first.back();
			int nb2 = second.back();
			if (nb2 < nb1)
				std::swap(first, second);
			first.insert(first.end(), second.begin(), second.end());
			main.push_back(first);
		} else {
			last.push_back(first);
		}
	}

	if (main.size() > 1)
		main = sortVector(main);
	main = unpairVector(main);

	std::vector<std::vector<int> > filteredMain;
	for (size_t j = 0; j < main.size(); ++j) {
		if (j % 2 == 0 && j >= 2)
			pend.push_back(main[j]);
		else
			filteredMain.push_back(main[j]);
	}
	main = filteredMain;
	
	JacobSthalVec(pend, main);
	JacobSthalVec(last, main);

	return main;
}

std::deque<std::deque<int> > PmergeMe::sortDeque(std::deque<std::deque<int> > &deq) {
	if (deq.size() <= 1)
		return deq;

	std::deque<std::deque<int> > main;
	std::deque<std::deque<int> > pend;
	std::deque<std::deque<int> > last;

	size_t i = 0;
	while (i < deq.size()) {
		std::deque<int> first = deq[i++];
		if (i < deq.size()) {
			std::deque<int> second = deq[i++];
			int nb1 = first.back();
			int nb2 = second.back();
			if (nb2 < nb1)
				std::swap(first, second);
			first.insert(first.end(), second.begin(), second.end());
			main.push_back(first);
		} else {
			last.push_back(first);
		}
	}

	if (main.size() > 1)
		main = sortDeque(main);
	
	main = unpairDeque(main);

	std::deque<std::deque<int> > filteredMain;
	for (size_t j = 0; j < main.size(); ++j) {
		if (j % 2 == 0 && j >= 2)
			pend.push_back(main[j]);
		else
			filteredMain.push_back(main[j]);
	}
	main = filteredMain;
	
	JacobSthalDeq(pend, main);
	JacobSthalDeq(last, main);

	return main;
}

PmergeMe::~PmergeMe() {}

bool isPositiv(char *str) {
	if (!str || str[0] == '\0')
		return false;
	for (size_t i = 0; str[i]; i++) {
		if (!std::isdigit(str[i]))
			return false;
	}
	char *endptr;
	long long integer = std::strtoll(str, &endptr, 10);
	if (integer > 2147483647 || integer < 0 || *endptr != '\0')
		return false;
	return true;
}

bool allIntegerPositiv(char **av) {
	for (size_t i = 1; av[i]; i++) {
		if (!isPositiv(av[i]))
			return false;
	}
	return true;
}

double getTimeMs() {
	return static_cast<double>(std::clock()) * 1e6 / CLOCKS_PER_SEC;
}