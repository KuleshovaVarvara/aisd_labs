export module TSet;

import std;

export template <typename T>
class TSet {
private:
    T* m_data;
    int m_size;
    int m_capacity;

public:
    static inline const double EPSILON = 1e-9;

    TSet();
    TSet(const T* arr, int count);
    TSet(int count, T min, T max);
    ~TSet();

    TSet(const TSet& other);
    TSet& operator=(const TSet& other);

    int size() const;
    bool contains(const T& value) const;
    void add(const T& value);
    void remove(const T& value);

    T& operator[](int index);
    const T& operator[](int index) const;

    TSet operator+(const TSet& other) const;
    TSet operator*(const TSet& other) const;
    TSet operator-(const TSet& other) const;

    TSet& operator+=(const T& value);
    TSet& operator-=(const T& value);
    TSet operator+(const T& value) const;
    TSet operator-(const T& value) const;

    bool operator==(const TSet& other) const;
    bool operator!=(const TSet& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TSet<T>& set) {
        os << "{ ";
        for (int i = 0; i < set.m_size; i++) {
            os << set.m_data[i];
            if (i < set.m_size - 1) os << ", ";
        }
        os << " }";
        return os;
    }
};


template <typename T>
TSet<T>::TSet() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
TSet<T>::TSet(const T* arr, int count) : m_data(nullptr), m_size(0), m_capacity(0) {
    if (count < 0) throw std::invalid_argument("Count cannot be negative");
    for (int i = 0; i < count; i++) {
        add(arr[i]);
    }
}

template <typename T>
TSet<T>::TSet(int count, T min, T max) : m_data(nullptr), m_size(0), m_capacity(0) {
    if (count < 0) throw std::invalid_argument("Count cannot be negative");

    static std::random_device rd;
    static std::mt19937 gen(rd());

    if constexpr (std::is_integral<T>::value) {
        if (min > max) throw std::invalid_argument("Min cannot be greater than max");
        std::uniform_int_distribution<T> dist(min, max);
        for (int i = 0; i < count; i++) {
            add(dist(gen));
        }
    }
    else if constexpr (std::is_floating_point<T>::value) {
        if (min > max) throw std::invalid_argument("Min cannot be greater than max");
        std::uniform_real_distribution<T> dist(min, max);
        for (int i = 0; i < count; i++) {
            add(dist(gen));
        }
    }
    else if constexpr (std::is_same_v<T, std::string>) {
        if (min.empty() || max.empty()) throw std::invalid_argument("Min/Max string cannot be empty");

        std::uniform_int_distribution<short> dist(static_cast<short>(min[0]), static_cast<short>(max[0]));

        for (int i = 0; i < count; i++) {
            std::string rand_str;
            for (int j = 0; j < 3; j++) {
                rand_str += static_cast<char>(dist(gen));
            }
            add(rand_str);
        }
    }
    else if constexpr (std::is_same_v<T, std::pair<int, double>>) {
        std::uniform_int_distribution<int> dist_int(min.first, max.first);
        std::uniform_real_distribution<double> dist_double(min.second, max.second);
        for (int i = 0; i < count; i++) {
            std::pair<int, double> p = { dist_int(gen), dist_double(gen) };
            add(p);
        }
    }
}

template <typename T>
TSet<T>::~TSet() {
    delete[] m_data;
}

template <typename T>
TSet<T>::TSet(const TSet& other) : m_data(nullptr), m_size(0), m_capacity(0) {
    *this = other;
}

template <typename T>
TSet<T>& TSet<T>::operator=(const TSet& other) {
    if (this == &other) return *this;
    delete[] m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    if (m_capacity > 0) {
        m_data = new T[m_capacity];
        for (int i = 0; i < m_size; i++) m_data[i] = other.m_data[i];
    }
    else {
        m_data = nullptr;
    }
    return *this;
}

template <typename T>
int TSet<T>::size() const {
    return m_size;
}

template <typename T>
bool TSet<T>::contains(const T& value) const {
    for (int i = 0; i < m_size; i++) {
        //точность
        if constexpr (std::is_floating_point<T>::value) {
            if (std::abs(m_data[i] - value) < EPSILON) return true;
        }
        else {
            if (m_data[i] == value) return true;
        }
    }
    return false;
}

template <typename T>
void TSet<T>::add(const T& value) {
    if (contains(value)) return;
    if (m_size >= m_capacity) {
        int new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        T* new_data = new T[new_capacity];
        for (int i = 0; i < m_size; i++) new_data[i] = m_data[i];
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }
    m_data[m_size] = value;
    ++m_size;
}

template <typename T>
void TSet<T>::remove(const T& value) {
    int index = -1;
    for (int i = 0; i < m_size; i++) {
        //точность
        if constexpr (std::is_floating_point<T>::value) {
            if (std::abs(m_data[i] - value) < EPSILON) { index = i; break; }
        }
        else {
            if (m_data[i] == value) { index = i; break; }
        }
    }
    if (index == -1) return;
    for (int j = index; j < m_size - 1; j++) m_data[j] = m_data[j + 1];
    --m_size;
}

template <typename T>
T& TSet<T>::operator[](int index) {
    if (index < 0 || index >= m_size) throw std::out_of_range("Index out of range");
    return m_data[index];
}

template <typename T>
const T& TSet<T>::operator[](int index) const {
    if (index < 0 || index >= m_size) throw std::out_of_range("Index out of range");
    return m_data[index];
}

template <typename T>
TSet<T> TSet<T>::operator+(const TSet& other) const {
    TSet<T> result;
    for (int i = 0; i < m_size; i++) result.add(m_data[i]);
    for (int i = 0; i < other.m_size; i++) result.add(other.m_data[i]);
    return result;
}

template <typename T>
TSet<T> TSet<T>::operator*(const TSet& other) const {
    TSet<T> result;
    for (int i = 0; i < m_size; i++) {
        if (other.contains(m_data[i])) result.add(m_data[i]);
    }
    return result;
}

template <typename T>
TSet<T> TSet<T>::operator-(const TSet& other) const {
    TSet<T> result;
    for (int i = 0; i < m_size; i++) {
        if (!other.contains(m_data[i])) result.add(m_data[i]);
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
    if (m_size != other.m_size) return false;
    for (int i = 0; i < m_size; i++) {
        if (!other.contains(m_data[i])) return false;
    }
    return true;
}

template <typename T>
bool TSet<T>::operator!=(const TSet& other) const {
    return !(*this == other);
}

//вне класса
export template <typename T>
bool isSubset(const TSet<T>& A, const TSet<T>& B) {
    for (int i = 0; i < A.size(); i++) {
        if (!B.contains(A[i])) return false;
    }
    return true;
}

export template <typename T>
bool isSuperset(const TSet<T>& A, const TSet<T>& B) {
    return isSubset(B, A);
}

export template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}