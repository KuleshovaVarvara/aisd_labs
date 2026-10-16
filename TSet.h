#pragma once
#include <iostream>
#include <stdexcept>
#include <random>

template <typename T>
class TSet {
private:
    T* m_data;
    int m_size;
    int m_capacity;

public:
    TSet();
    TSet(const T* arr, int count);
    TSet(int count, T min, T max);
    ~TSet();
    int size() const;
    void add(const T& value);
    TSet(const TSet& other);           
    TSet& operator=(const TSet& other); 
    bool contains(const T& value) const;
    T& operator[](int index);
    const T& operator[](int index) const;
    void remove(const T& value);
    TSet operator+(const TSet& other) const;
    TSet operator*(const TSet& other) const;
    TSet operator-(const TSet& other) const;
    TSet& operator+=(const T& value);
    TSet& operator-=(const T& value);
    TSet operator+(const T& value) const;
    TSet operator-(const T& value) const;
    bool operator==(const TSet& other) const;
    bool operator!=(const TSet& other) const;
    bool isSubset(const TSet& other) const;
    bool isSuperset(const TSet& other) const;
    friend std::ostream& operator<<(std::ostream& os, const TSet<T>& set) {
        os << "{ ";
        for (int i = 0; i < set.m_size; i++) {
            os << set.m_data[i];
            if (i < set.m_size - 1) {
                os << ", ";
            }
        }
        os << " }";
        return os;
    }
   
};

template <typename T>
TSet<T>::TSet() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
TSet<T>::TSet(const T* arr, int count) : m_data(nullptr), m_size(0), m_capacity(0) {
    if (count < 0) {
        throw std::invalid_argument("Count cannot be negative");
    }
    for (int i = 0; i < count; i++) {
        add(arr[i]);
    }
}

template <typename T>
TSet<T>::~TSet() {
    delete[] m_data;
}

template <typename T>
int TSet<T>::size() const {
    return m_size;
}

template <typename T>
void TSet<T>::add(const T& value) {
    if (contains(value)) {
        return;
    }

    if (m_size >= m_capacity) {
        int new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        T* new_data = new T[new_capacity];

        for (int i = 0; i < m_size; i++) {
            new_data[i] = m_data[i];
        }

        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }

    m_data[m_size] = value;
    ++m_size;
}

template <typename T>
TSet<T>::TSet(const TSet& other) : m_data(nullptr), m_size(0), m_capacity(0) {
    *this = other;
}

template <typename T>
TSet<T>& TSet<T>::operator=(const TSet& other) {
    if (this == &other) {
        return *this;
    }

    delete[] m_data;

    m_size = other.m_size;
    m_capacity = other.m_capacity;

    if (m_capacity > 0) {
        m_data = new T[m_capacity];
        for (int i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
    }
    else {
        m_data = nullptr;
    }

    return *this;
}

template <typename T>
bool TSet<T>::contains(const T& value) const {
    for (int i = 0; i < m_size; i++) {
        if (m_data[i] == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
T& TSet<T>::operator[](int index) {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

template <typename T>
const T& TSet<T>::operator[](int index) const {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

template <typename T>
void TSet<T>::remove(const T& value) {
    int index = -1;
    for (int i = 0; i < m_size; i++) {
        if (m_data[i] == value) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return;
    }

    for (int j = index; j < m_size - 1; j++) {
        m_data[j] = m_data[j + 1];
    }
    --m_size;
}

template <typename T>
TSet<T> TSet<T>::operator+(const TSet& other) const {
    TSet<T> result;
    for (int i = 0; i < m_size; i++) {
        result.add(m_data[i]);
    }

    for (int i = 0; i < other.m_size; i++) {
        result.add(other.m_data[i]);
    }
    return result;
}

template <typename T>
TSet<T> TSet<T>::operator*(const TSet& other) const {
    TSet<T> result;
    for (int i = 0; i < m_size; i++) {
        if (other.contains(m_data[i])) {
            result.add(m_data[i]);
        }
    }
    return result;
}

template <typename T>
TSet<T> TSet<T>::operator-(const TSet& other) const {
    TSet<T> result;
    for (int i = 0; i < m_size; i++) {
        if (!other.contains(m_data[i])) {
            result.add(m_data[i]);
        }
    }
    return result;
}

template <typename T>
TSet<T>& TSet<T>::operator+=(const T& value) {
    add(value);
    return *this;
}

template <typename T>
TSet<T>& TSet<T>::operator-=(const T& value) {
    remove(value);
    return *this;
}

template <typename T>
TSet<T> TSet<T>::operator+(const T& value) const {
    TSet<T> result = *this;
    result.add(value);
    return result;
}

template <typename T>
TSet<T> TSet<T>::operator-(const T& value) const {
    TSet<T> result = *this;
    result.remove(value);
    return result;
}

template <typename T>
bool TSet<T>::operator==(const TSet& other) const {
    if (m_size != other.m_size) {
        return false;
    }

    for (int i = 0; i < m_size; i++) {
        if (!other.contains(m_data[i])) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool TSet<T>::operator!=(const TSet& other) const {
    return !(*this == other);
}

template <typename T>
bool TSet<T>::isSubset(const TSet& other) const {
    for (int i = 0; i < m_size; i++) {
        if (!other.contains(m_data[i])) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool TSet<T>::isSuperset(const TSet& other) const {
    return other.isSubset(*this);
}

template <typename T> 
TSet<T>::TSet(int count, T min, T max) : m_data(nullptr), m_size(0), m_capacity(0) {
    if (count < 0) {
        throw std::invalid_argument("Count cannot be negative");
    }
    if (min > max) {
        throw std::invalid_argument("Min cannot be greater than max");
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());
    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dist(min, max);
        for (int i = 0; i < count; i++) {
            add(dist(gen));
        }
    }
    else if constexpr (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dist(min, max);
        for (int i = 0; i < count; i++) {
            add(dist(gen));
        }
    }
}
// Специализация вывода для std::pair
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}