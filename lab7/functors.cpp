#include <cassert>

#include <iostream>
#include <string>
#include <unordered_map>

struct S
{
    int i;

    bool operator==(const S & other) const
    {
        std::cerr << "bool operator==(const S & other) const" << std::endl;
        return i == other.i;
    }
};

struct SHash
{
    std::size_t operator()(const S & s) const
    {
        std::cerr << "SHash::operator()(const S & s) const" << std::endl;
        std::hash<int> h{};
        return h(s.i);
    }
};

struct SEqual
{
    bool operator()(const S & s1, const S & s2) const
    {
        std::cerr << "SEqual::operator()(const S & s1, const S & s2) const" << std::endl;
        return s1.i == s2.i;
    }
};

struct SAll
{
    std::size_t operator()(const S & s) const
    {
        std::cerr << "SAll::operator()(const S & s) const" << std::endl;
        return std::hash<int>()(s.i);
    }

    bool operator()(const S & s1, const S & s2) const
    {
        std::cerr << "SAll::operator()(const S & s1, const S & s2) const" << std::endl;
        return s1.i == s2.i;
    }
};

namespace std
{
    template<>
    struct hash<S>
    {
        size_t operator()(const S & s) const
        {
            std::cerr << "std::hash<S>::operator()(const S & s) const" << std::endl;
            return hash<int>{}(s.i);
        }
    };

#if 0 // Undefine to make use of default implementation of equal_to<S> that calls S::operator==
    template<>
    struct equal_to<S>
    {
        bool operator()(const S & s1, const S & s2) const
        {
            std::cerr << "std::equal_to<S>::operator()(const S & s1, const S & s2) const" << std::endl;
            return s1.i == s2.i;
        }
    };
#endif
}

int main(void)
{
    // Make this compile
    std::unordered_map<S, std::string> smap{};

    // Insert elements into map using 3 different ways
    {
        std::unordered_map<S, std::string, SHash> smap{};

        S key{};
        smap[key] = "hello";

        auto [it, success] = smap.insert(std::pair(S{5}, "second"));

        auto [it1, success1] = smap.insert(std::make_pair(S{5}, "other"));

        auto [it2, success2] = smap.insert({S{5}, "other"});

        assert(!success2);

        smap.insert_or_assign(S{5}, "other");

        smap.emplace(S{6}, "other");

        for (auto [key, value] : smap) {
            std::cout << "[" << key.i << "]: " << value << std::endl;
        }
    }
    {
        std::unordered_map<S, int> smap{};

        smap[S{5}] = 1;
        smap[S{5}] = 1;
    }

    return 0;
}