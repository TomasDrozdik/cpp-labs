 # Constructors and Rules of *n*

> [cppreference: The rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three)

> Beware of declaration of [copy assignment operator](https://en.cppreference.com/w/cpp/language/copy_assignment). Copy and swap idiom.


## Tasks on Constructors:

1. Implement Rule of 3 for our `Allocator`:
    0. Destructor
    1. Default constructor
    2. Copy contructor
    3. Copy assignment operator

2. Implement Rule of 5
    0. Destructor
    1. Default constructor
    2. Copy contructor
    3. Copy assignment operator
    4. Move contructor
    5. Move assignment operator

[example on ctors and their usage: ctors.cpp](./ctors.cpp)
[solution allocator.h](./allocator.h)

---

### Notes on copy and move operations

Everything about copies and moves has to deal with the way constructors are written.
Beware of default

C++ Keywords: [cppreference: Keywords](https://en.cppreference.com/w/cpp/keyword)
* `explicit` - try to use always for constructors with a single parameter, implicit conversion is default!!
* `= delete` - causes loooong error messages, just scroll to the bottom and search for what is not defined and from where it is required..
* `noexcept` - will be discussed later

[How compiler implicitely declares constructors for you?](https://safecpp.com/RuleOfDesDeMovA.html)

Remember that the type system of C++ is one big lego structure and the compiler has to have all the pieces.
Constructors are probably the most important adapting blocks that allow you to call functions, even those that don't exactly match the type of your variable.

---


## Tasks on function overloading, operator overloading and conversions:

> [cppreference: Operator overloading](https://en.cppreference.com/w/cpp/language/operators)

> [cppreference: Expressions](https://en.cppreference.com/w/cpp/language/expressions)
> Pay particular attention to different types of casts.

1. Oveload `new` and `delete` operators globally so that they use your `Allocator`.

2. Implement a conversion from one type of allocator to another e.g. from `Freelist` to `Bitmap` or vice versa.
