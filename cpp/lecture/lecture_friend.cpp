#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class A
{
public:
    int a_public;
    
    void print()
    {
        cout << "This is A class";
    }

private:
    int a_private;
protected:
    int a_protected;
    
    friend int a_friend_private(A*, int);
    friend int a_friend_public(A*, int);
    friend int a_friend_protected(A*, int);
};

int a_friend_private(A* a, int x)
{
    return a->a_private = -1;
}

int a_friend_public(A* a, int x)
{
    return a->a_public = -2;
}

int a_friend_protected(A* a, int x)
{
    return a->a_protected = -3;
}

class B_private : private A
{
private:
    int b_private;
public:
    
    int a_friend_private_wrapper(int x) {
        return a_friend_private(this, x);
    }
    
    int a_friend_public_wrapper(int x) {
        return a_friend_public(this, x);
    }
    
    int a_friend_protected_wrapper(int x) {
        return a_friend_protected(this, x);
    }
};

class B_protected : protected A
{
private:
    int b_protected;
public:
    
    int a_friend_private_wrapper(int x) {
        return a_friend_private(this, x);
    }
    
    int a_friend_public_wrapper(int x) {
        return a_friend_public(this, x);
    }
    
    int a_friend_protected_wrapper(int x) {
        return a_friend_protected(this, x);
    }
};

class B_public : public A
{
private:
    int b_public;
public:
    
    int a_friend_private_wrapper(int x) {
        return a_friend_private(this, x);
    }
    
    int a_friend_public_wrapper(int x) {
        return a_friend_public(this, x);
    }
    
    int a_friend_protected_wrapper(int x) {
        return a_friend_protected(this, x);
    }
};

int main(void)
{
    B_private b_private;
    B_protected b_protected;
    B_public b_public;
    
    a_friend_private(&b_private, 1);
    a_friend_protected(&b_private, 2);
    a_friend_public(&b_private, 3);
    b_private.a_friend_private_wrapper(4);
    b_private.a_friend_protected_wrapper(5);
    b_private.a_friend_public_wrapper(6);
    
    a_friend_private(&b_protected, 7);
    a_friend_protected(&b_protected, 8);
    a_friend_public(&b_protected, 9);
    b_protected.a_friend_private_wrapper(10);
    b_protected.a_friend_protected_wrapper(11);
    b_protected.a_friend_public_wrapper(12);
    
    a_friend_private(&b_public, 13);
    a_friend_protected(&b_public, 14);
    a_friend_public(&b_public, 15);
    b_public.a_friend_private_wrapper(16);
    b_public.a_friend_protected_wrapper(17);
    b_public.a_friend_public_wrapper(18);
    
    return 0;
}
