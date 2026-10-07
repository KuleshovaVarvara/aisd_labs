#include <iostream>
#include "TSet.h"

int main() {
    TSet<int> A;
    A.add(1);
    A.add(2);
    A.add(3);

    TSet<int> B;
    B.add(3);
    B.add(4);
    B.add(5);

    TSet<int> C = A - B;

    std::cout << "A size: " << A.size() << std::endl;
    std::cout << "B size: " << B.size() << std::endl;
    std::cout << "C size (A - B): " << C.size() << std::endl;

    std::cout << "C elements: ";
    for (int i = 0; i < C.size(); i++) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}