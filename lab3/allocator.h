#pragma once

#include <vector>
#include <cstdint> // equivalent to #include <stdint.h>

namespace lab3 {

struct allocator {
public:
    using TYPE = uint64_t;

    struct Blk {
        TYPE * p;
        std::size_t n;
    };

    // Allocate consecutive memory place n variables of type TYPE.
    // If no such memory exists return nullptr.
    Blk allocate(std::size_t n);

    // Deallocate Blk returned by allocated.
    // Assume that the block was in fact returned by allocate and that it it freed only once.
    void deallocate(Blk block);

    // Decide whether given block was allocated by allocate.
    bool owns(Blk block) const;

    void debug_print() const;

private:
    // In place allocation of underlaying memory, check what is the sizeof(buffer) and what is the
    // sizeof(allocator)? Where is it stored?
    constexpr static std::size_t BUFFER_SIZE = sizeof(TYPE) * 1024;
    uint8_t buffer[BUFFER_SIZE];

    // Options
    // 1. Bump pointer
    // TYPE * bump_pointer;
    //
    // 2. Stack Allocator
    // TYPE * stack_top;
    //
    // 3. Free List
    // TYPE * freelist_root;
    //
    // 4. Bitmap
    // std::vector<bool> bitmap;
};

}