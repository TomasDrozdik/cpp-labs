#include <iostream>

char c;

#define SIZEOF_PRINT(type) \
    std::cout << "sizeof(" <<  #type << ") ";  \
    std::cin  >> c; \
    std::cout << ' ' << sizeof(type) << '\n';

struct Foo {
    std::size_t x;
};

struct Bar {
    uint32_t a;
    bool b;
    // padding
};

struct Baz {
    bool b;
    // padding
    uint32_t a;
};

struct Com {
    uint32_t a[10];
};

// No padding, much worse on the CPU because its instructions can only work with
// aligned memory so it has to do another instruction to align the memory anyway.
// If it deosn't it almost certainly means that the instructions are gona be
// slower.
struct __attribute__((__packed__))  FooBar {
    bool b;
    uint32_t a[10];
    char c;
};

int main() {
    SIZEOF_PRINT(bool);
    SIZEOF_PRINT(char);
    SIZEOF_PRINT(int);
    SIZEOF_PRINT(int32_t);
    SIZEOF_PRINT(long);
    SIZEOF_PRINT(long long);
    SIZEOF_PRINT(uint64_t);
    SIZEOF_PRINT(std::size_t);
    SIZEOF_PRINT(Foo);
    SIZEOF_PRINT(Bar);
    SIZEOF_PRINT(Baz);
    SIZEOF_PRINT(Com);
    SIZEOF_PRINT(FooBar);

    return 0;
}