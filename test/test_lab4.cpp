#include <gtest/gtest.h>

#include "lab4/allocator.h"

using namespace lab4;

// Fixture with a parametrized test
// Create a memory pool of a fixed size
struct ParametrizedAllocatorFixture
    : public testing::TestWithParam<std::size_t>
{
public:
    void * ptr{};
    std::size_t len{};
    std::unique_ptr<Allocator> allocator{};

protected:
    void SetUp() override
    {
        len = GetParam();
        ptr = new void * [len];
        allocator = NewAllocator(ptr, len);
    }

    void TearDown() override
    {
        // empty we expect the allocator to free the memory once it is done.
    }
};

#define CHECK_WRITEABILITY(blk) \
    constexpr Allocator::TYPE val = 0xDEADBEEFll; \
    ASSERT_NE(blk.ptr, nullptr); \
    for (size_t i = 0; i < blk.len; ++i) { \
        blk.ptr[i] = val; \
        ASSERT_EQ(blk.ptr[i], val) << "Value at offset \'" << i \
                                   << "\' of " << blk << " is not writable."; \
    } \

TEST_P(ParametrizedAllocatorFixture, DemonstrateFixtureTest)
{
    EXPECT_TRUE(GetParam() > 0);
}

TEST_P(ParametrizedAllocatorFixture, TestSingleAlloc)
{
    auto blk = allocator->allocate();
    CHECK_WRITEABILITY(blk);
}

TEST_P(ParametrizedAllocatorFixture, AllocCheckDeallocRepeat)
{
    for (size_t i = 0; i < 50; ++i) {
        auto blk = allocator->allocate();
        EXPECT_TRUE(allocator->owns(blk));
        CHECK_WRITEABILITY(blk);
        allocator->deallocate(blk);
    }
}

TEST_P(ParametrizedAllocatorFixture, AllocAllCheckDeallocAllAllocAll)
{
    // Alloc all
    std::vector<Allocator::Blk> orig_blks{};
    for (;;) {
        auto blk = allocator->allocate();
        if (blk.ptr == nullptr) {
            break;
        }
        orig_blks.push_back(blk);
    }

    // Check
    for (const auto & blk : orig_blks) {
        CHECK_WRITEABILITY(blk);
    }

    // Dealloc all
    for (const auto & blk : orig_blks) {
        EXPECT_TRUE(allocator->owns(blk));
        allocator->deallocate(blk);
    }

    // Alloc all again but write to the memory at the same time
    std::size_t allocated_blocks_len = 0;
    for (;;) { // equivalent to `while(1)` or `while(true)`
        auto blk = allocator->allocate();
        if (blk.ptr == nullptr) { // equivalent to `if (!blk.ptr)`
            break;
        }
        EXPECT_TRUE(allocator->owns(blk));
        CHECK_WRITEABILITY(blk);
        ++allocated_blocks_len;
    }

    EXPECT_EQ(orig_blks.size(), allocated_blocks_len);
}

INSTANTIATE_TEST_SUITE_P(DifferentSizedMemoryPoolSuite,
                         ParametrizedAllocatorFixture,
                         testing::Values(128, 1024)); // 128 B, and 1 KiB memory pool size
