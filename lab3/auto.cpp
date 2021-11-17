#include <cassert>

void foo(int *) {}
void bar(int const *) {}
void baz(int const * const) {}

int main() {
    {
        int x = 0;
        [[maybe_unused]] auto a = x; // int - copy
        [[maybe_unused]] auto & ar = x; // int &
    }
    {
        const int x = 1;
        [[maybe_unused]] auto a = x; // int - copy
        [[maybe_unused]] auto & ar = x; // const int & - const has to be deduced since the referenced variable cannot change
        [[maybe_unused]] const auto & car = x; // const int & - const is explicitely specified
    }
    {
        int const * x = nullptr;
        [[maybe_unused]] auto a = x; // int const * - copy pointed to value is const -> this is const
        auto & ar = x; // (int const *) & - reference to a pointer to a const int

        // foo(a); error that proves a is pointer to const int thus types are incompatible

        int i;
        ar = &i;
        assert(ar == x);
    }

    return 0;
}
