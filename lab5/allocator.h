#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include <cassert> // equivalent to #include <assert.h> this holds for all C libraries
#include <cstdint>

namespace lab4
{

struct Allocator
{
public:
    using TYPE = uint64_t;

    struct Blk
    {
        TYPE * ptr{};
        std::size_t len{};

        // Returns pointer one past the length of the Blk
        inline TYPE * end_ptr() const
        {
            return ptr + len;
        }
    };

    Allocator(void * p, std::size_t len)
        : memory{static_cast<TYPE *>(p), len / sizeof(TYPE)}
    {
    }

    Allocator(const Allocator & other)
        : memory{new TYPE[other.memory.len], other.memory.len}
    { 
    }

    

    Allocator & operator=(const Allocator & other) = delete;

    // Allocator a1{ptr, 5};
    // Allocator a2{a1};
    // a2 = a3;

    virtual ~Allocator()
    {
        delete[] memory.ptr;
    }

    // Allocate consecutive memory place n variables of type TYPE.
    // If no such memory exists return nullptr.
    virtual Blk allocate(std::size_t n = 1) = 0;

    // Deallocate Blk returned by allocated.
    // Assume that the block was in fact returned by allocate and that it it freed only once.
    virtual void deallocate(Blk block) = 0;

    // Decide whether given block was allocated by allocate.
    // If the block was deallocated the behavior is undefined (you'll see it's better this way) :-)
    virtual bool owns(Blk block) const
    {
        return block.ptr >= memory.ptr and
               block.ptr + block.len <= memory.end_ptr();
    }

protected:
    Blk memory;

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


// Overload operator<< in order to be able to call following code:
// ``` c++
// Blk block{.ptr=std::nullptr_t, .len=0};
// std::cout << block;
// ```
// Output:
// Blk(ptr=0, len=0)
std::ostream & operator<<(std::ostream & os, const Allocator::Blk & blk)
{
    os << "Blk(ptr=" << blk.ptr << ", len=" << blk.len << ")";
    return os;
}


struct BumpAllocator
    : public Allocator
{
public:

    BumpAllocator(void * p, std::size_t len)
        : Allocator{p, len}, bump_pointer{memory.ptr}
    {
    }

    virtual Blk allocate(std::size_t n = 1) override
    {
        assert(bump_pointer < memory.end_ptr());
        if (bump_pointer + n > memory.end_ptr()) {
            return Blk{nullptr, 0};
        }
        auto new_blk = Blk{bump_pointer, n};
        bump_pointer += n;
        return new_blk;
    }

    virtual void deallocate(Blk) override
    {
        // Bump pointer allocator cannot deallocate...
        return;
    }

private:
    TYPE * bump_pointer;
};


struct StackAllocator
    : public Allocator
{
public:

    StackAllocator(void * p, std::size_t len)
        : Allocator{p, len}
        , stack_top{memory.ptr}
    {
    }

    virtual Blk allocate(std::size_t n = 1) override
    {
        assert(stack_top <= memory.end_ptr());
        if (stack_top + n > memory.end_ptr()) {
            return Blk{nullptr, 0};
        }
        auto new_blk = Blk{stack_top, n};
        stack_top += n;
        return new_blk;
    }

    virtual void deallocate(Blk block) override
    {
        // If this is the last block then we dealloc otherwise not
        if (block.ptr == stack_top - block.len) {
            stack_top -= block.len;
        }
        return;
    }

private:
    TYPE * stack_top;
};


struct FreelistAllocator
    : public Allocator
{
public:

    FreelistAllocator(void * p, std::size_t len)
        : Allocator{p, len}
        , bump_ptr{memory.ptr}
    {
    }

    virtual Blk allocate(std::size_t n = 1) override
    {
        assert(n == 1);
        Blk new_blk{nullptr, 1};
        if (!!free_list_next) {
            new_blk.ptr = free_list_next;
            free_list_next = reinterpret_cast<TYPE *>(*free_list_next);
        } else if (bump_ptr + n <= memory.end_ptr()) {
            new_blk.ptr = bump_ptr;
            ++bump_ptr;
        }
        return new_blk;
    }

    virtual void deallocate(Blk block) override
    {
        assert(block.len == 1);
        *block.ptr = reinterpret_cast<TYPE>(free_list_next);
        free_list_next = block.ptr;
    }

    virtual bool owns(Blk block) const override
    {
        assert(block.len == 1);
        return Allocator::owns(block);
    }

private:
    TYPE * bump_ptr{};
    TYPE * free_list_next{};
};


struct BitmapAllocator
    : public Allocator
{
private:
    static constexpr bool used = true;
    static constexpr bool free = false;

    std::vector<bool> bitmap{};

    inline auto bitmap_indices(Blk block) const
    {
        std::size_t start_idx = block.ptr - memory.ptr;
        return std::pair{start_idx, start_idx + block.len};
    }

    inline void bitmap_fill(std::size_t start, std::size_t end, bool value)
    {
        assert(start <= end && end <= bitmap.size());
        std::fill(bitmap.begin() + start, bitmap.begin() + end, value);
    }

public:
    BitmapAllocator(void * p, std::size_t len)
        : Allocator{p, len}
    {
        bitmap.resize(memory.len);
        bitmap_fill(0, bitmap.size(), free);
    }

    virtual Blk allocate(std::size_t n = 1) override
    {
        std::size_t free_counter = 0;
        for (std::size_t i = 0; i < bitmap.size(); ++i) {
            free_counter = bitmap[i] == free ? free_counter + 1 : 0;
            if (free_counter == n) {
                std::size_t start = i - (n - 1);
                bitmap_fill(start, start + n, used);
                return Blk{memory.ptr + start, n};
            }
        }
        return Blk{nullptr};
    }

    virtual void deallocate(Blk block) override
    {
        assert(owns(block));
        const auto [start_idx, end_idx] = bitmap_indices(block);
        bitmap_fill(start_idx, end_idx, free);
    }

    virtual bool owns(Blk block) const override
    {
        if (!Allocator::owns(block)) {
            return false;
        }

        // This may be a bad idea. Can you guess why?
        const auto [start_idx, end_idx] = bitmap_indices(block);
        for (auto i = start_idx; i < end_idx; ++i) {
            if (bitmap[i] == free) {
                return false;
            }
        }
        return true;





        // Answer: every owns function is O(1) thus user expects it to be fast, even though with
        // this kind of structure we can do better check it may be a bad idea because it would
        // violate assumptions users of this class can make about performance of such call.
        // Safest bet is to document the complexity.
    }
};


// To showcase what are the issues with current tests.
struct FakeAllocator
    : public Allocator
{
    FakeAllocator(void * p, std::size_t len)
        : Allocator{p, len}
    {
    }

    virtual Blk allocate(std::size_t) override
    {
        if (counter++ == 50) {
            counter = 0;
            return Blk{nullptr};
        }
        return Blk{&dummy_val, 1};
    }

    virtual void deallocate(Blk) override
    {
    }

    virtual bool owns(Blk) const override
    {
        return true;
    }

private:
    TYPE dummy_val{0xDEADBEEFll};
    std::size_t counter{};
};

// Factory method used in tests
std::unique_ptr<Allocator> NewAllocator(void * ptr, std::size_t len)
{
    return std::make_unique<FreelistAllocator>(ptr, len);
}

}