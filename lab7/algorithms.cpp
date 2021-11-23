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

bool cmp(const int & a, const int & b)
{
    return a > b;
}

int acc_product(int a, int val)
{
    return a * val;
}

bool even(int a)
{
    return a % 2 == 0;
}

int main(void)
{
    {
        std::vector<int> v{9,8,1,2,8,7,9,4};

        print(v);

        int x = 7;
        auto it = std::find(v.cbegin(), v.cend(), x);
        if (it != v.cend()) {
            std::cout << "Found: " << x << " at index " << std::distance(v.cbegin(), it) << std::endl;
        } else {
            std::cout << "Not found: " << x << std::endl;
        }
    }
    
    // TODO: try other algorithms from https://en.cppreference.com/w/cpp/algorithm
    // use predicates, comparators, inserters...

    {
        // min/max
        std::vector<int> v{9,8,1,2,8,7,9,4};
        auto it = std::min_element(v.cbegin(), v.cend());
        std:: cout << "min: " << *it << std::endl; 

        it = std::min_element(v.cbegin(), v.cend(), &cmp);
        std:: cout << "min with custom comparator (max): " << *it << std::endl; 
    }
    {
        // accumulate
        std::vector<int> v{9,8,1,2,8,7,9,4};
        auto sum = std::accumulate(v.cbegin(), v.cend(), 0);
        std::cout << "sum: " << sum << std::endl;

        auto product = std::accumulate(v.cbegin(), v.cend(), 1, &acc_product);
        std::cout << "product: " << product << std::endl;
    }
    {
        // find_if
        std::vector<int> v{9,8,1,2,8,7,9,4};
        auto it = find_if(v.cbegin(), v.cend(), &even);
        if (it != v.cend()) {
            std::cout << "find_if: " << *it << " at index " << std::distance(v.cbegin(), it) << std::endl;
        } else {
            std::cout << "find_if: not found " << std::endl;
        }
    }
    {
        // unique
        std::vector<int> v{9,8,1,2,8,7,9,4};
        std::sort(v.begin(), v.end());
        std::cout << "sort: "; print(v);

        auto end = std::unique(v.begin(), v.end());
        std::cout << "unique: "; print(v);

        v.erase(end, v.end());
        std::cout << "erase dupes: "; print(v);
    }
    {
        // fill
        std::vector<int> v{9,8,1,2,8,7,9,4};
        std::fill(v.begin(), v.end(), -1);
        std::cout << "fill -1: "; print(v);
    }

    return 0;
}
