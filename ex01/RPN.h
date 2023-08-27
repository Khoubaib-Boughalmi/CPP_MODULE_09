#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <stack>
#include <cctype>
#include <cstdlib>

extern std::stack<int> rpnStack;

// 1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 / 
// ((((((((((1 * 2) / 2) + 2) * 5) - 6) * 1) - 3) * 4) * 5) / 8) == 15

#endif