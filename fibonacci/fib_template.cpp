#include <iostream>
#include <array>
#include <utility>

template <int T>
struct Fib
{
    static const int val = Fib<T-1>::val + Fib<T-2>::val;
};

template<>
struct Fib<0>
{
    static const int val = 0;
};

template<>
struct Fib<1>
{
    static const int val = 1;

};

template<size_t ... I>
int fib_impl(std::index_sequence<I...>, const int i)
{
    constexpr std::array<int, sizeof...(I)>  a
    = {Fib<I>::val...};

    return a[i];
}

const int fib(const int i)
{
    return fib_impl(std::make_index_sequence<47>(), i);
}

int main(int argc, const char *[])
{
    std::cout << "Fib template: " << Fib<45>::val << "\n";
    return 0;
}