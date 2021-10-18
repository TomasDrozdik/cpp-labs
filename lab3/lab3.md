# Lab 3 - Memory and Types (15.10.2021)

## Note on CMake from CLI and how this project looks

``` bash
git clone <cmake_repo>
cd <cmake_repo>
mkdir build
cd build
cmake ..
make

# Given your binaries was added in <cmake_repo/labX/CMakeLists.txt as add_executable(exe foo.cpp)
# you can call:
./labX/exe

# Or given it supports Ctest you can call the tests with `gtest_discover_tests(test_exe)`
# you can call:
ctest
```

## Note on `namespace` and `using namespace`

* Do not use `using namespace` in header files, that will polute namespace.

* You may use `using namespace` in `.cpp` files once you know that there are no collisions otherwise the compiler will yell at you.

* Global namespace is reffered to as `::`.

* `std` is a namespace for the standard template library.

* Do not hide main inside of a namespace, compiler will not be able to find it.

## Memory structure

1. CPU Registers
2. Caches
3. (Main) Memory or RAM
4. (Block) devices (disks, SSDs, network card, mouse...)

### Memory layout - magic of virtual addressing

<https://www.geeksforgeeks.org/memory-layout-of-c-program/>

1. Text
2. Initialized global (static) data
3. Uninitialized global (static) data or BSS
4. Heap
5. Stack
6. Environment

> `size` to show size of an object file/binary/executable

> To explore stack at runtime view "CallStack" / "StackTrace" in your debuger.

> Exploring heap is more difficult.
> You can use memory profiler to see what lines of code allocate memory.
> Or add debug information to your allocator (will be explored later).
> Or use dynamic profiling tools like `valgrind` to explore how your program works with its heap. (will be used later).

### *Advanced* Memory hierarchy and performance *(skipped)*

<https://gist.github.com/hellerbarde/2843375>

The memory layout lives inside of virtual address space of a given process.
The parts of this address space (text, heap, stack...) live inside of memory "pages" provided by the operating system.

Actual data from this address space needs to get from memory through the cache hierarchy to the register in order to be used (*LOAD*) by the CPU.
During this time the data (pointed to by given virtual address pointer) is "duplicated" and lives inside of the hierarchy on each level.

If the CPU changes the data (it is not `const`) it has to do a *STORE* the data.
Firt it stores it just the the top level cache (L1 cache).
If you don't modify this memory anytime soon it will be evicted from the L1 and need to be stored to (consistently updated) in L2, L3 all the way up to main memory and potenially paged out pages in swap space...

Above paragraph meant to illustrate that *LOAD*s and *STORE*s are expensive operations and you want to work with the data that you already have in your registers/top level cache in order to get the best performance.

In programming that means you pack the data you use for particular part of the computation closely together adhering to a *Locality* principle.

> To view your memory hierarchy on UNIX use `lstopo`.

-------

## C++ Types

*From Lecture:*
> Preference for value types
> * Similar to old languages, unlike any modern language
> * Objects are often manipulated by copying/moving instead of sharing references to them
> * No implicit requirement for dynamic allocation
> * No garbage collector
> * Approximated by smart pointers since C++11
> * Safety still dependent on programmer's discipline

