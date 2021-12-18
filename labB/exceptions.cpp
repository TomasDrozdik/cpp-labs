#include <exception>
#include <iostream>

struct MyException
    : std::exception
{
	const char * what () const throw ()
    {
    	return "C++ Exception";
    }
};

void bar() {
    throw MyException();
}

void baz() {
    bar();
}

void foo() {
    try {
        bar();
    } catch (const MyException & e) {
        std::cerr << e.what() << std::endl;
    }
}

int main(int, char **) {
    foo();
}
