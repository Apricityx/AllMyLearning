#include <string>
#include <iostream>
#include <vector>

int re_call(const int &x) {
    return x;
}

int main() {
    // Vector
    std::vector<std::string> vec;
    vec.emplace_back("123");
    vec.emplace_back("345");
    std::cout << vec.back() << std::endl;
    std::cout << re_call(123123)<<std::endl;
    for (const std::string &word: vec) {
        std::cout << word << std::endl;
    }
    return 0;
}
