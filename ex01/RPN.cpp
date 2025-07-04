#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(const std::string &str)
{
	if (str.find_first_not_of("0123456789+-*/ ") != std::string::npos)
		throw(std::invalid_argument("Error: Invalid argument."));
	for (std::string::const_iterator i = str.begin(); i != str.end(); i++)
	{
		if (*i == ' ')
			continue;
		modifStack(*i);
	}
	if (this->s.size() != 1)
		throw(std::invalid_argument("Error: Invalid expression."));
	std::cout << this->s.top() << std::endl;
}

RPN::RPN(const RPN &src)
{
	*this = src;
}

RPN &RPN::operator=(const RPN &src)
{
	if (this != &src)
		this->s = src.s;
	return *this;
}

RPN::~RPN(){}

double RPN::operation(char c, double first, double second)
{
	switch (c)
	{
	case '+':
		return second + first;
	case '-':
		return second - first;
	case '*':
		return second * first;
	case '/':
		if (first == 0)
			throw(std::invalid_argument("Error: Division by zero."));
		return second / first;
	default:
		throw(std::invalid_argument("Error: Invalid operator."));
	}
}

void RPN::modifStack(char c)
{
	std::string ope = "+-*/";
	if (ope.find(c) != std::string::npos)
	{
		if (this->s.size() < 2)
			throw(std::invalid_argument("Error: Invalid operation."));
		double first = this->s.top();
		this->s.pop();
		double second = this->s.top();
		this->s.pop();
		this->s.push(operation(c, first, second));
	}
	else
		this->s.push(c - '0');
}