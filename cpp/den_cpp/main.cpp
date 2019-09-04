#include <iostream>
#include <thread>
#include <time.h>
#include <math.h>

using namespace std;

const int ARR_LENGTH = 100;
const int MIN_VALUE = 0;
const int MAX_VALUE = 100;
int shalling_over = 0;

template<class T>
void swap(T& a, T& b)
{
    T t = a;
    a = b;
    b = t;
}

template<class T>
void shelling(T& arr, int step, int start,  int end)
{
    for (int i = start; i < end; i+=step)
        for (int j = start; j < i; j += step)
            if (arr[j] > arr[j + step])
                swap(arr[j], arr[j + step]);
    shalling_over++;
}

template<class T>
void shell_one_thread(T& arr, int start, int end)
{
    int step = (start + end) / 2;
    while (step > 0)
    {
        for (int j = 0; j < step; j++)
        {
            std::thread shalling_step(shelling(std::ref(arr), step, j, end));
            shalling_step.detach();
        }
        while (shalling_over < step);
        step /= 2;
    }
}

template<class T>
void shell_multithread(T& arr, int start, int end)
{

}

int main()
{
    srand(time(0));
    int arr1[ARR_LENGTH];
    int arr2[ARR_LENGTH];
    cout << "ARR:" << endl;
    for (int i = 0; i < ARR_LENGTH; i++)
    {
        int t = (MIN_VALUE + rand()) % MAX_VALUE;
        arr1[i] = t;
        arr2[i] = t;
        cout << arr1[i] << " ";
    }
    cout << endl;

    shell_one_thread(arr1, 0, ARR_LENGTH);

    std::thread shell_sort(shell_multithread, std::ref(arr2), 0, ARR_LENGTH);
    shell_sort.join();

    return 0;
}