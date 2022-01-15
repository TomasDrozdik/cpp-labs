# LabC : Templates and types and a little bit of Game Engine


## Game Engine Object Design

*World* has a static *Map* and *Objects* that can interact with each other.
*Object* can be of multiple things: *Player*, *NPC*, *Item*...
Given *NPC* e.g. *Zombie* can have multiple ways of how it behaves - *Strategy*, this executes some *Actions* in the *World*'s other *Objects*.

Then the game loop works as follows:
```
while True:
    display(world)
    actions = []
    foreach object in World:
        actions += prepareAction(object, world)
    foreach action in actions:
        action.execute()
    sleep
```

*Challenges:*

* In world of objects object can ask whether there is another object in front of it, how to determine whether I want to interact with it and how would I do that?

* Efficient ways of querying the world for surrounding objects -> fairly complex grid maps data structures.

* Handling frame rate in the game loop, how long should the sleep be?


## Templates

**Basic templates:**
*Source*: [templates.cpp](./templates.cpp)

> Try them out at [cppinsights.io](https://cppinsights.io/).

**(Compile time) Type programming:**
*Source*: [type_programming.cpp](./type_programming.cpp)

**Compile time programming:**

> Check using [compiler_explorer](https://godbolt.org/)

* `constexpr` can be evaluated both at compile and run time
    * support for `constexpr functions
    * support for `if constexpr`

* `consteval` (C++20) only viable in compile-time

*Source*: [compile_time.cpp](./compile_time.cpp)

## Type deduction

*Q: What is a lvalue?*

*Q: What rvalues and lvalues are here?*
``` c++
void foo(int && param)

foo(10)
```

*Argument* is what you pass in.
*Param* is what you have available in the function scope.
Types of *Param* and *Argument* may differ.

Take following case:
``` c++
template<typename T>
void foo(PARAM p);

int bar()
{
    EXPR expr;
    foo(expr);
}
```

There are 3 important types  in this example:
* `T` - type in the template
* `PARAM` type of the *parameter*
* `EXPR` type of the expression - *argument* that you pass to `foo`

types **types** *x* **references&pointers** *x* **const**

For example:
```c++
template<typename T> 
void foo(const T & p);

int bar()
{
    int i;
    foo(i);
}
```

Here:
* `EXPR` is `int`
* `T` is `int`
* `ParamType` is `const int &`


Distinguish these 3 cases:
1. If `PARAM` is a **reference** or a **pointer** but not **universal reference**
    1. If `EXPR` is reference ignore the reference part
    2. Pattern match `EXPR` against `PARAM` type and determine `T`

2. If `PARAM` is **universal reference**
    ``` c++
    template<typename T>
    void foo(T && param); // same syntax as rvalue reference but it is different, behaves nicely
    ```
    1. If `EXPR` is an lvalue both `T` and `PARAM` are deduced to be lvalue references.
    2. If `EXPR` is an rvalue case 1. applies i.e. simple non-universal (rvalue) reference


3. If `PARAM` is neither pointer nor reference
    1. As before, if `EXPR` is referece ignore the reference part.
    2. If `EXPR` is `const` ignore that too.


### `auto` type deduction

Almost the same as "template type deduction" above using following concept:

``` c++
auto x = expr;

template<typename T>
void func_for_x(PARAM x);
```

For example:
``` c++
const auto & x = 27;

// What is the type of x?
// Use template deduction in following case
template<typename T>
void func_for_x(const T & param);
```

### Special cases:

* `auto` with initializer list

* c-array pointers and function pointers

* braced expressions for `decltype(auto)`


### How to get the type of a variable?

1. From IDE: Let your editor tell you (erroneous)
2. Runtime: Use std::typeid (sometimes erroneous) or boost (external)
3. Compile time: using *deliberate* compiler error m

```c++
template<typename T>
class TD;

void foo()
{
    TD<decltype(expr)> x;
    // Throws something like:
    // error: type ... has incomplete type and cannot be defined
}
```

## Sources:

1. [cppcon: Back to Basics Templates (part 1)](https://www.youtube.com/watch?v=VNJ4wiuxJM4&ab_channel=CppCon)
2. [cppcon: Back to Basics Templates (part 2)](https://www.youtube.com/watch?v=0dtjDTEE0hQ&t=8s&ab_channel=CppCon)
3. [cppcon: Back to Basics const and constexpr](https://www.youtube.com/watch?v=tA6LbPyYdco&t=3114s&ab_channel=CppCon)
4. Effective Modern C++, Scott Meyers, Chapter 1
