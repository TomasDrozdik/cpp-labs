# Lab 2 Building C++ projects

## Tasks

### Manual builds

1. Create `main.cpp`, `foo.cpp` and `foo.h`, one with main. Don't include any library just alter the return value of main from a function in the other file.
2. View assembler files. (using option `-S`)
3. Create object files. (using option `-c`) And view them using tool `hexdump -C`.
4. Link those object files using `ld`.
   * How are headers processed?
   * One Definition Rule (ODR)
   * Header guards
   * Modules (C++20) compiler support
5. Explore the executable using `file` and `readelf`

> Try include stdio. Any issues?
> What really `g++` does? -> Compile with `g++ -v`.

**What about header files and libraries?**

1. Create separate file `bar.cpp` and `bar.h`.
2. Make a static library `libbar.a` out of it and move it to `lib`.
   ```
   g++ -c bar.cpp -o libbar.o
   ar rvs libbar.a libar.o
   ```
3. Link and run.
    ```
    g++ main.o -L./lib -lbar
    ```

**What are dynamic/shared libraries?**

1. Create `baz` source and header.
2. Make a dynamic/shared library `libbaz.so`.
3. Use `baz()` in main try to run it. (using option `LD_LIBRARY_PATH`)
4. Recompile with `-rpath`.
5. Change the dynamic library and observe whether the behavior changes.

> Is StandardTemplateLibrary (std) library static or dynamic?
> How are templates compiled? (will be discussed in later lab)

### C++ build systems

* make
* cmake
* ninja, bazel...


## C++ Tooling

* IDEs
  * VisualStudio
  * CLion
  * VSCode
  * vim + tmux

* Static analysers
  * WARNINGS
    * `g++` `clang++` -> `-Wall -Wpedantic -Wextra -Werror`
    * `MSVC` -> `/W[01234] /Wall`
  * syntax highlighters
  * usage, includes...

* linter
  * IDE built-in
  * [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html)
    * available 'built-in' style options [link](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)

> Pick your code style and stick to it!

* logging

* documentation generation
  * [`doxygen`](https://www.doxygen.nl/index.html)

* Debuggers
  * `gdb` `lldb` <- these create debuging interface that IDEs connect to
  * `std::cerr` and `1>/dev/null`
  * Debug / Release builds (compiler option `-g`, `-O[123]`)

* (Unit) Testing
  * [Google Test or `gtest`](https://github.com/google/googletest)
  * Test Driven Development (TDD)

* MicroBenchmarking
  * [Google Benchmark](https://github.com/google/benchmark)

### Explore CMake

1. Clone <https://gitlab.mff.cuni.cz/teaching/nprg041/drozdik/cmakegtesttemplate.git>
2. Explore how does CMake do what we did previously.

> Notice no inherent dependency on any environment (Windows, Unix) that was one of the main goals of CMake, try to clone this project in IDE on different OS and it will, with a bit of luck, work.

### Gitlab CI

> Speaking of `git` look at `.gitignore` `.git/info/exclude`. Do not push generated files (object, binaries, `.vscode`, `.idea`, temporary files...)

1. Setup `clang-format` checks on git hooks.
    ```
    clang-format --dry-run --Werror foo.cpp
    ```

2. Setup unit test CI (requires some Docker knowledge).
  * [Docker tutorial](https://docs.docker.com/get-started/)
  * [Gitlab CI](https://docs.gitlab.com/ee/ci/quick_start/)
  * Examples:
    * this repository -> [.gitlab-ci.yml](../.gitlab-ci.yml)
    * linked [cmakegtesttemplate repo](https://gitlab.mff.cuni.cz/teaching/nprg041/drozdik/cmakegtesttemplate/-/blob/master/.gitlab-ci.yml)


## Homework: MyC++ProjectTemplate

> This is *not* a mandatory assignment. Its purpose is to get you more comfortable with tools that you want to be using to their full potential in order to be a successful developer.

Create your own C++ working environment familiarize yourselves with tools you want to be using.

Setup CI on your Gitlab project.

Play with the debugger and find a way how to:
* try setting (conditional) breakpoints
* evaluate expressions during run
* explore call stack and jump between different stack frames
