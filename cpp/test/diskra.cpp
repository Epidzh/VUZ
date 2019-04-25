#include <iostream>
 #include <time.h>
 #include <vector>

 using namespace std;

 int main()
{
    int n = 5, m = 2;
    int a[] = {1, 3};
    int b[] = {1, 2};

    int ans[] = {1, 2};
    int i = 0;
    bool t = true;
    while (t)
    {
        if (i > 10000)
            break;
        i++;
        int num = ans[m - 1];
        for (int i = m - 1; i >= 0; i--)
            ans[i] = (i > 0) ? (ans[i-1] + num * a[i]) % n : (0 + num * a[0]) % n;
        for (int i = 0; i < m; i++)
            if (b[i] != ans[i])
                continue;
    }
    cout << i << endl;
    return 0;
}