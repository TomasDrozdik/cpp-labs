#include <iostream>

constexpr int max(int a, int b) 
{ 
    return (a < b) ? a : b;
} 

template<int N>
struct Fib
{
    static constexpr int value = Fib<N-1>::value + Fib<N-2>::value;
};

template<>
struct Fib<1>
{
    static constexpr int value = 1;
};

template<>
struct Fib<0>
{
    static constexpr int value = 0;
};

int main()
{
    auto x = max(10000, 999999);
    std::cout << x << std::endl;

    std::cout << Fib<10>::value << std::endl;

    return 0;
}
