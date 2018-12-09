//
//  main.cpp
//  lectures
//
//  Created by Сергей Петров on 22/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#include <iostream>

using namespace std;

class A
{
private:
    int p;
public:

    A()
    {
        p = 10;
    }
    void fun(int a)
    {
        p = a;
    }
    
    void print()
    {
        cout << p;
    }
//    A() {
//        i = 10;
//    }
//
//    ~A() {
//        i = 0;
//    }
    
};



int main()
{
    A a;
    a.fun(666);
    a.print();
    return 0;
}
