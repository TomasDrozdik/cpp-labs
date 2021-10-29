#include <iostream>

struct S
{
    int * pi;

    explicit S(int * pi)
        : pi(pi)
    {
       std::cout << "S(int *)\n";
    }

    ~S()
    {
       std::cout << "~S()\n";
       delete pi;
    }

    S(const S & other)
    {
        std::cout << "S(const S & other)\n";
        this->pi = new int{*other.pi};
    }

    S & operator=(const S & other)
    {
        std::cout << "S & operator=(const S & other)";
        this->pi = new int{*other.pi};
        return *this;
    }

    S(S && other)
    {
        this->pi = other.pi;
        other.pi = nullptr;
    }

    S & operator=(S && other)
    {
        this->pi = other.pi;
        other.pi = nullptr;
        return *this;
    }

    // Example of how you can use operator overloading in completely bad way. But it is possible, it
    //is just a function with a special name and 2 ways of calling it.
    int operator++()
    {
        return 5;
    }

    // Subscript operator again same as operator++ can return anything, it can also be overloaded..
    // In general these kinds of overloads are bad idea. Since they are just a syntactic sugar
    // replacement for actual method calls most of the time a (properly) named method is better.
    int operator[](int)
    {
        return 5;
    }
};

// This function takes argument of struct S, but since it is not a reference nor a pointer it
// "pass by value" it means that we have to crete copy of passed argument -> use copy ctor.
void foo(S s)
{
    std::cout << "foo(S & s)\n";
}

// This function takes argument of struct S &&, that means that the caller gives up the "ownership"
// of variable s and you are free to do with it what you want.
// Notice that no constructor is invoked. Since no new value is constructed the passed value is just
// "handed over" to this function foo.
void bar(S && s)
{
    std::cout << "bar(S && s)\n";
}

int main(void)
{
    #if 1
    {
        S s{new int{8}};
        S s2{s};
        foo(s2);
        std::cout << "after foo\n"; // is this invoked before or after destruction of s.
    }
    #endif
    #if 1
    {
        std::cout << "\n 0 -------------------\n";

        S s{new int{8}};
        S s2 = s;
        s2 = s2; // Beware of self assignment
        s2.operator=(s2); // Equivalent use
    }
    #endif
    #if 1
    {
        std::cout << "\n 1 -------------------\n";

        S s{new int{8}};
        bar(std::move(s));
        // Beware! Even though s is still in scope it has been "handed over" / "moved" to the foo,
        // That means it should be no longer used in here.
        std::cout << "after foo\n"; // is this invoked before or after destruction of s.
    }
    #endif
    #if 1
    {
        std::cout << "\n 2 -------------------\n";

        S s{new int{8}};
        S s2{std::move(s)};
    }
    #endif
    #if 1
    {
        std::cout << "\n 3 -------------------\n";

        S s{new int{8}};
        S s2{new int{7}};
        s2 = static_cast<S &&>(s); // same as std::move()
    }
    #endif
    #if 1
    {
        std::cout << "\n 4 -------------------\n";

        int i{};
        auto pi = &i;
        //foo(S{pi}); // error is S(int *) is explicit otherwise this is possible and wrong
    }
    #endif
    #if 1
    {
        std::cout << "\n 5 -------------------\n";

        int i{};
        auto pi = &i;
        //foo(S{pi}); // error is S(int *) is explicit otherwise this is possible and wrong
    }
    #endif
}
