# Lab A: Writing your own containers - Non-Contiguous Vector

## Non-Contiguous Vector

* `std::vector` does not preserve location of the elements
    * changes in the vector => invalidation of references, iterators...

**What do we want?**
* data structure that preserves the location of its elements
* no reference/iterator invalidation
* constant access time to an element

**What we are willing to sacrifice?**
* contiguous data

### Interface

* reserve / resize

* push_back

* subscript operator / at

* iterator
    * begin, end
    * operator++, prefix / postfix
    * operator !=
    * const?

* copy?, move?

* clear

### Task 1 : Write declarations for `struct ncvec`

* templates?

> Templates at this stage are pretty simple, essentially what it does is simple replace of every templated parameter e.g. `T` in the given scope of a structure e.g. `ncvec` with the passed value.
> For example if you did `ncvec<int>` the code looks the same as if you did Find&Replace of `T` for `int`.
> However, all templated code NEEDS to be in the header files i.e. you cannot split your declarations to `*.h` and definitions to `*.cpp`.

* constructors?

> We suffice with defaults, however since we internally use `std::unique_ptr` we might explicitly delete copy ctors.

* const + overloading?

> This is bit of a pain, you need to implement the same methods repeatedly.

* `using` type declarations?

> Look at the [cppreference for vector](https://en.cppreference.com/w/cpp/container/vector) and check the member types section.
> It means that in `std::vector` there is something like this: `using value_type = T;`

**Hint: Reuse your code**
Try to reuse the functions you've already implemented as much as possible.
Think in terms of semantics of the object you are implementing!
For example, this vector needs resizing if your current size reaches capacity.

For this you may use private helper functions to avoid code duplication.

**Hint: Avoid creating properties for things you can cheaply compute**
For example, you know the number of allocated blocks from the underlying vector.
Try to be minimalistic in your properties and if some are computable from others create functions for them.
Of course, if something is difficult to compute, make an exception.

### Task 2 : Start simple! Implement `reserve` and `capacity`

> Q: What happens when reserving less than current capacity?
> A: Just return and don't shrink space.

### Task 3 : Continue simple! Implement `push_back`, `size`, and `operator[]`

> Think about what functions could simplify your life e.g. look at the `push_block(std::size_t block_count)` private helper function.

### Task 4 : Test!

### Task 5 : Write declarations for `struct iterator`

> You need methods mentioned below or check what different types of iterator there are [on cppreference](https://en.cppreference.com/w/cpp/iterator)

### Task 6 : Start simple! Implement constructor and `ncvec::begin` and `ncvec::end`

### Task 7 : Implement `operator!=`

> Thinking in terms of negative logic is hard and counterintuitive.
> For this reason it may be a good idea to first implement `operator==` and then just negate it.
> Event though the `operator==` is not required by the iterator interface it is a good practice to add it.

### Task 8 : Implement `operator*` and `operator->`

> `operator->` has somewhat weird syntax, check out the comment in the source code.

### Task 9 : Implement `operator++` prefix/postfix variant

> Here you can see what is the difference between prefix and postfix variant.
> However, don't feel obliged to implement it this way, it is your code and you can do it the way you need/want to...

### Task 10 : How would you implement `cbegin` and `cend`?

> You could use templates or just implement a new struct with const method variants, the later option has a lot of code duplication though.

### Task 11 : Use an algorithm to accumulate your vector

### Task 12 : Modify your container and verify that the iterators are still valid


## Next time: standard library
