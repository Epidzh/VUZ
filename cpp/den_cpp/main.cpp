#include <iostream>
#include <time.h>
#include <thread>
#include <time.h>

static const int N = 10000;
static const int MIN_VAL = -1000;
static const int MAX_VAL = 1000;

std::mutex shelling_lock;
std::mutex counter_lock;
static int counter = 0;

template<class T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

void print(int arr[], int length)
{
    for (int i = 0; i < length; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

template<class T>
void shell_sort(T arr[], int length)
{
    for (int step = length / 2; step > 0; step /= 2)
    {
        for (int j = step; j < length; j++)
        {
            for (int k = j - step; (k >= 0) && (arr[k] > arr[k + step]); k -= step)
            {
                T tmp = arr[k];
                arr[k] = arr[k + step];
                arr[k + step] = tmp;
            }
        }
    }
}

template<class T>
void shelling(T arr[], int step, int j)
{
    for (int k = j - step; (k >= 0) && (arr[k] > arr[k + step]); k -= step)
    {
        shelling_lock.lock();
        T tmp = arr[k];
        arr[k] = arr[k + step];
        arr[k + step] = tmp;
        shelling_lock.unlock();
    }
    counter_lock.lock();
    counter--;
    counter_lock.unlock();
}

template<class T>
void shell_sort_multithread(T arr[], int length)
{
    for (int step = length / 2; step > 0; step /= 2)
    {
        for (int j = step; j < length; j++)
        {
            counter_lock.lock();
            counter++;
            counter_lock.unlock();
            std::thread th(shelling<T>, std::ref(arr), step, j);
            th.detach();
        }
        while (counter > 0);
    }
}

template<class T>
bool check(T arr[], int length)
{
    for (int i = 0; i < length-1; i++)
        if (arr[i] > arr[i+1])
            return false;
    return true;
}

int main()
{
    srand((unsigned int)time(NULL));
    int arr1[N];
    int arr2[N];
    std::cout << "Array: " << std::endl;
    for (int i = 0; i < N; i++)
    {
        int t = (MIN_VAL + rand()) % MAX_VAL;
        arr1[i] = t;
        arr2[i] = t;
        //std::cout << t << " ";
    }
    std::cout << std::endl;
    
    unsigned long t = clock();
    shell_sort(arr1, N);
    std::cout << "One thread sort" << (check(arr1, N) ? " correct. " : "incorrect. ");
    std::cout << "Time: " << (double)(clock() - t) / CLOCKS_PER_SEC << std::endl;
    
    t = clock();
    std::thread shell_sort_thread(shell_sort_multithread<int>, std::ref(arr2), N);
    shell_sort_thread.join();
    std::cout << "Multithread sort" << (check(arr1, N) ? " correct. " : "incorrect. ");
    std::cout << "Time: " << (double)(clock() - t) / CLOCKS_PER_SEC << std::endl;
    
    return 0;
}
