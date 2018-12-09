//
//  main.cpp
//  dm_max_path
//
//  Created by Сергей Петров on 28/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#include <iostream>
#include "main.h"

int main(int argc, const char * argv[]) {

    int start = 0, end = 1;
    freopen(input_file_name, "r", stdin);
    int n = 0;
    cin >> n;
    Graph G(n, vector<int> (n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> G[i][j];
    freopen(output_file_name, "r", stdin);
    int correct_ans = 0;
    cin >> correct_ans;

    vector<int> vec = Dijkstra(G, start);
    int ans = vec.at(end);
    cout << ans;
    if (ans == correct_ans)
        cout << " Correct" << endl;
    else
        cout << " Incorrect" << endl;
    return 0;
}
