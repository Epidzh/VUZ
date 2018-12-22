//
//  main.h
//  cpp_solutions
//
//  Created by Сергей Петров on 28/10/2018.
//  Copyright © 2018 SerGioPetrovx. All riGhts reserved.
//

#ifndef main_h
#define main_h

#include "vector"
using namespace std;
typedef vector<vector<int> > Graph;

char *input_file_name = "/Users/epidzhx/Staff/VUZ/cpp/dm_max_path/tests/test8.in";
char *output_file_name = "/Users/epidzhx/Staff/VUZ/cpp/dm_max_path/tests/test8.out";

void relax(Graph &G, int v, vector<int> &d)
{
    for (int j = 0; j < G[v].size(); j++)
        d[j] = min(G[v][j], d[v]) > d[j] ? min(G[v][j], d[v]) : d[j];
}
int find_max(Graph &G, vector<int> &d, vector<bool> &used)
{
    int ans = -1;
    for (int j = 0; j < G.size(); j++)
        ans = !used[j] && (ans == -1 || d[j] > d[ans]) ? j : ans;
    return ans;
}

vector<int> Dijkstra(vector<vector<int> > &G, int start)
{
    int INF = -INT_MAX;
    vector<int> dist(G.size(), INF);
    dist[start] = 0;
    vector<bool> used(G.size(), false);
    for (int i = 0; i < G.size(); i++)
    {
        if (G[start][i] > 0)
            dist[i] = G[start][i];
    }
    used[start] = true;
    for (int i = 0; i < G.size(); ++i)
    {
        
        int v = find_max(G, dist, used);
        if (bool check = (dist[v] == INF) || (v == -1))
            break;
        used[v] = true;
        relax(G, v, dist);
    }
    return dist;
}
#endif /* main_h */
