#include <iostream>
#include "TSet.h"

int main() {
    std::cout << "=== TSet demonstration ===" << std::endl << std::endl;

    // 1. Конструктор по умолчанию
    std::cout << "1. Default constructor:" << std::endl;
    TSet<int> empty;
    std::cout << "empty = " << empty << std::endl;
    std::cout << "size = " << empty.size() << std::endl << std::endl;

    // 2. Конструктор из массива
    std::cout << "2. Constructor from array:" << std::endl;
    int arr1[] = { 1, 2, 3, 3, 2, 1 };
    TSet<int> A(arr1, 6);
    std::cout << "A = " << A << std::endl << std::endl;

    // 3. Конструктор случайных значений
    std::cout << "3. Random constructor:" << std::endl;
    TSet<int> R(5, 1, 10);
    std::cout << "R = " << R << std::endl;
    std::cout << "size = " << R.size() << std::endl << std::endl;

    // 4. Работа с float
    std::cout << "4. Float test:" << std::endl;
    TSet<float> F(4, 1.0f, 5.0f);
    std::cout << "F = " << F << std::endl << std::endl;

    // 5. Метод add
    std::cout << "5. Method add:" << std::endl;
    A.add(5);
    A.add(5);
    std::cout << "A after add(5) twice = " << A << std::endl << std::endl;

    // 6. contains
    std::cout << "6. Method contains:" << std::endl;
    std::cout << "A contains 3? " << (A.contains(3) ? "Yes" : "No") << std::endl;
    std::cout << "A contains 99? " << (A.contains(99) ? "Yes" : "No") << std::endl << std::endl;

    // 7. operator[]
    std::cout << "7. Operator []:" << std::endl;
    std::cout << "A[0] = " << A[0] << std::endl;
    A[0] = 100;
    std::cout << "After A[0] = 100: A = " << A << std::endl << std::endl;

    // 8. remove
    std::cout << "8. Method remove:" << std::endl;
    A.remove(100);
    std::cout << "After remove(100): A = " << A << std::endl << std::endl;

    // 9. Set operations
    std::cout << "9. Set operations:" << std::endl;
    int arr2[] = { 3, 4, 5 };
    TSet<int> B(arr2, 3);
    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "A + B = " << (A + B) << std::endl;
    std::cout << "A * B = " << (A * B) << std::endl;
    std::cout << "A - B = " << (A - B) << std::endl << std::endl;

    // 10. Comparison
    std::cout << "10. Comparison:" << std::endl;
    TSet<int> A_copy = A;
    std::cout << "A == A_copy? " << (A == A_copy ? "Yes" : "No") << std::endl;
    std::cout << "A == B? " << (A == B ? "Yes" : "No") << std::endl;
    std::cout << "A != B? " << (A != B ? "Yes" : "No") << std::endl << std::endl;

    // 11. Task #4: relations between sets
    std::cout << "11. Task #4: relations between sets" << std::endl;
    int arr3[] = { 2, 3 };
    TSet<int> C(arr3, 2);
    std::cout << "C = " << C << std::endl;
    std::cout << "A = " << A << std::endl;
    std::cout << "C.isSubset(A)? " << (C.isSubset(A) ? "Yes" : "No") << std::endl;
    std::cout << "A.isSuperset(C)? " << (A.isSuperset(C) ? "Yes" : "No") << std::endl << std::endl;

    // 12. Exceptions
    std::cout << "12. Exception check:" << std::endl;
    try {
        std::cout << "Trying A[100]..." << std::endl;
        std::cout << A[100] << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // 13. std::string
    std::cout << "13. TSet<std::string>:" << std::endl;
    std::string words[] = { "apple", "banana", "apple", "cherry" };
    TSet<std::string> S(words, 4);
    std::cout << "S = " << S << std::endl;

    S.add("date");
    std::cout << "After add(\"date\"): S = " << S << std::endl << std::endl;

    // 14. std::pair<int, double>
    std::cout << "14. TSet<std::pair<int, double>>:" << std::endl;
    std::pair<int, double> pairs[] = { { 1, 1.5 },{ 2, 2.5 },{ 1, 1.5 } };
    TSet<std::pair<int, double>> P(pairs, 3);
    std::cout << "P = " << P << std::endl << std::endl;

    return 0;
}
