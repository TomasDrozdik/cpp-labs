#include<iostream>

#include "allocator.h"

namespace lab3 {

void allocator::debug_print() const {
    for (std::size_t i = 0; i < BUFFER_SIZE; ++i) {
        std::cout << std::hex << static_cast<uint>(this->buffer[i]) << ' ';
        if (i != 0 && i % 30 == 0) {
            std::cout << '\n';
        }
    }
}

}