#include <iostream>
#include <time.h>
#include <thread>

static const int N = 10000;
static const int MIN_VAL = -1000;
static const int MAX_VAL = 1000;

std::mutex shelling_lock;

class barrier
{
    
};

template<class T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
void shell_sort(T arr[], int length)
{
    for (int step = length / 2; step > 0; step /= 2)
        for (int j = step; j < length; j++)
            for (int k = j - step; k >= 0 && arr[k] > arr[k + step]; k -= step)
            {
                T tmp = arr[j];
                arr[k] = arr[j + step];
                arr[k + step] = tmp;
            }
}

template<class T>
void shelling(T arr[], int step, int j)
{
    for (int k = j - step; k >= 0 && arr[k] > arr[k + step]; k -= step)
    {
        shelling_lock.lock();
        T tmp = arr[j];
        arr[k] = arr[j + step];
        arr[k + step] = tmp;
        shelling_lock.unlock();
    }
}

template<class T>
void shell_sort_multithread(T arr[], int length)
{
    for (int step = length / 2; step > 0; step /= 2)
        for (int j = step; j < length; j++)
        {
            std::thread th(shelling<T>, std::ref(arr), step, j);
            th.detach();
        }
}

template<class T>
bool check(T arr[], int length)
{
    for (int i = 1; i < length; i++)
        if (arr[i] > arr[i-1])
            return false;
    return true;
}

int main()
{
    srand((unsigned int)time(NULL));
    int arr1[N];
    int arr2[N];
    for (int i = 0; i < N; i++)
    {
        int t = (MIN_VAL + rand()) % MAX_VAL;
        arr1[i] = t;
        arr2[i] = t;
    }
    
    shell_sort(arr1, N);
    
    std::thread shell_sort_thread(shell_sort_multithread<int>, std::ref(arr1), N);
    shell_sort_thread.join();
    
    std::cout << "arr1" << (check(arr1, N) ? " correct, " : "incorrect") << std::endl;
    std::cout << "arr2" << (check(arr2, N) ? " correct, " : "incorrect") << std::endl;
    return 0;
}
