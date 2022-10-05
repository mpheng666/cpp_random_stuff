//  Boost.PFR is a C++14 library for a very basic reflection. It gives you access to structure elements by index and provides other std::tuple like methods for user defined types without macro or boilerplate code:
#include <iostream>
#include <string>

#include "boost/pfr.hpp"

struct some_person {
    std::string name;
    unsigned birth_year;
    // int house;
    // int car;
    // int table;
    // bool happy;
    struct family
    {
        float father{41};
        float mother{4};
        struct house
        {
            int my{1};
            int sg{3};
        };
    };
};

int main() {
    some_person::family test_val;
    some_person val{"Edgar Allan Poe", 1809, test_val};

    // std::cout << boost::pfr::get<0>(val) // No macro!
    //           << " was born in "
    //           << boost::pfr::get<1>(
    //                      val) << "\n"; // Works with any aggregate initializables!

    std::cout << boost::pfr::io(val)
              << "\n"; // Outputs: {"Edgar Allan Poe", 1809}
    std::cout << boost::pfr::io(test_val)
              << "\n"; // Outputs: {"Edgar Allan Poe", 1809}
}

// struct my_type {
//     int a;
//     float b;
//     std::string c;
// };

// VISITABLE_STRUCT(my_type, a, b, c);

// struct debug_printer {
//     template <typename T> void operator()(const char *name, const T &value) {
//         std::cerr << name << ": " << value << std::endl;
//     }
// };

// void debug_print(const my_type &my_struct) {
//     visit_struct::for_each(my_struct, debug_printer{});
// }