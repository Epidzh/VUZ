#include <iostream>

using namespace std;

class A
{
public:
    A() {cout << "A;";}
    static void print() {cout << "AAAAA";}
};

int main()
{
    int * param1 = new int(2);
    int param2 = 2;
    int * reference = &param2;
    
    std::cout << (*reference == *param1);
    
    return 0;
} 
