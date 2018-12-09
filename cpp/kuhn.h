//
//  kuhn.h
//  cpp_solutions
//
//  Created by Сергей Петров on 21/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#ifndef kuhn_h
#define kuhn_h
#include <vector>
using namespace std;

typedef vector<vector<long> > List;

bool find_new_matching(List &G, vector<bool> &visited, vector<int> &in_matching, int v)
{
    if (visited[v])
        return false;
    visited[v] = true;
    for (int i = 0; i < G[v].size(); i++)
        if (in_matching[G[v][i]] == -1 || find_new_matching(G, visited, in_matching, in_matching[G[v][i]]))
        {
            in_matching[G[v][i]] = v;
            return true;
        }
    return false;
}

int Kuhn(List &G, int size_n, int size_m)
{
    int matching_num = 0;
    vector<int> in_matching(size_n + size_m, -1);

    for (int i = 0; i < size_n; i++)
    {
        vector<bool> visited(size_n + size_m, false);
        find_new_matching(G, visited, in_matching, i);
    }
    for (int i=size_n; i<size_n + size_m; ++i)
        if (in_matching[i] != -1)
            matching_num++;
    return matching_num;
}
#endif /* kuhn_h */
