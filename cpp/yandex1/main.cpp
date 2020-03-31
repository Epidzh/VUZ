#include <iostream>
#include <ctime>

using namespace std;

void merge(int *a, int left, int mid, int right){
    int i = 0;
    int j = 0;
    int res =
    while ((left + i < mid) && (mid  + j < right)){
        if (a[left + i] < a[left + j])
        {
            
        }
    }
}

void sort(int *a, int left, int right) {
    if (left >= right - 1)
        return;
    int mid = (left + right) / 2;
    sort(*a, left, mid);
    sort(*a, mid, right);
    merge(*a, left, mid, right);
}

int main(int argc, const char * argv[]) {
    int n, m;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> m;
    int b[n];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    
    
    return 0;
}
