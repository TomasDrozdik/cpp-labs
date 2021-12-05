#include <iostream>
#include <memory>
#include <vector>

#include "press_enter.h"

struct Base;
struct A;
struct B;

std::ostream & operator<<(std::ostream & os, const Base &);
std::ostream & operator<<(std::ostream & os, const A &);
std::ostream & operator<<(std::ostream & os, const B &);

struct Base
{
    virtual ~Base() = default;

    virtual std::unique_ptr<Base> clone() = 0;

    virtual void print()
    {
        std::cout << *this << std::endl;
    }
};

struct A : Base
{
    std::string s = "orig";

    virtual std::unique_ptr<Base> clone() override
    {
        A copy = *this;
        std::unique_ptr<A> p = std::make_unique<A>(copy);
        return p;
    }

    virtual void print() override
    {
        std::cout << *this << std::endl;
    }
};

struct B : Base
{
    std::size_t n = 73;

    virtual std::unique_ptr<Base> clone() override
    {
        B copy = *this;
        std::unique_ptr<B> p = std::make_unique<B>(copy);
        return p;
    }

    virtual void print() override
    {
        std::cout << *this << std::endl;
    }
};


std::ostream & operator<<(std::ostream & os, const Base &)
{
    return os << "Base()";
}

std::ostream & operator<<(std::ostream & os, const A & a)
{
    return os << "A(s=\"" << a.s << "\")";
}

std::ostream & operator<<(std::ostream & os, const B & b)
{
    return os << "B(s=" << b.n << ")";
}

int main()
{
    {
        std::unique_ptr<Base> p;

        p = std::make_unique<A>();

        press_enter();
        std::cout << *p << std::endl;

        press_enter();
        p->print();

        // Don't do this, but just in case..
        dynamic_cast<A&>(*p).s = "new";

        press_enter();
        p->print();
    }

    {
        // TODO 1:
        // 1. create a vector of polymorphic pointers
        // 2. create a clone of it
    }

    {
        // TODO 2:
        // 1. Add this class and implement TODOs
        //
        // struct C : Base
        // {
        //     std::vector<std::unique_ptr<Base>> container;
        //
        //     virtual std::unique_ptr<Base> clone() override
        //     {
        //         // TODO
        //     }
        //
        //     virtual void print() override
        //     {
        //         // TODO
        //     }
        // };
        //
        // std::ostream & operator<<(std::ostream & os, const C &)
        // {
        //     // TODO
        // }
        //
        // 2. Don't forget to add forward declarations for both struct and operator<<.
    }

    return 0;
}
