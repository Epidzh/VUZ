#include <iostream>

using namespace std;

class A
{
public:
    virtual void fun()
    {
        cout << "I'm funtion from A class" << endl;
    }
};

class B : public A
{
public:
    virtual void fun()
    {
        cout << "I'm funtion from B class" << endl;
    }
};

int main()
{

    A a, *pa; pa = &a;
    B b, *pb; pb = &b;

    pa->fun(); pb->fun();
    pa = pb;
    pa->fun();

    return 0;
}