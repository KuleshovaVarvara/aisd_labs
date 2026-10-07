#include <iostream>
#include "TSet.h"

int main() {
    TSet<int> set;
    set.add(5);
    set.add(10);
    set.add(15);
    set.add(20);

    std::cout << "Size: " << set.size() << std::endl;

    set.remove(10);
    std::cout << "After remove(10), size: " << set.size() << std::endl;
    std::cout << "set[0] = " << set[0] << std::endl;
    std::cout << "set[1] = " << set[1] << std::endl;
    std::cout << "set[2] = " << set[2] << std::endl;

    set.remove(99);
    std::cout << "After remove(99), size: " << set.size() << std::endl;

    return 0;
}