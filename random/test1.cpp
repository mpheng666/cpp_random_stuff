#include <algorithm>
#include <iostream>
#include <vector>

template <typename V>
int count_something(V &vec, int value) {
    std::for_each(begin(vec), end(vec), [](auto &v) { std::cout << v; });
    std::cout << '\n';

    for (const auto &element : vec) {
        // std::cout << element;
        std::sort(begin(vec), end(vec), [](int a, int b) -> bool {
            std::cout << "a:" << a << '\t';
            std::cout << "b:" << b << '\n';

            return a > b;
        });
    }
    std::cout << '\n';

    const auto x = std::count(begin(vec), end(vec), value);
    return x;
}

int main() {
    // auto x = 5%2;
    // constexpr auto y = 10.0;
    std::vector<int> vec1 = {2, 2, 4, 5, 1, 2, 1, 2, 4, 5, 6, 4};
    std::vector<int> vec2 = {2, 3, 1};
    auto x = count_something(vec2, 2);
    std::cout << "count: " << x << "\n";
    for (const auto &v : vec1) {
        std::cout << v;
    }

    return 0;
}