#include <iostream>
#include <memory>
#include <vector>

#include "press_enter.h"

struct Base
{
    Base() { std::cout << "Base::Base()" << std::endl; }

    Base(const Base &) { std::cout << "Base::Base(const Base & other)" << std::endl; }

    Base(Base &&) { std::cout << "Base::Base(Base && other)" << std::endl; }

    Base & operator=(const Base &) { std::cout << "Base::operator=(Base & other)" << std::endl; return *this; }

    Base & operator=(const Base &&) { std::cout << "Base::operator=(Base && other)" << std::endl; return *this; }

    virtual ~Base() { std::cout << "Base::~Base()" << std::endl; }
};

struct A : Base
{
    A() { std::cout << "A::A()" << std::endl; }

    A(const A &) { std::cout << "A::A(const A & other)" << std::endl; }

    A(A &&) { std::cout << "A::A(A && other)" << std::endl; }

    A & operator=(const A &) { std::cout << "A::operator=(A & other)" << std::endl; return *this; }

    A & operator=(A &&) { std::cout << "A::operator=(A && other)" << std::endl; return *this; }

    ~A() { std::cout << "A::~A()" << std::endl; }
};

struct B : Base
{
    B() { std::cout << "B::B()" << std::endl; }

    B(const B &) { std::cout << "B::B(const B & other)" << std::endl; }

    B(B &&) { std::cout << "B::B(B && other)" << std::endl; }

    B & operator=(const B &) { std::cout << "B::operator=(B & other)" << std::endl; return *this; }

    B & operator=(B &&) { std::cout << "B::operator=(B && other)" << std::endl; return *this; }

    ~B() { std::cout << "B::~B()" << std::endl; }
};

// How to pass unique_ptr to functions?

// Reference
void foo(const std::unique_ptr<Base> &) { std::cout << "void foo(const std::unique_ptr<Base> & p)" << std::endl; }
void foo2(const Base &) { std::cout << "void foo2(const Base & p)" << std::endl; }

// Move options
void bar(std::unique_ptr<Base>) { std::cout << "void bar(std::unique_ptr<Base> p)" << std::endl; }
void baz(std::unique_ptr<Base> &&) { std::cout << "void baz(std::unique_ptr<Base> && p)" << std::endl; }

int main()
{
    press_enter();

    {
        std::cout << "> unique_ptr" << std::endl;
        std::unique_ptr<Base> p;
        p = std::make_unique<A>();

        // Copy of unique_ptr:
        // std::unique_ptr<Base> copy = p; // uncomment to view error on your compiler
        // Users/tdrozdik/school/cpp-labs/lab9/clones2.cpp:69:31: error: call to implicitly-deleted copy constructor
        // of 'std::unique_ptr<Base>'
        //     std::unique_ptr<Base> copy = p; // uncomment to view error on your compiler
    }

    press_enter();

    {
        std::cout << std::endl << "> foo bar unique_ptr" << std::endl;
        std::unique_ptr<Base> p;
        p = std::make_unique<A>();
        foo(p);
        foo2(*p);
        bar(std::move(p));
    }

    press_enter();

    {
        std::cout << std::endl << "> baz unique_ptr" << std::endl;
        std::unique_ptr<Base> p;
        p = std::make_unique<A>();
        foo(p);
        bar(std::move(p));
    }

    press_enter();

    {
        std::cout << std::endl << "> move of p" << std::endl;
        std::unique_ptr<Base> p;
        p = std::make_unique<A>();

        std::cout << "move" << std::endl;
        std::unique_ptr<Base> p_moved = std::move(p);
    }

    press_enter();

    {
        std::cout << std::endl << "> vector<unique_ptr>" << std::endl;
        std::vector<std::unique_ptr<Base>> container;
        container.push_back(std::make_unique<A>());
        container.push_back(std::make_unique<B>());

        // Copy of vector:
        // std::vector<std::unique_ptr<Base>> copy = container; // uncomment to view error on your compiler
        // Fails on clang 12.0.0 with error:
        // In file included from /Users/tdrozdik/school/cpp-labs/lab9/clones.cpp:1:
        // In file included from /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/iostream:37:
        // In file included from /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/ios:215:
        // In file included from /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/__locale:14:
        // In file included from /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/string:504:
        // In file included from /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/string_view:175:
        // In file included from /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/__string:57:
        // In file included from /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/algorithm:643:
        // /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/memory:1881:31: error: call to
        //       implicitly-deleted copy constructor of 'std::__1::unique_ptr<Base, std::__1::default_delete<Base> >'
        //             ::new((void*)__p) _Up(_VSTD::forward<_Args>(__args)...);
        // ...
        //
        // In short that still refers to the unique_pointer copy but the output is much longer.
    }

    press_enter();

    {
        std::cout << std::endl << "> move of vector<unique_ptr>" << std::endl;
        std::vector<std::unique_ptr<Base>> container;
        container.push_back(std::make_unique<A>());
        container.push_back(std::make_unique<B>());

        std::cout << "move" << std::endl;
        std::vector<std::unique_ptr<Base>> container_moved = std::move(container);
    }

    return 0;
}