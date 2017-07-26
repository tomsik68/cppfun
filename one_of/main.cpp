#include "one_of.hpp"
#include <iostream>

enum class Test {
    A,
    B,
    C
};

int main() {
    int i = 50;

    std::cout << "is 50 one of pre-defined values: " << one_of<decltype(1),1,2,3,4,5,50>()(i) << std::endl;
    
    std::cout << "is C one of pre-defined values:" << one_of<Test, Test::A, Test::C>()(Test::C);
}
