#include <array>
#include <memory>
#include <vector>

template<typename T, std::size_t N = 100>
struct ncvec
{
    struct iterator
    {
        iterator(ncvec & c, bool is_end)
            : c(c)
            , is_end(is_end)
            , idx(0)
        {}

        iterator(const iterator & other)
            : c(other.c)
            , is_end(other.is_end)
            , idx(other.idx)
        {}

        iterator & operator=(const iterator & other)
        {
            this->c = other.c;
            this->is_end = other.is_end;
            this->idx = other.idx;
            return *this;
        }

        T & operator*() const
        {
            return c[get_idx()];
        }

        T * operator->() const
        {
            return &this->operator*();
        }

        bool operator==(const iterator & other)
        {
            auto same_container = &this->c.data == &other.c.data;
            if (same_container) {
                return this->get_idx() == other.get_idx();
            } else {
                return false;
            }
        }

        bool operator!=(const iterator & other)
        {
            return !(*this == other);
        }

        iterator & operator++()
        {
            ++idx;
            return *this;
        }

        // Postfix operator++ notice the "weird int parameter", that is used to distinuguish this
        // operator from prefix operator since overloads can only differ in types of arguments not
        // in return value type. The int parameter is not used and thus it doesn't have a name.
        iterator operator++(int)
        {
            auto copy = *this;
            ++this->idx;
            return copy;
        }

    private:
        std::size_t get_idx() const
        {
            if (is_end) {
                return c.end_idx;
            } else {
                return idx;
            }
        }

        ncvec & c;
        bool is_end;
        std::size_t idx;
    };

    ncvec() = default;
    ncvec(const ncvec &) = delete;
    ncvec(ncvec &&) = default;
    ncvec & operator=(const ncvec &) = delete;
    ncvec & operator=(ncvec &&) = default;
    ~ncvec() = default;

    void reserve(std::size_t new_capacity)
    {
        if (capacity() >= new_capacity) {
            return;
        }
        auto total_blocks_needed = new_capacity / N;
        if (new_capacity % N == 0) {
            ++total_blocks_needed;
        }
        auto current_blocks = data.size();
        push_block(total_blocks_needed - current_blocks);
    }

    std::size_t capacity() const
    {
        return data.size() * N;
    }

    std::size_t size() const
    {
        return end_idx;
    }

    void clear() const
    {
        end_idx = 0;
    }

    void push_back(const T & x)
    {
        if (end_idx == capacity()) {
            push_block();
        }
        this->operator[](end_idx) = x;
        ++end_idx;
    }

    void push_back(T && x)
    {
        if (end_idx == capacity()) {
            push_block();
        }
        this->operator[](end_idx) = x;
        ++end_idx;
    }

    T & operator[](std::size_t idx)
    {
        const auto [top_lvl_idx, bottom_lvl_idx] = get_index(idx);
        return data[top_lvl_idx]->operator[](bottom_lvl_idx);
    }

    const T & operator[](std::size_t idx) const
    {
        const auto [top_lvl_idx, bottom_lvl_idx] = get_index(idx);
        return data[top_lvl_idx]->operator[](bottom_lvl_idx);
    }

    iterator begin()
    {
        bool is_end = false;
        return iterator(*this, is_end);
    }

    iterator end()
    {
        bool is_end = true;
        return iterator(*this, is_end);
    }

private:
    std::pair<std::size_t, std::size_t> get_index(std::size_t idx) const
    {
        return {idx / N, idx % N};
    }

    void push_block(std::size_t blocks = 1)
    {
        for (std::size_t i = 0; i < blocks; ++i) {
            data.push_back(std::make_unique<std::array<T, N>>());
        }
    }

    std::size_t end_idx = 0;
    std::vector<std::unique_ptr<std::array<T, N>>> data;
};
