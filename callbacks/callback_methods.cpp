#include <functional>
#include <iostream>
#include <string>
#include <vector>

using CallBackT = std::function<int(int)>;

void processor(const std::string& prefix, const std::vector<int>& vec, CallBackT cb)
{
    std::cout << "Using " << prefix << ": ";
    for (const auto& element : vec)
        std::cout << cb(element) << " ";
    std::cout << "\n";
}

int sum_plain_function(int i) { return i + i; }

class Summor {
public:
    Summor() = default;
    int operator()(int i) { return i + i; }
};

class Sum {
public:
    Sum() = default;

    int sum_class_member(int i) { return i + i; }
};

int main()
{
    std::vector<int> vec{123, 2345, 45, 1, 234, 6};
    std::cout << "Test callbacks! \n";

    Sum sum_object;
    auto method = std::bind(&Sum::sum_class_member, &sum_object, std::placeholders::_1);
    processor("Plain function pointer", vec, &sum_plain_function);
    processor("Pure lambda", vec, [](int i) { return i + i; });
    processor("Functor method", vec, Summor());
    processor("Bind member function", vec, method);
    processor("Lambda member function", vec, [&sum_object](int element) {
        return sum_object.sum_class_member(element);
    });

    return 0;
}