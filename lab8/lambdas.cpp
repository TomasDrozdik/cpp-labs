#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>

template<typename ForwardIt>
void print(ForwardIt begin, ForwardIt end)
{
    if (begin == end) {
        std::cout << "empty" << std::endl;
        return;
    }
    auto it = begin;
    for ( ; it + 1 < end; ++it) {
        std::cout << *it << ", ";
    }
    std::cout << *it << std::endl;
}

template<class Container>
void print(Container c)
{
    print(std::cbegin(c), std::cend(c));
}

struct Searcher
{
    int item{};

    Searcher(int item) : item(item)
    {}

    // Notice that this does not need to be const
    bool operator()(int i)
    {
        return i == item;
    }
};

struct Summer
{
    int sum{};

    void operator()(int i)
    {
        this->sum += i;
    }
};

int main(void)
{
    // Algorithms using functors
    {
        std::cout << "Functors" << std::endl;

        std::vector<int> v{9,8,1,2,8,7,9,4};
        print(v);

        Searcher searcher{2};
        auto it = std::find_if(v.cbegin(), v.cend(), searcher);
        if (it != v.cend()) {
            std::cout << "Found: " << searcher.item << " at index " << std::distance(v.cbegin(), it) << std::endl;
        } else {
            std::cout << "Not found: " << searcher.item << std::endl;
        }

        // Sum without an accumulator
        Summer summer{};
        Summer result = std::for_each(v.cbegin(), v.cend(), summer);
        std::cout << "Summer result: " << result.sum << std::endl;
    }

    std::cout << std::endl;

    // Algorithms using lambdas
    {
        std::cout << "Lambdas" << std::endl;

        std::vector<int> v{9,8,1,2,8,7,9,4};
        print(v);

        int x = 2;
        auto it = std::find_if(v.cbegin(), v.cend(), [x](int item) -> bool { return item == x; });
        if (it != v.cend()) {
            std::cout << "Found: " << x << " at index " << std::distance(v.cbegin(), it) << std::endl;
        } else {
            std::cout << "Not found: " << x << std::endl;
        }

        // Sum without an accumulator
        int sum{};
        std::for_each(v.cbegin(), v.cend(), [&sum](int i) { sum += i; });
        std::cout << "Summer result: " << sum << std::endl;
    }

    std::cout << std::endl;

    {
        std::vector<int> v{9,8,1,2,8,7,9,4};
        print(v);

        // TODO: 1. Get container of elements greater than `X` incremented by `Y`.

        print(v);
    }

    std::cout << std::endl;

    {
        std::vector<int> v{9,8,1,2,8,7,9,4};
        print(v);

        int x = 5;

        // TODO: 2. Find first element different from previous one by at least `X`.

        print(v);
    }

    std::cout << std::endl;

    {
        std::vector<int> v{9,8,1,2,8,7,9,4};
        print(v);

        // TODO: 3. Increment numbers following pattern: `[first + X, second + 2*X, third + 3*X]`.

        print(v);
    }

    std::cout << std::endl;

    {
        std::vector<int> v{9,8,1,2,8,7,9,4};
        print(v);

        // TODO: 4. Get difference of neighbor values.

        print(v);
    }

    std::cout << std::endl;

    {
        std::vector<int> v{9,8,1,2,8,7,9,4};
        std::vector<int> result{};
        print(v);

        // TODO: 5. Create a new container of second powers of even and third powers of odd numbers.
        // That is result container will be of same size as the input. And if input[i] is even then
        // output[i] = input[i] squared. If it's odd then output[i] = input[i] to the third power.

        print(result);
    }

    return 0;
}
