#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

void print(vector<int>::const_iterator begin, vector<int>::const_iterator end)
{
    cerr << "call: void print(vector<int>::const_iterator begin, vector<int>::const_iterator end)" << endl;
    for (auto it = begin; it != end; ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Overloaded version of previous print function.
// If we were to pass arguments matching the exact types (vector<int>::const_iterator) then the
// previous overload will be chosen, otherwise it will instantiate this templated version
// for passed types of arguments.. will be discussed later.
template<typename Iterator>
void print(Iterator begin, Iterator end)
{
    cerr << "call: void print(Iterator begin, Iterator end)" << endl;
    for (auto it = begin; it != end; ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void bubblesort(vector<int>::iterator begin, vector<int>::iterator end)
{
    cerr << "call: void bubblesort(vector<int>::iterator begin, vector<int>::iterator end)" << endl;
    if (begin == end) {
        return;
    }
    bool changed = true;
    while(changed){
        changed = false;
        for(auto it = begin; it+1 != end; ++it){
            if(*it < *(it + 1)){
                swap(*it, *(it + 1));
                changed = true;
            }
        }
    }
}

template<typename Iterator>
void bubblesort(Iterator begin, Iterator end)
{
    cerr << "call: void void bubblesort(Iterator begin, Iterator end)" << endl;
    // Range of size 0 or 1 is already sorted
    if (begin == end || begin + 1 == end) {
        return;
    }
    bool changed = true;
    while (changed) {
        changed = false;
        // Initial condition ensured that there are at least 2 elements so we can access `it + 1`
        for(auto it = begin; it + 1 != end; ++it){
            if (*it < *(it + 1)) {
                swap(*it, *(it + 1));
                changed = true;
            }
        }
    }
}

struct S
{
    int i;

    bool operator<(const S & other) const
    {
        cerr << "call: S::operator<" << endl;
        return this->i < other.i;
    }
};

int main(void)
{
#if 1
    cout << "print using explicit types" << endl;
    {
        vector<int> vec = {8, 3, 10, 2};
        print(vec.cbegin(), vec.cend());
    }
#endif
#if 1
    {
    cout << "bubblesort using explicit types" << endl;
        vector<int> vec = {7, 8, 3, 10, 2};
        bubblesort(vec.begin(), vec.end());
    }
#endif
#if 1
    {
    cout << "bubblesort on different vectory type -> use templated version" << endl;
        vector<long> vec = {7, 8, 3, 10, 2};
        bubblesort(vec.begin(), vec.end());
    }
#endif
#if 1
    {
    cout << "bubblesort on different container -> use templated version" << endl;
        std::array<int, 5> a = {7, 8, 3, 10, 2};
        bubblesort(a.begin(), a.end());
    }
#endif
#if 1
    {
        cout << "print vector and set, check used overload" << endl;
        vector<long> vec = {7, 8, 3, 10, 2};
        print(vec.cbegin(), vec.cend());

        std::set<int> s = {1, 2, 3};
        print(vec.rbegin(), vec.rend());
    }
#endif
#if 1
    {
        cout << "histogram (need input, cancel with <Ctrl-d> on UNIX" << endl;
        map<char, int> hist{};
        char c;
        while (cin >> c) {
            hist[c] += 1;
        }

        for (auto x : hist) {
            cout << x.first << ": " << string(x.second, '*') << endl;
        }
    }
#endif
#if 1
    cout << "set of custom type" << endl;
    {
        set<S> s;
        s.insert(S(1));
        s.insert(S(1));
        s.insert(S(2));

        // Print set.
        // `auto` in this case is a copy by value, and that is on purpose since copying a struct of
        // small sizes e.g. 4 bytes is faster that taking a reference to it.
        for (auto v : s) {
            cout << v.i << endl;
        }
    }
#endif
}
