#include <iostream>
#include <memory>
#include <vector>

#include "press_enter.h"

struct Base
{
    virtual ~Base() = default;

    virtual void foo()
    {
        std::cout << "Base::foo" << std::endl;
    }
};

struct A : Base
{
    virtual void foo() override
    {
        std::cout << "A::foo" << std::endl;
    }
};

struct AA : A
{
    void foo() override
    {
        this->Base::foo();
        this->A::foo();
        std::cout << "AA::foo" << std::endl;
    }
};

struct B : Base
{
    void foo() override
    {
        std::cout << "B::foo" << std::endl;
    }
};

int main()
{
    std::unique_ptr<Base> p{};

    press_enter();

    p = std::make_unique<A>();
    p->foo();

    std::vector<std::unique_ptr<Base>> container{};

    container.push_back(std::move(p));
    container.push_back(std::make_unique<B>());
    container.emplace_back(std::make_unique<AA>());
    container.emplace_back(std::make_unique<Base>());

    press_enter();

    std::cout << std::endl << "Call foo on container elements:" << std::endl;
    for (auto & x : container) {
        x->foo();
        press_enter();
    }
    return 0;
}