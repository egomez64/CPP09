#pragma once

#include <iostream>
#include <stack>
#include <string>

class RPN
{
	private:
		std::stack<double> s;

	public:
		RPN(const std::string &str);
		RPN &operator=(const RPN &src);
		~RPN();

	private:
		RPN();
		RPN(const RPN &src);

	public:
		double operation(char c, double first, double second);
		void modifStack(char c);
};