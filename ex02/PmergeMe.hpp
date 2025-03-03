#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>

void fordjv(std::vector<int> &tab);
void fordjd(std::deque<int> &tab);
void mergev(std::vector<int> &sub1, std::vector<int> &sub2, std::vector<int> &result);
void merged(std::deque<int> &sub1, std::deque<int> &sub2, std::deque<int> &result);

void displayv(std::vector<int> &tab);
void displayd(std::deque<int> &tab);

bool parsing(char **lst, int ac);

std::vector<int> initv(char **lst, int ac);
std::deque<int> initd(char **lst, int ac);