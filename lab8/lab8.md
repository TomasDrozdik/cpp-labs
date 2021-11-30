# Lab 8: Functors & Lambdas

## Homework Macroprocessor questions?

## Homework CoutingSheeps summary

> Sorry, this task sucks :-(

* **Beware of pass by value** of big objects! It is only OK to pass small values (couple of bytes ~16) by value, otherwise use `const & T`
    ```c++
    // Bad
    void foo(std::string input);

    // Good
    void foo(const std::string & input);
    ```

*   ```c++
    switch (expression) {
    case x:
        // code block
        break;
    case y:
        // code block
        break;
    default:
        // code block
    }
    ```

* use `enum class` instead of `enum`
    ```c++
    enum class Color { red, green = 20, blue };
    Color r = Color::blue;
    switch(r)
    {
        case Color::red  : std::cout << "red\n";   break;
        case Color::green: std::cout << "green\n"; break;
        case Color::blue : std::cout << "blue\n";  break;
    }
    // int n = r; // error: no implicit conversion from scoped enum to int
    int n = static_cast<int>(r); // OK, n = 21 <- still don't do this
    ```

* but for flags:
    ```c++
    enum Flags
    {
        A = 1 << 0, // binary 0001
        B = 1 << 1, // binary 0010
        C = 1 << 2, // binary 0100
        D = 1 << 3  // binary 1000
    };

    Flags f = A | B | C;
    ```

* use `std::array<T, n>` instead of `T[n]` because it allows you to access array functions and iterators thus unlocking all algorithms

*   ```c++
    string input;
    while (cin.get(c)) {
        input += c;
    }

    std::string s(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
    ```

* use structures instead of magic constants
    ```c++
    const char* output[6]{ "znaku: " , "slov: ", "vet: ", "radku: ", "cisel: ", "soucet: " };
    cout << output[5] << counter.getsum() << endl;
    ```
    For constants prefer using global (or scoped in a `class`) `static constexpr T var;`
 
* streams are polymorphic thus you can use generic `std::istream` for both `std::cin` and `std::ifstream` but we'll get to streams and I/O later

*   ```c++
    friend std::ostream& operator<<(std::ostream&, const Counter&);
    ```

* English! Pretty please :-)
    ```c++
    // slovo: nejdel?? posloupnost alfanumerick?ch (isalnum) znak? neza??naj?c? ??slic? (isdigit)
    ```

## Algorithms + functors + `std::function`

**From last time:** Predicates, functions, and comparators:
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

Example usage was:
```c++
bool even(int a) { return a % 2 == 0; }

{
    auto it = find_if(v.cbegin(), v.cend(), &even);
}
```

### Task: How about using Functors instead of function pointers?

Count number of elements bigger than given number.

1. Using `std::accumulate`
2. Using functor + `std::for_each`


## Lambdas [cppreference](https://en.cppreference.com/w/cpp/language/lambda)

```c++
[ capture ]( params ) mutable -> rettype { body }

class ftor {
public:
    ftor( TList ... plist) : vlist( plist) ... { }
    rettype operator()( params ) const { body }

private:
    TList ... vlist;
};
```

`TList` and `vlist` refer to params from `capture`.

### Return type:
* can be automatically deduced from the body's `return` statement, or
* explicitly specified using `->` or
* `void` if there is no return value

### Captures!

You can capture local variables and `this`.

```c++
struct S {
    int a;
    std::string s;

    void foo() {
        auto f = [this, a, &s](char c) -> void { body };
    }
}
```

Explicit captures:
* by value `[=]`
* by reference `[&]`
* can be combined e.g. `[=, &i]` or `[&, i]`

Beware of dangling references!

### Task: use algorithms with lambdas / functors / functions

1. Get container of elements greater than `X` incremented by `Y`.

2. Find first element different from previous one by at least `X`.

3. Increment numbers following pattern: `[first + X, second + 2*X, third + 3*X]`.

4. Get difference of neighbor values.

5. New container of second powers of even and third powers of odd numbers.

## Ranges

This is still pretty cumbersome compared to C# LINQ and Java streams.
That is why C++ 20 has introduced concept of `ranges` see [examples](https://mariusbancila.ro/blog/2019/01/20/cpp-code-samples-before-and-after-ranges/) of how it would look once compilers have support.

Good way to check compiler support across multiple compilers is [Compiler Explorer](https://godbolt.org/z/xrq4Txsbn).

## Next time: unique_ptr and polymorphic clones
