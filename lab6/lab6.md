# Lab 6: Containers and Iterators

## Git upstream workflow

```
# Clone a repo or init a new one
$ git clone <url>                        # <url> is named as remote origin by default
$ git remote show
$ git remote show origin 

# Add new remote
$ git remote add upstream <my_lab_url>   # adds new remote location - upstream, can be named differently
$ git fetch upstream                     # fetches from this repository
$ git merge upstream/master              # merges master branch from upstream to your master

# Work with the original remote - origin
$ git push origin                        # pushes to your repo that you've cloned initially
```

## From last time: Tasks on function overloading, operator overloading and conversions:

> [cppreference: Operator overloading](https://en.cppreference.com/w/cpp/language/operators)

> [cppreference: Expressions](https://en.cppreference.com/w/cpp/language/expressions)
> Pay particular attention to different types of casts.

1. Overload `new` and `delete` operators globally so that they use your `Allocator`.

2. Implement conversion from one type of allocator to another e.g. from `Freelist` to `Bitmap` or vice versa.

> Beware of `const_cast`! [const_cast.cpp](./const_cast.cpp)

3. Look at all the operators the C++ has and allows you to override, imagine what kinds of different and unique overloads - multiple parameters, `const`, `&`, `&&`... Try to implement something that makes sense for your `Allocator`.

4. Now think why task#3 was a bad idea?

## Containers or Introduction to templates

[cppreference: Containers](https://en.cppreference.com/w/cpp/container)

Look at adaptors.

## Vector, Arrays, and their iterators

Look at [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector) what is a type of an iterator?

### Task: Define functions with following declarations

``` c++
#include <vector>

print(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end);

template<typename ConstIterator>
print(ConstIterator begin, ConstIterator end);

bubblesort(std::vector<int>::iterator begin, std::vector<int>::iterator end);

template<typename T>
bubblesort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end);

template<typename Iterator>
bubblesort(Iterator begin, Iterator end);

// Reverse print the vector using templated print.
```

Note that `std::sort` function from `https://en.cppreference.com/w/cpp/algorithm/sort` has declaration
``` c++
template< class RandomIt >
void sort( RandomIt first, RandomIt last );
```
There is only difference in name of template parameter (`class` and `typename` are effectively same).
Additionaly name is arbitrary, therefore this function declaration is the same as our `bubblesort`.

However as noted during the labs when an argument type is templated compiler tries to use that argument in the given function body and each operation on it has to be supported otherwise it throws a loooong error message with lots of suggestions (called notes) on what is and isn't implemented.

For this reason the reference states the type requirements i.e. what is done on that type in the given function, if your `typename` (or `class`) template parameter fulfills these conditions you can use your own type using sort.

> [From cppreference on std::sort](https://en.cppreference.com/w/cpp/algorithm/sort):
> Type requirements
> -RandomIt must meet the requirements of ValueSwappable and LegacyRandomAccessIterator.
> -The type of dereferenced RandomIt must meet the requirements of MoveAssignable and MoveConstructible.

Beware of iterator invalidation! (look it up in previous link on containers)

## Maps and Sets

Ordered versions use `operator<`.

Unordered use hash and key_equal functors - will be discussed in the next lab.

### Task: Histogram

Create a histogram of characters read from input.
Print it out.

Read input as such:
``` c++
char c;
while (cin >> c) { // once input ends cin >> c returns istream and istream that ended evaluated to false...
    // use read char or int or whatever you've passed to cin
}
```

### Task: Creating (ordered) maps and sets

Create your `struct S` with some data properties.
You need to implement your own comparator (`operator<`) since `std::set` is ordered!

Try print the struct using `operator<<` can we place it inside of `S`?

### Task: So what if I don't need order?

Create a `std::unordered_set<S>`

View template arguments:
```c++
template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator< std::pair<const Key, T> >
> class unordered_map;
```

> Beware! If hashes of 2 keys equal elements have to equal as well otherwise it just does not work.
