# Lab 7: Unordered containers, Functors, and `std::algorithm`

## First Homework: Macroprocessor

```
input:  "text #macroname macro body # next text macroname end"
output: "text  next text  macro body  end"
```

Definition of once macro can contain previously declared macro:
```
input:  "zz #m1 xx # #m2 yy m1 # m2"
output: "zz    yy  xx  "
```

All other characters apart from macro definition and invocation go to `cout`.

Whitespaces around macro definition are preserved on output:
```
ws1macrodefinitionws2  ->  ws1ws2
```

Identificators used in macro names are sequences of `std::alphanum` that begins with `std::alpha`.
For example "2A" is not identificator and sequence "X$B1" identificator X followed by non-alphanum character "$" and identificator "B1".
This is relevant for invalid inputs.

Separators of "#macroname" and "#" are `std::isspace`.
"#" on input after non `std::isspace` character behaves as regular character "#".

Input validation, process input up to first error then provide a (debug) error output.
For example:
* macro definition inside of another definition
* two macro ends after each other
* ...
This is not tested.

The program can't act weirdly even on incorrect input.

## Functors

## Task: So what if I don't need an order?

Create a `std::unordered_set<S>` for your `struct S`.

View template arguments of `unordered_map`:
```c++
template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator< std::pair<const Key, T> >
> class unordered_map;
```

This tells us that we need some `Hash` and some `KeyEqual` class for `Key` type that is `struct S` in our case.
These classes are called Functors because they are "executable" in a sense they overload `operator()`.

To find what a particular function uses search the reference otherwise, the compiler will tell you.
Because, like before, the template type simply has to match all usages of that type in the particular function body.
In this case, it is something like this:
``` c++
operator()(const S & s) const;

operator()(const S & s1, const S & s2) const;
```

> Beware! If hashes of 2 keys equal elements have to equal as well otherwise, it just does not work.

## Task: map inserting

Find 3 ways to insert values into a map.

### Bonus task: template specializing `std::hash` and `std::equal_to`.

In your `cpp` file open namespace `std` and define specializations for your custom type.
Then compiler will use defuault argument present above.
```c++
namespace std
{

struct std::hash<S>
{
    // ... same as hash functor from previous task
};

struct std::equal_to<S>
{
    // ... same as equal functor from previous task
};

}
```

*Solution: [algorithms.cpp](./algorithms.cpp)*.

## Algorithms [*cppreference*](https://en.cppreference.com/w/cpp/algorithm)

```c++
#include <algorithm>
#include <numeric>
```

Min/Max:
``` c++
const T& min(T&, T&, Comp);
const T& max(T&, T&, Comp);

ForwardIt max_element(ForwardIt begin, ForwardIt end);
ForwardIt min_element(ForwardIt begin, ForwardIt end);
```

Predicates, functions, and comparators:
``` c++
// Unary predicate
bool pred(const Type1 &a);
// Binary predicate
bool pred(const Type1 &a, const Type2 &b);
// Unary function
void fun(const Type &a);
// Comparator
bool cmp(const Type1 &a, const Type2 &b);
```

Query containers:
``` c++
InputIt find(InputIt first, InputIt last, const T&);
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p);
it assoc_container.find(const T& key); // map or unordered_map

int count(it first, it last, T&) // actual return type is typename iterator_traits<InputIt>::difference_type which may be e.g. `ptrdiff_t`
int count_if(InputIt first, InputIt last, UnaryPredicate p);

ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value);
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value);

T accumulate(InputIt first, InputIt last, T init, BinaryOperation op);
```

Update containers:
``` c++
void fill(ForwardIt first, ForwardIt last, const T& value);

UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );

void sort(RandomIt first, RandomIt last);
void sort(RandomIt first, RandomIt last, Compare comp);

OutputIt transform(InputIt first1,
                   InputIt last1,
                   OutputIt d_first, // may be equal to first1
                   UnaryOperation unary_op);

// Removes all elements satisfying specific criteria from the range [first, last) and returns a past-the-end iterator for the new end of the range.
// i. e. doesn't remove elements from the container
// 1) Removes all elements that are equal to value, using operator== to compare them.
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value);
// 3) Removes all elements for which predicate p returns true.
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p );

// Eliminates all except the first element from every consecutive group of equivalent elements from the range [first, last) and returns a past-the-end iterator for the new logical end of the range.
// binary predicate that returns ​true if the element should be treated as equal.
ForwardIt unique(ForwardIt first, ForwardIt last);
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p);

// Actual destruction of objects, available from methods on a container (e.g. `vector::erase`):
// Iterator invalidation!!!
iterator container::erase(const_iterator first, const_iterator last);
```

Inserters, an option for output iterators without worrying about capacity:
```c++
back_inserter(container)
front_inserter(container)
inserter(container)
```

> If the capacity is known prior to container insertion use `.reserve(size_t new_capacity)`.

Container creation:
```c++
OutputIt copy(InputIt first, InputIt last, OutputIt d_first);
OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred );
```

### Task algorithms examples

Pick 3 "algorithms" from above and show *example usage*.
Try different containers: arrays, vectors, strings, sets, maps, and their unordered variants.

*Solution: [functors.cpp](./functors.cpp) + examples from cppreference.com*.

## Next time: lambdas
