#include <iostream>

template<typename T, T val>
struct integral_constant
{
    static constexpr T value = val;
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template<typename T>
struct is_pointer : false_type
{
};

template<typename T>
struct is_pointer<T*> : true_type
{
};

static_assert(is_pointer<int*>::value);
static_assert(not is_pointer<int>::value);

template<typename T, size_t SIZE>
struct Array
{
    static_assert(not is_pointer<T>::value); // in c++20 you can use Concepts!

    T mData[SIZE];

    T * data();
    const T * data() const { return std::addressof(mData); }
    T * begin() { return data(); }
    T * end() { return data(); }
    constexpr size_t size() const { return SIZE; }
};

int main(int, char **)
{
    int x{22};

    Array<int, 2> valid{x};

    // Array<int *, 2> invalid{&x};
}
