#include <numeric>
#include <iostream>

#include "ncvec.h"

struct A
{
    int x;
};

int main(void)
{
#if 1
    {
        std::cout << "> push_back() print using foreach loop" << std::endl;

        ncvec<int, 3> v;
        for (auto i = 0; i < 10; ++i) {
            v.push_back(i);
        }

        for (auto i : v) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    }
#endif
#if 1
    {
        std::cout << "> Verify that operators are not invalidated" << std::endl;

        ncvec<int, 10> v;
        v.reserve(23);
        for (auto i = 0; i < 23; ++i) {
            v.push_back(i);
        }

        auto begin_it = v.begin();
        v.push_back(9999);

        for (auto it = begin_it; it != v.end(); ++it) {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
    }
#endif
#if 1
    {
        std::cout << "> Custom structure use of ncvec::iterator::operator->" << std::endl;

        ncvec<A> va;
        va.push_back(A{73});
        std::cout << va.begin()->x << std::endl;
    }
#endif
#if 1
    {
        ncvec<int> v;
        for (auto i = 0; i < 10; ++i) {
            v.push_back(i);
        }

        std::cout << "> Use algorithms! see that we can call std::begin(v) instead of v.begin()" << std::endl;
        auto res = std::accumulate(std::begin(v), std::end(v), 1,
            [](int acc, int x) { return acc + x; });
        std::cout << res << std::endl;
    }
#endif
}
