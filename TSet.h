#pragma once
#include <iostream>

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
    for (int i = 0; i < m_size; i++) {
        if (m_data[i] == value) {
            return;
        }
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