[Fundemental C++ types](https://en.cppreference.com/w/cpp/language/types)

**Task: do an (educative) guess of what is the output of `sizeof` i.e. size of given type in Bytes**
``` c++
sizeof(bool);
sizeof(char);
sizeof(int);
sizeof(int32_t);
sizeof(long);
sizeof(long long);
sizeof(uint64_t);
sizeof(std::size_t);

struct Foo {
    std::size_t x;
};

sizeof(Foo);

struct Bar {
    uint32_t a;
    bool b;
};

sizeof(Bar);

struct Baz {
    bool b;
    uint32_t a;
};

sizeof(Baz);

struct Com {
    uint32_t a[10];
};

sizeof(Com);
```

*[solution](./sizeof.cpp)*

### How to read C types? *(skipped)*

[~~Right to left~~ - Clockwise spiral rule from an identifier](https://riptutorial.com/c/example/18833/using-the-right-left-or-spiral-rule-to-decipher-c-declaration)

``` c++
int aa[][];
int (*pa)[];
int *aap[][];

int (*pf)();
int **fpp();
```

### References `&` `&&`

* lvalue reference `&`
* rvalue reference `&&` (will be discussed next time)
* forward reference `auto &&` (even more later)

### `const` modifier

**Task: decide whether line with `// ?` is an error?**
``` c++
// Basic types
const int a;
const int a[3] = {1, 2, 3};

// Basic objects
struct Foo {
  int i;
  const int j; // ? - tricky one

  void bar();

  void baz() const; // object method `const` modifier
};

// Declaration and Initialization
Foo foo{};
const Foo const_foo{}; // without {} it does not work, why?

void foobaz(const Foo f) {
  f.bar(); // ?
  f.baz(); // ?
}

void foobar(Foo f) {
  f.baz(); // ?
  f.j = 5; // ?
}

void cref(const Foo & f);
void ref(Foo & f);

int task_constness() {
  const_foo.bar(); // ?
  const_foo.baz(); // ?
  const_foo.i = 1; // ?
  const_foo.j == 42; // ?

  foobar(foo); // ?
  foobar(const_foo); // ?

  foobaz(foo); // ?
  foobaz(const_foo); // ?

  ref(foo); // ?
  ref(const_foo); // ?

  cref(foo); // ?
  cref(const_foo); // ?
}


#include <iostream>
void Foo::bar() {
  std::cout << j; // ?
}

void Foo::baz() const { // notice the const at the end without it this is invalid!
  i = 5; // ?
}

// Pointers
int * p_int;
int *is_pointer_to_int, not_a_pointer_int;
int * is_pointer_to_int1, * is_pointer_to_int2;

int const * pointer_const_int; // east notation
const int * wpointer_const_int; // west notation

int * const const_pointer_to_int;
int const * const const_pointer_const_int; // east notation
const int * const wconst_pointer_const_int; // west notation

void pointer_test() {
    int i;
    int const ci; // east notation

    int * p1 = &ci; // ?
    int * const p2 = &ci; // ?
    int * const p3 = &i; // ?
    const int * p4 = &i; // ?
    int const * const p5 = &i; // ?
}
```

*solution - compile this code and see*

> `const` is part of the type!
> That holds for methods as well!

### `auto`

[C++ weekly episode on `auto`](https://www.youtube.com/watch?v=tn69TCMdYbQ&ab_channel=C%E1%90%A9%E1%90%A9WeeklyWithJasonTurner)

Rules for auto:
1. `auto` never deduces reference, unless you specify `&` explicitely
2. `auto` always deduces constness for reference and pointer types
3. otherwise it makes a copy

**Task: what type does `auto` deduce?**
``` c++
{
    int x = 0;
    auto a = x; // ?
    auto & ar = x; // ?
}
{
    const int x = 1;
    auto a = x; // ?
    auto & ar = x; // ?
    const auto & car = x; // ?
}
{
    int const * x = nullptr;
    auto a = x; // ?
    auto & ar = x; // ?
}
```

[*soulution*](./auto.cpp)

### Allocators available in C++

1. Stack allocation
  * local variables
  * distinguish object declaration and initialization

2. Heap allocation
  * C interfaces: `#include <stdlib.h>`
    * `std::malloc`
    * `std::free`
  * `operator new`
    * `new` `delete`
    * `new[]` `delete[]`
    * placement new
  * `make_unique<T>` `make_shared<T>` smart pointers factories
    * internally uses `operator new` for heap allocation
    * arguments match to `T` constructors

## Task: Write your own Allocator

> Heap profiling: [`valgrind`](https://www.valgrind.org/)

1. First try these invalid operations and check them with `valgrind`: *(homework)*
  * don't free allocated memory
  * loose reference to an allocated pointer
  * double free

  ```
  valgrind a.out
  ```

2. Look at the [the allocator interface](./allocator.h).

    You see that is has statically defined memory of fixed size.
    You are supposed to use this memory to make allocations.
    Write simple tests that match your expectation of how should such allocator behave.
    For now allocate will return `nullptr` if it is not able to allocate memory.

3. Implement [the allocator interface](./allocator.h) custom allocator of integers. Possible options: *(explained .1 and .2, code next time)*
    1. *Bump pointer*

        Do not implement `deallocate` just bump the pointer untill possible and once the space is up the program can get no more memory.

    2. *Stack allocator*

        Similar to bump pointer but this time we allow to deallocate the last element.
        If there is a request to deallocate some other than last allocated element just leave it be.

    3. [*Free list*](https://en.wikipedia.org/wiki/Free_list) *(next time)*

        Clever implementation of linked list using empty places as singly linked list of pointers to utilize used space.
        It is a fundamental building block of [Slab allocator](https://en.wikipedia.org/wiki/Slab_allocation)

    4. *Bitmap* *(next time)*

        Use `vector<bool> map` as bitmap where block at index `idx` is used (allocated) iff `map[idx] == true`.
        That means that in order to allocate *n* ints you have to search for n consecutive `false` bools in the array.
        Feel free to do a dumb version.

> This allocator exercise is based on talk [CppCon 2015: Andrei Alexandrescu “std::allocator...”](https://www.youtube.com/watch?v=LIb3L4vKZ7U&ab_channel=CppCon)