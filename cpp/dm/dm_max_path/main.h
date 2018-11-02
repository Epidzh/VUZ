//
//  main.h
//  cpp_solutions
//
//  Created by Сергей Петров on 28/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#ifndef main_h
#define main_h

char *input_file_name = "/Users/epidzhx/Library/Autosave Information/cpp_solutions/dm_max_path/tests/test2.in";
char *output_file_name = "/Users/epidzhx/Library/Autosave Information/cpp_solutions/dm_max_path/tests/test2.out";

#include "vector"
using namespace std;
typedef vector<vector<int> > Graph;

//int GetLeader(vector<int> &leader, int v) {
//    if (v == leader[v])
//        return v;
//
//    return leader[v] = GetLeader(leader, leader[v]);
//}
//
//void Union(vector<int> &leader, int a, int b) {
//    a = GetLeader(leader, a);
//    b = GetLeader(leader, b);
//    if (a != b)
//    {
//        if (rand() % 2 == 1)
//            swap(a, b);
//        leader[a] = b;
//    }
//}
//
//int GetMaxBandwidth(Graph &G, vector<int> &leader, int start)
//{
//    int max_c = 0;
//    for (int i = 0; i < G.size(); i++)
//        if (G[start][i] > 0 && GetLeader(leader, i) != GetLeader(leader, start))
//            max_c = max(max_c, G[start][i]);
//
//    return max_c;
//}
//
//void UpdateGraph(Graph &G, vector<int> &leader, int start, int max_c)
//{
//    for (int i = 0; i < G.size(); i++)
//        for (int j = G.size(); j > i; j--)
//            if (G[i][j] >= max_c)
//                Union(leader, i, j);
//}
//
//int FrankFrish(Graph &G, int start, int end)
//{
//    int ans = INT_MAX;
//
//    vector<int> leader;
//    for (int i = 0; i < G.size(); i++)
//        leader.push_back(i);
//
//    while (GetLeader(leader, start) != GetLeader(leader, end))
//    {
//        int max_c = GetMaxBandwidth(G, leader, start);
//        UpdateGraph(G, leader, start, max_c);
//        ans = min(max_c, ans);
//    }
//
//    return ans;
//}

int Dijkstra(vector<vector<int> > &g, int start,  int end)
{
    int INF = INT_MAX;
    int n = g.size();
    vector<int> d (n, INF),  p (n);
    d[start] = 0;
    vector<bool> u (n, false);
    for (int i = 0; i < n; i++)
        if (g[start][i] > 0)
            d[i] = g[start][i];
    u[start] = true;
    for (int i = 1; i < n; ++i) {
        
//        int v = -1;
//        for (int j = 0; j < n; ++j)
//            if (!u[j] && (v == -1 || d[j] < d[v]))
//                v = j;
//        if (d[v] == INF)
//            break;
//        u[v] = true;
//
//        for (size_t j = 0; j < g[v].size(); ++j)
//        {
//            if (g[v][i] > 0)
//                if (d[v] + g[v][i] < d[j])
//                {
//                    d[j] = d[v] + g[v][i];
//                    p[j] = v;
//                }
//        }
        
        int v = -1;
        for (int j = 0; j < n; j++)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == INF) break;
        u[v] = true;
        
        for (int j = 0; j < g[v].size(); j++)
            if (g[v][j] > 0 && (min(g[v][i], d[v]) > d[j] || d[j] == INF))
                d[j] = min(g[v][i], d[v]);
    }
    return d[end];
}
#endif /* main_h */
