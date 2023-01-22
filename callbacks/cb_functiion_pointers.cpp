#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

struct Context {
    Context(int value)
        : value(value)
    {
    }
    int value{0};
    int count{0};
};

using Callback = int (*)(Context&, int, int);

void processor(const std::vector<int>& vec, Callback cb, Context ctx)
{
    int result = 0;
    for (const auto& element : vec) {
        result += cb(ctx, element, static_cast<int>(vec.size()));
    }
    std::cout << "Result: " << result << "\n";
}

int main()
{
    std::vector<int> data{1, 2, 2, 3, 4, 34, 342, 67, 2, 34, 5, 45, 54, 8};
    auto lambda = [](Context& ctx, int value, int count) {
        if (++ctx.count >= count) {
            std::cout << "100 \n";
        }
        else {
            std::cout << static_cast<int>(ctx.count * 100.0 / count) << "\r"
                      << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        return ctx.value + value;
    };

    processor(data, lambda, Context{2});
    return 0;
}