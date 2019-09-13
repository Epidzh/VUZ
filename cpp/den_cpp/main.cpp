#include <iostream>
#include <thread>

template<class T>
void print(T n) {
    for (int i = 0; i < 100; i++)
        std::cout << n;
}

int main(){
    
    std::thread th(print<int>, 1);
    th.detach();
    for (int i = 0; i < 100; i++)
        std::cout << 5;
    
    return 0;
}
