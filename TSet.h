#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class TSet {
private:
    T* m_data;      
    int m_size;    
    int m_capacity; 

public:
    TSet();                 
    ~TSet();                   
    int size() const; 
    void add(const T& value);
    bool contains(const T& value) const;
    T& operator[](int index);
    const T& operator[](int index) const;
    void remove(const T& value);
    TSet operator+(const TSet& other) const;
    TSet operator*(const TSet& other) const;
    TSet operator-(const TSet& other) const;
};

template <typename T>
TSet<T>::TSet() : m_data(nullptr), m_size(0), m_capacity(0) {}

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