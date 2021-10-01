#include <iostream>
#include <vector>

int vynasob(int cislo1, int cislo2)
{
    return cislo1 * cislo2;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int gcd2(int a, int b)
{
    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }
    return a;
}

// Task 3.2
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Task 3.3
void bsort(std::vector<int> &vec)
{
    for (int i = 1; i < vec.size(); i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (vec[j] > vec[j - 1])
            {
                swap(&vec[j], &vec[j - 1]);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    // Task 1
    // note what is in argv[0]
#if 0

    for(int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
#endif

    // Task 2
#if 0
    int x,y;
    std::cin >> x;
    std::cin >>y;


    std::cout << x << " " << y << std::endl;
    std::cout << vynasob(x, y) << std::endl;

    std::cout << gcd(x,y) << "\n";
    std::cout << gcd2(x, y) << "\n";
#endif

    // Task 3
#if 1
    // Task 3.2
    int a = 42;
    int b = 73;

    std::cout << a << ' ' << b << '\n';
    swap(&a, &b);
    std::cout << a << ' ' << b << '\n';

    // Task 3.1
    std::vector<int> v;
    for (int i = -10; i < 10; i++)
    {
        v.push_back(i);
    }

    bsort(v);

    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << std::endl;
    }
#endif
}
