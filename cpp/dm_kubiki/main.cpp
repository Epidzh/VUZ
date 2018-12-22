//
//  main.cpp
//  dm_kubiki
//
//  Created by Сергей Петров on 27/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#include <iostream>
#include "main.h"
#include "max_flow.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    int n = 0;
    freopen(input_file_name, "r", stdin);
    string w;
    string p;
    cin >> n;
    cin >> w;
    
    int size = n + w.length() + 2;
    vector<vector<long> > G(size, vector<long> (size, 0));
    for(int i = 0; i < n; i++)
    {
        cin >> p;
        for (int j = 0; j < w.length(); j++)
            for (int k = 0; k < p.length(); k++)
                if (w[j] == p[k])
                    G[i][n+j] = 1;
    }
    for (int i = 0; i < n; i++)
        G[i][size-2] = G[size-2][i] = 1;
    for (int i = n; i < n+w.length(); i++)
        G[i][size-1] = G[size-1][i] = 1;

    Matrix Flow = Ford_Fulkerson(G, size, size-2, size-1);
    int f_power = 0;
    for (int i = 0; i < size-1; i++)
        f_power += Flow[i][size-1];
    
    string ans;
    string correct_ans;
    freopen(output_file_name, "r", stdin);
    cin >> correct_ans;
    if (f_power == w.length())
        ans = "YES";
    else
        ans = "NO";
    cout << ans << ": ";
    if (ans == correct_ans)
        cout << "Correct" << endl;
    else
        cout << "Incorrect" << endl;
    return 0;
}
