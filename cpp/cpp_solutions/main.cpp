#include <iostream>
#include <time.h>
//using namespace std;
#include <vector>

using namespace std;

int main()
{
    int n = 2, m = 6;
    int a[] = {1, 1, 1, 0, 0, 1};
    int b[] = {1, 0, 0, 1, 1, 0};
    
    int ans[] = {1, 0, 0, 1, 1, 0};
    int i = 0;
    bool t = false;
    while (!t)
    {
        if (i > 1000)
            break;
        i++;
        int num = ans[m - 1];
        for (int i = m - 1; i >= 0; i--)
            ans[i] = (i > 0) ? (ans[i-1] + num * a[i]) % n : (0 + num * a[0]) % n;
//        for (int i = 0; i < m; i++)
//            cout << ans[i] << " ";
//        cout << endl;
        t = true;
        for (int i = 0; i < m; i++)
            t *= b[i] == ans[i];
    }
    cout << i << endl;
    return 0;
}
