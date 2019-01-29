char *input_file_name = "/Users/epidzhx/Staff/VUZ/cpp/dm_max_matching/tests/test1.in";
char *output_file_name = "/Users/epidzhx/Staff/VUZ/cpp/dm_max_matching/tests/test1.out";
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "max_flow.h"

int main()
{
    int n = 0, m = 0;
    freopen(input_file_name, "r", stdin);
    cin >> n >> m;
    
    int size = n + m + 2;
    
    //init Matrix
    Matrix mc(size, vector<long> (size));
    
    for (int i = 0; i < n; i++)
    {
        int v_num;
        cin >> v_num;
        for (int j = 0; j < v_num; j++)
        {
            int v;
            cin >> v;
            mc[i][n+v] = 1;
        }
    }
    for (int i = 0; i < n; i++)
        mc[i][size-2] = mc[size-2][i] = 1;
    for (int i = n; i < n+m; i++)
        mc[i][size-1] = mc[size-1][i] = 1;
    
    // Checking the answer and calculating
    freopen(output_file_name, "r", stdin);
    int ans = 0;
    cin >> ans;
    
    Matrix Flow = Ford_Fulkerson(mc, size, size-2, size-1);
    int f_power = 0;
    for (int i = 0; i < size-1; i++)
        f_power += Flow[i][size-1];
    cout << "Flow answer: " << f_power;
    if (f_power == ans)
        cout << " Correct" << endl;
    else
        cout << " Incorrect" << endl;
}
