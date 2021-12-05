# Lab 8: Polymorphic clones (Inheritance and Containers)

## Homework Macroprocessor questions?

* Your solution has to return error code 0 (i.e. no error) even if there is an error.
    Otherwise, the judging process is skipped and the test fails.

* code review:
    I have to look at your submissions, so please make it pretty.
    I don't want to take away points so I will post some comments in Recodex and you'll have a week or so to fix them.
    If you won't, then I'll subtract some points based on the severity of the issue.
    Please don't cheat.. I've been told that it is pretty easy to spot when you're reading them all at the same time.

## Clones

**Goal:**
Explore how to make polymorphic copies.
That is, given pointer to base class how to make copy what it is pointing to?

* [clones1](./clones1.cpp)
    - inheritance and method overriding example
    - calling explicit method versions from class predecessors using `this->PredecessorClass::method` (useful mostly only if it is virtual otherwise there is some weird overloading going on)
    - shows usage of `std::unique_ptr` with containers

* [clones2](./clones2.cpp)
    - explores what constructors are called during move operations on `std::unique_ptr`
    - it is shown that the only called constructor are the base one (to construct the object) and then a destructor when unique_ptr falls out of scope
    - no move / move assignment constructors are called
    - notice that during the calls to functions taking (moved parameter `bar` and `baz`) no move constructor is invoked since no construction is done in this case
    - if we were to store the moved value in some other place only then it will invoke the ctor try this with your custom method and these print versions of constructors
    - notice that after we move away from the container the container is empty, due to implementation of `std::vector` move assignment ctor

* [clones3](./clones3.cpp)
    - since no ctors are called (apart them the initial constructing one) we have to utilize something else -> virtual methods
    - the core of cloning is this function declaration in the base class:
    ``` c++
    virtual std::unique_ptr<Base> clone() = 0;
    ```
    - note the required forward declarations in this example (https://stackoverflow.com/questions/553682/when-can-i-use-a-forward-declaration)
    - notice that `struct C` is recursive you can create n-ary tree structure with this declaration and then with recursive `clone` call copy it exactly as is

    > hint1: You can't use this 
    > ```c++
    > C copy = *this;
    > ```
    > as in other `clone` implementations.
    > `this` is a pointer to given instance of class you are in i.e. in this case `C *`, therefore if we do `*this` (deferecence pointer to C thus get reference to it `C &`) we attempt to copy a non-copyable object.
    > `struct C` contains a non-copyable object `std::vector<std::unique_ptr>>` thus C is not copyable.

    > hint2: To create copy of C utilize TODO 1

### Design patterns utilizing clones

* Prototype
* Generator

## Next 3 times:

1. Exceptions
2. Standard library: I/O, time measurements, randomness...
3. Templates
