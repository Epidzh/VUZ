#include <iostream>
#include <time.h>
#include <vector>
//#define mysort(x) mysort(vector<int> a = arr)

using namespace std;

void mysort(int *arr)
{
    vector<int> a(arr, arr + sizeof arr / sizeof arr[0]);
    int size = 0;
    for (auto i : a)
        size++;
    cout << size;
}

int main()
{
    int arr[] = {1, 8, 9, 0, 7};
    
    mysort(arr);
    return 0;
}
