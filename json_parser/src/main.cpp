#include "../single_include/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

void preOrderTraverse(const ordered_json &OJSData) {
    if (OJSData.empty()) {
        return;
    }

    for (auto it = OJSData.begin(), end = OJSData.end(); it != end; ++it) {
        if (it.value().is_object()) {
            std::cout << it.key().c_str() << "\n";
            preOrderTraverse(it.value());
        } else {
            std::cout << it.key() << " : " << it.value() << "\n";
        }
    }
}

int main() {
    std::ifstream f("../data/default_tune_param.json");
    ordered_json data = ordered_json::parse(f);
    std::string s = data.dump();

    // for (const auto &d : data) {
    //     std::cout << d << "\n";
    // }

    preOrderTraverse(data);

    return 0;
}