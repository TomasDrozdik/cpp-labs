# Lab1 - Introducing C++ (1.10.2021)

1. Introduction, for basic information view [README](../README.md) highlights:
    * Mattermost channel for our lab only with name *nprg041-cpp-drozdik*, if you don't see it use `Find channel` in `2122ZS` "group" on the left (marked by a snowflake).

    * All materials will be pushed here in this form.

    * If you don't understand something e.g. weird syntax, code diverges even slightly form your expectation... please open a thread in our channel (just write a message), include code snippets that confuse you using [markdown syntax](https://www.markdownguide.org/basic-syntax/) and I or your classmates will try to help you.

    * Don't be embarassed or anything, no question is stupid, we all just want to learn something new, mistakes and missunderstandings are part of it.

    * If you want to try to find out the answers yourself - figure out syntax or library interface use one of the provided cpp reference pages e.g. [cppreference](https://en.cppreference.com/w/).

    * If you don't understand what the reference is trying to say ask in the channel, post a link, include a screenshot..

    * Lab activity is tracked by contributions to GitLab. By the next lab try access to it and post your work from the lab if you've been there or try something at home and post it there as well.

2. Lab structure
    * Before each lab (hopefully sufficiently in advance) I'll prepare some tasks for the next lab.

    * I'll give you some time to try them out and then we will try to create some solution together and I'll try to do some explanations in between.

## Tasks

### 1. Hello world - output and command-line arguments

1. Write a program that prints `Hello world!`.

2. Say hello to an argument from command line.

3. Say hello to all arguments from command line.

### 2. Simple constructs

1. Write a function that reads 2 integers form stdin and prints them out.

2. Write a function that computes rectangle area given that numbers read in (1) are sides of the rectangle.

3. Write euclidian algorithm (Greatest Common Divisor) of these two numbers.

### 3. Bubblesort

1. Create a `std::vector` from interval [10..-10], use `push_back` and `for`.

2. Write a function that swaps two integers (play with pointers).
    ``` c++
    void swap(int * a, int * b)
    ```

3. Sort the vector from (1) using (2) and bubblesort function.
    ``` c++
    void bsort(std::vector<int> &vec)
    ```

## Solution

Solution is in [lab1.cpp](lab1.cpp).

> Note I've found issue with preprocessor macros that alter code. Change `#if 0` to `#if 1` to enable particullar block of code - from `#if` to `#endif`.

**Compile:**
* on UNIX/Linux/in rotunda lab using [g++](https://en.wikipedia.org/wiki/GNU_Compiler_Collection) or [clang++](https://en.wikipedia.org/wiki/Clang).
    ``` bash
    g++ lab1.cpp --output executable
    ```

* on Windows use VisualStudio / VisualStudioCode with integrated compiler [MSVC](https://en.wikipedia.org/wiki/Microsoft_Visual_C%2B%2B) and use buttons to compile and run the code. However the compiler in ReCodex uses unix variant and they tend to be a bit more strict. For that reason I advice you to setup unix environment on Windows using [Windows Subsystem for Linux 2](https://docs.microsoft.com/en-us/windows/wsl/). And then it can be connected to your IDE e.g. VSCode.

**Run:**
```
# In case you compiled with `--output executable` (or -o)
./executable <argument_1> <argument_2> ...

# If `--output` was ommited then the binary has default name `a.out`
./a.out <arg_1> <arg_2> ...

# If the executable is not runable run
chmod +x ./executable
```

If your setup does not work write to our group chat, me or others might help.
