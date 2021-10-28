#include<iostream>

using namespace std;

class Base
{
public:
    Base()
    {
        cout<<"Constructing base \n";
    }

    // virtual ~Base()
    ~Base()
    {
        cout<<"Destructing base \n";
    }
};

class Derived: public Base
{
public:
    Derived()
    {
        cout<<"Constructing derived \n";
    }

    ~Derived()
    {
        cout<<"Destructing derived \n";
    }
};

int main(void)
{
  Base * b = new Derived();
  delete b;
  return 0;
}