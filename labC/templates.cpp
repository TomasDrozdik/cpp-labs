#include <iostream>

//
// Function templates
//

template<typename T>
T min(const T & a, const T & b)
{
    return (a < b) ? a : b;
}

template<typename T, size_t N>
T size(const T (& array) [N])
{
    return N;
}

template<typename T>
bool equal(const T & a, const T & b)
{
    return a == b;
}

// Template Specialization
template<>
bool equal(const double & a, const double & b)
{
    return std::abs(a - b) < 0.0001;
}

//
// Class templates
//

template<typename T, size_t SIZE>
struct Array
{
    T mData[SIZE];

    T * data();
    const T * data() const { return std::addressof(mData); }
    T * begin() { return data(); }
    T * end() { return data(); }
    constexpr size_t size() const { return SIZE; }
};

template<typename T, size_t SIZE>
T * Array<T, SIZE>::data()
{
    return std::addressof(mData);
}

template<typename T>
struct Foo
{
    T mData;

    // Method templates
    template<typename U>
    Foo & operator=(const U & other)
    {
        mData = other;
        return *this;
    }
};

//
// Template inheritance
//

template<typename T>
struct Base
{
    void foo() {}
};

template<typename T>
struct Derived : Base<T>
{
    void bar()
    {
        this->foo();
        Base<T>::foo();
    }
};


//
// Aliass template
//

template<size_t N>
using CharArray = Array<char, N>;


int main(int, char *[])
{
    int i = 1, j = 2;
    long l = 100, m = 200;

    std::cout << min(i, j) << std::endl;
    std::cout << min(l, m) << std::endl;

    // Automatic conversions?
    //std::cout << min(i, l);

    Foo<int> f{1};
    f = 1L;

    Derived<int> d{};
    d.bar();

    CharArray<10> array;
}
