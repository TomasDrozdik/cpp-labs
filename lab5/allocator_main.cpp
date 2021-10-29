#include <iostream>

#include <cstdlib>

#include "allocator.h"

using namespace lab4;

int main() {
    constexpr size_t len = 100;
    void * p = std::malloc(len);
    auto allocator = NewAllocator(p, len);

    auto blk = allocator->allocate();
    std::cout << "New block allocated by our allocator: " << blk << std::endl;
    *blk.ptr = 42;
    std::cout << "Value of the *blk.ptr is " << *blk.ptr << std::endl;
}
