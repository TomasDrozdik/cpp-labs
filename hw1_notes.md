# Homework Macroprocessor notes

## Code style


Avoid one mega function


Any function like this:
```c++
void foo()
{
	//Stage 1
	...
	// Stage 2
	...
	// Stage 3
}
```
Can (and should) be split into multiple functions.


If your source code looks like this it is also pretty bad:
```
f(char & c)
{
	if {
		while() {
			if {
				foo(c);
				break;
			} else {
				if (
					c = get_next_c();
					continue;
				)
			}
		}
	} else {
		switch {
			case:
				if {

				}
		}
		if {

		} else {
			c = get_next_c();
		}
	}
}
```

Notes:
* if you cant split it then there is most likely something wrong with your design
	* start again from scratch
	* think about logical components of the problem, not from your solution
* single return point
	* if it branches too much it is too hard to follow
	* ofc this has a lot of exceptions
* this is just painfully hard to debug and follow
	* the proficiency of programmer is that you can read his/her code as if it was a pseudocode meant to explain a solution to the problem
	* with many branches, variable dependencies, and bad modularity this is impossible to do and to debug and test properly
* reader's expectation about "what is the next line" should be correct

global functions vs. static functions vs. in class methods vs. in class static methods

Output / Input on multiple places around the code.

Do you need the map to be ordered?

```c++
std::make_pair()
```

Pass by value does not need to be `const`.
Properties and methods should be `const` if viable.

Different approaches:
1. read by char and store in strings per identifier then output to cout
2. read by line, split by whitespace process afterwards
3. read all the input

For (2) and (3) look at `std::string_view` to avoid many copies.

Anytime you are working with substrings consider `std::string_view` as it is the only way to avoid copies.

Why is exit bad?

Notes on points.


## Opinions

Appreciate use of advanced concepts like algorithms, iterators, lambdas.

Find one code style and stick to it (using format checker).

Always use {}.

Line should be <120 chars long.

Compile with all warnings.

Formating.

Comments. Doc comments. Explanation of the process.

Property naming.
