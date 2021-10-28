# Lab 4 - Allocators, Polymorphism

## Polymorphism

Similar to Java and C hashtag.

### Private polymorphism

*"With private inheritance, public and protected member of the base class become private members of the derived class. That means the methods of the base class do not become the public interface of the derived object. However, they can be used inside the member functions of the derived class."*

### Virtual descructor and Undefined Behavior (UB) ..and possible memory leaks

Try [./virtual_descructor.cpp](./virtual_descructor.cpp) with and without virtual destructor of the base class.

It generaly causes memory leaks -> try `valgrind`.


### Multiple inheritance

Carefull for diamond inheritance i.e. you are free to derive from single non-abstract class and then as many abstract classes as you want.
Think of it as single inheritance in Java but you can still implement multiple interfaces:
``` Java
public static class JavaDerivedClass extends Base implements IFace1, IFace2 {}
```
C++ analogy of an abstract class is purely virtual class.
See examples of virtual and purely virtual methods in [allocator.h](./allocator.h).


## Task Allocator

[Gitlab Pipeline](https://gitlab.mff.cuni.cz/teaching/nprg041/drozdik/labs/-/jobs/107059) is failing, lets find out why and fix it!

### Notes on unit tests in [allocator tests](../test/test_lab4.cpp)

[Fixtures](https://google.github.io/googletest/primer.html#same-data-multiple-tests) and [unit test parametrization](https://google.github.io/googletest/advanced.html#value-parameterized-tests).

---

> Code sharing with [VSCode Live Share extension](https://code.visualstudio.com/learn/collaboration/live-share) or just come to the desk :-)
> *Supposedly up to 30 participants so lets check it out*

1. Allocator interface and unit tests *(done)*
    Write unit tests for [allocator.h](./allocator.h) interface.

2. Implement [the allocator.h interface](./allocator.h) - custom allocator of integers. Possible options:
    1. Bump pointer *(done)*

        Do not implement `deallocate` just bump the pointer untill possible and once the space is up the program can get no more memory.

    2. Stack allocator

        Similar to bump pointer but this time we allow to deallocate the last element.
        If there is a request to deallocate some other than last allocated element just leave it be.

    3. [Free list](https://en.wikipedia.org/wiki/Free_list)

        Clever implementation of linked list using empty places as singly linked list of pointers to utilize used space.
        It is a fundamental building block of [Slab allocator](https://en.wikipedia.org/wiki/Slab_allocation)

    4. Bitmap

        Use `vector<bool> map` as bitmap where block at index `idx` is used (allocated) iff `map[idx] == true`.
        That means that in order to allocate *n* ints you have to search for n consecutive `false` bools in the array.
        Feel free to do a dumb version.

## *(Voluntary)* Mini Homework (or just additional tasks)

1. Are the unit tests good? Think of a simple Allocator subclass that does pass all of the original tests but it it is obviously wrong.

2. Implement better tests ;-)

> Try to submit a Merge Requests to my repo with your better test version from your fork of it or just your branch with 2 remote origins.
> I'll review your MR and include them in my repo.
