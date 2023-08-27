#include "RPN.h"

int main()
{
    std::stack<int> rpnStack;
    rpnStack.push(10);
    rpnStack.push(20);
    rpnStack.push(30);
    std::cout << "Size: " << rpnStack.size() << std::endl;
    int val1 = rpnStack.top();
    rpnStack.pop();
    int val2 = rpnStack.top();
    rpnStack.pop();
    std::cout << "val1: " << val1 << " val2: " << val2 << std::endl;
    std::cout << "top: " << rpnStack.top() << std::endl;
    return (0);
}