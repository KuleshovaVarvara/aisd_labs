#include <iostream>
#include "TSet.h"

int main() {
    TSet<int> set;

    set.add(5);
    set.add(10);
    set.add(5);  

    std::cout << "Size: " << set.size() << std::endl;

    return 0;
}