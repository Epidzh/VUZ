// #include <iostream>
// #include <time.h>
// #include <thread>

// using namespace std;

// static const int N = 10000;
// static const int MIN_VAL = -10000;
// static const int MAX_VAL = 10000;
// static const unsigned THREADS_NUM = thread::hardware_concurrency();
// mutex counter_lock;
// volatile static int counter = 0;

// template<class T>
// void print(T arr[])
// {
//     for (int i = 0; i < N; i++)
//         cout << arr[i] << " ";
//     cout << endl;
// }

// template<class T>
// void shell_sort(T arr[], int length)
// {
//     for (int step = length / 2; step > 0; step /= 2)
//     {
//         for (int j = step; j < length; j++)
//         {
//             for (int k = j - step; (k >= 0) && (arr[k] > arr[k + step]); k -= step)
//             {
//                 T tmp = arr[k];
//                 arr[k] = arr[k + step];
//                 arr[k + step] = tmp;
//             }
//         }
//     }
// }

// template<class T>
// void shelling(T arr[], int step, int j)
// {
//     for (int k = j - step; (k >= 0) && (arr[k] > arr[k + step]); k -= step)
//     {
//         T tmp = arr[k];
//         arr[k] = arr[k + step];
//         arr[k + step] = tmp;
//     }
//     counter_lock.lock();
//     counter--;
//     counter_lock.unlock();
// }

// template<class T>
// void shell_sort_multithread(T* arr, int length)
// {
//     for (int step = length / 2; step > 0; step /= 2)
//     {
//         for (int j = step; j < length; j++)
//         {
//             counter_lock.lock();
//             counter++;
//             counter_lock.unlock();
//             while (counter >= THREADS_NUM);
//             thread th(shelling<T>, cref(arr), step, j);
//             th.detach();
//         }
//         while (counter > 0);
//     }
// }

// template<class T>
// bool check(T arr[], int length)
// {
//     for (int i = 0; i < length-1; i++)
//         if (arr[i] > arr[i+1])
//             return false;
//     return true;
// }

// int main()
// {
//     srand((unsigned int)time(NULL));
//     int arr1[N];
//     int arr2[N];
//     for (int i = 0; i < N; i++)
//     {
//         int t = (MIN_VAL + rand()) % MAX_VAL;
//         arr1[i] = t;
//         arr2[i] = t;
//     }
    
//     unsigned long t = clock();
//     shell_sort(arr1, N);
//     cout << "One thread sort" << (check(arr1, N) ? " correct. " : "incorrect. ");
//     cout << "Time: " << (double)(clock() - t) / CLOCKS_PER_SEC << endl;
    
//     t = clock();
//     thread shell_sort_thread(shell_sort_multithread<int>, arr2, N);
//     shell_sort_thread.join();
//     cout << "Multithread sort" << (check(arr1, N) ? " correct. " : "incorrect. ");
//     cout << "Time: " << (double)(clock() - t) / CLOCKS_PER_SEC << endl;

//     return 0;
// }
#include "stdafx.h"
#include <iostream>
#include <thread>
#include <ctime>
#include <vector>
using namespace std;

void shellSort(vector <vector<int>>& wp, int k)
 {
    int n = wp[k].size();
    for (int gap = n / 2; gap > 0; gap /= 2)
     {

       for (int i = gap; i < n; i++)
        {
           int temp = wp[k][i];
           int j;
           for (j = i; j >= gap && wp[k][j - gap] > temp; j -= gap)
               wp[k][j] = wp[k][j - gap];
           wp[k][j] = temp;
        }
      }
 }

  int main()
 {
    int N, thN, i;
    cout << "\nEnter the length of array: ";
    cin >> N;
    cout << "\nEnter the amount of threads: ";
    cin >> thN;
    int* A = new int[N];
    for (i = 0; i < N; i++)
        A[i] = rand() % 100;

    thread* t = new thread[thN];

    vector<vector<int> > wp(thN, vector<int>());

    int start = 0;
    for (i = 0; i < thN; i++){
        for (int j = start; j < start + N / thN; j++){
            wp[i].push_back(A[j]);
        }
        start += N / thN;
    }

    double endTime, startTime;
    startTime = clock();

    for (i = 0; i < thN; i++)
        t[i] = thread(shellSort,wp,i);

    for (i = 0; i < thN; i++)
        t[i].join();

    endTime = clock();

    cout << "Runtime of shell sort: " << (endTime - startTime) / 1000 << endl;// time in miliseconds
    system("pause");
    return 0;
}