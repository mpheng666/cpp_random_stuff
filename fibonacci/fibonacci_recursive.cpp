#include <iostream>

int fib(const int i)
{
    if(i==0) return 0;
    if(i==1) return 1;
    return fib(i-1) + fib(i-2);
}

int main()
{
    std::cout << "Fib: " << fib(45) << std::endl;
}