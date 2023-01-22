#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <vector>
#include <memory>

class Context {
public:
    Context(int mul)
        : multiplier_(mul)
    {
    }
    ~Context() { std::cout << "Context cleanly destroyed\n"; }

    int multiplier_{0};
    int count_{0};
};

using Callback = std::function<int(int, int)>;

int processor(const std::vector<int>& vec, Callback cb)
{
    int result = 0;
    for (const auto& ele : vec) {
        result += cb(ele, static_cast<int>(vec.size()));
    }
    return result;
}

int main()
{
    using namespace std::literals;
    std::vector<int> data{1, 2, 3, 4, 5};
    std::future<int> expected_result;

    {
        auto ctx = Context(10);
        // auto ctx = std::make_shared<Context>(10);

        auto lambda = [&ctx](int value, int count) {
            if (++ctx.count_ >= count) {
                std::cout << "100%";
            }
            else {
                std::cout << static_cast<int>(ctx.count_ * 100.0 / count) << "\r"
                          << std::flush;
                std::this_thread::sleep_for(1000ms);
            }
            return ctx.multiplier_ * value;
        };
        expected_result =
        std::move(std::async(std::launch::async, &processor, data, std::move(lambda)));
    }

    auto result = expected_result.get();
    std::cout << "Result: " << result << "\n";

    return 0;
}