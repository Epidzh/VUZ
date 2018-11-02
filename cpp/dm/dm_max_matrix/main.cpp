//
//  main.cpp
//  dm_max_matrix
//
//  Created by Сергей Петров on 23/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#include <iostream>
#include "main.h"
#include "max_flow.h"

int main(int argc, const char * argv[]) {
    
    long INF = LONG_MAX; // billion
    int n = 0, m = 0;
    freopen(input_file_name, "r", stdin);
    cin >> n >> m;
    int size = n+m+2;
    vector<int> max_sum_row(n), max_sum_col(m);
    for (int i = 0; i < n; i++)
        cin >> max_sum_row[i];
    for (int i = 0; i < m; i++)
        cin >> max_sum_col[i];
    
    // init matrix
    int istok = 0, stok = size - 1;
    Matrix G(size, vector<long> (size, 0));
    for (int i = 1; i < size; i++)
        if (i < n+1)
            G[0][i] = G[i][0] = max_sum_row[i-1];
        else
            G[0][i] = G[i][0] = 0;
    for (int i = 1; i < size-1; i++)
        if (i > n)
            G[i][size-1] = G[size-1][i] = max_sum_col[i-n-1];
        else
            G[i][size-1] = G[size-1][i] = 0;
    
    for (int i = 1; i < size-1; i++)
        for (int j = 1; j < i+1; j++)
            if ((i < n+1) || (i == j) || (j > n+1))
                G[i][j] = G[j][i] = 0;
            else
                G[i][j] = G[j][i] = INF;
    
    // find a solution
    Matrix F = Ford_Fulkerson(G, size, istok, stok);
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += F[istok][i];
    
    // print and compare result
    freopen(output_file_name, "r", stdin);
    int ans = 0;
    cin >> ans;
    cout << "Answer: " << sum;
    if (sum == ans)
        cout << " Correct" << endl;
    else
        cout << " Incorrect" << endl;
    return 0;
}
