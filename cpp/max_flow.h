#ifndef max_flow_h
#define max_flow_h

#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<long> > Matrix;

bool bfs_find_way(Matrix &G, Matrix &F, vector<int> &parent, vector<bool> &visited, int start, int end)
{
    queue<int> q;
    q.push(start);
    
    int v = start;
    while (!q.empty())
    {
        v = q.front();
        q.pop();
        if (v == end)
            return true;
        for (int i = 0; i < G[v].size(); i++)
        {
            if ((!visited[i]) && (G[v][i] - F[v][i] > 0))
            {
                q.push(i);
                visited[i] = true;
                parent[i] = v;
            }
        }
    }
    return false;
    
}

Matrix Ford_Fulkerson(Matrix &G, int n, int start, int end)
{
    int find_way = 1;
    vector<bool> visited(n);
    vector<int> parent(n);
    Matrix F(n, vector<long> (n, 0));
    
    while (find_way)
    {
        visited.assign(n, false);
        parent.assign(n, -1);
        visited[start] = true;
        find_way = bfs_find_way(G, F, parent, visited, start, end);
        if (find_way)
        {
            long curr_max_flow = G[parent[end]][end];
            int t = end;
            while (t != start)
            {
                int u = parent[t];
                curr_max_flow = min(curr_max_flow, G[u][t] - F[u][t]);
                t = u;
            }
            t = end;
            while (t != start)
            {
                int u = parent[t];
                F[u][t] += curr_max_flow;
                F[t][u] -= curr_max_flow;
                t = u;
            }
        }
    }
    return F;
}

#endif /* max_flow_h */
