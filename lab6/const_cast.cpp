#include <iostream>

int main(void)
{
	const int i = 7;
	std::cout << i << std::endl;
	const_cast<int &>(i) = 42;
	std::cout << i << std::endl;
	return 0;
}
