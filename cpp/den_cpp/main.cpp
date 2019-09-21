#include <iostream>
#include <time.h>
#include <thread>

using namespace std;

static const int N = 10000;
static const int MIN_VAL = -10000;
static const int MAX_VAL = 10000;
static const unsigned THREADS_NUM = thread::hardware_concurrency();
mutex counter_lock;
volatile static int counter = 0;

template<class T>
void print(T arr[])
{
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;
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
        T tmp = arr[k];
        arr[k] = arr[k + step];
        arr[k + step] = tmp;
    }
    counter_lock.lock();
    counter--;
    counter_lock.unlock();
}

template<class T>
void shell_sort_multithread(T* arr, int length)
{
    for (int step = length / 2; step > 0; step /= 2)
    {
        for (int j = step; j < length; j++)
        {
            counter_lock.lock();
            counter++;
            counter_lock.unlock();
            while (counter > THREADS_NUM);
            thread th(shelling<T>, cref(arr), step, j);
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
    for (int i = 0; i < N; i++)
    {
        int t = (MIN_VAL + rand()) % MAX_VAL;
        arr1[i] = t;
        arr2[i] = t;
    }
    
//    print(arr1);
    unsigned long t = clock();
    shell_sort(arr1, N);
    cout << "One thread sort" << (check(arr1, N) ? " correct. " : "incorrect. ");
    cout << "Time: " << (double)(clock() - t) / CLOCKS_PER_SEC << endl;
    
    t = clock();
    thread shell_sort_thread(shell_sort_multithread<int>, arr2, N);
    shell_sort_thread.join();
    cout << "Multithread sort" << (check(arr1, N) ? " correct. " : "incorrect. ");
    cout << "Time: " << (double)(clock() - t) / CLOCKS_PER_SEC << endl;
    
//    print(arr1);
//    print(arr2);
    return 0;
}
