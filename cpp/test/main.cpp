#include <iostream>
#include "test.cpp"

using namespace std;

union u {
  long a;
  short b;
} a;
int main()
{
    //cout << a.a << " " << a.b << endl;
    a.a = 10;
    cout << a.a << " " << a.b << endl;
    a.a = 1000000000;
    cout << a.a << " " << a.b << endl;

    cout << var;
    
}