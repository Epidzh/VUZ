#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
int Ford_Fulkerson (T &G, int n)
{
    int max_flow = 0;
    int find_way = 0;
    vector<int> visited(n);
    vector<int> parent(n);
    vector<vector<int> > F(n, vector<int> (n, 0));
    
    while (find_way != -1)
    {
        queue<int> q;
        q.push(0);
        visited.assign(n, 0);
        parent.assign(n, -1);
        visited[0] = 1;
        int v = 0;
        while (!q.empty())
        {
            v = q.front();
            q.pop();
            if (v == 1)
                break;
            for (int i = 0; i < n; i++)
            {
                if ((!visited[i]) && (G[v][i] - F[v][i] > 0))
                {
                    q.push(i);
                    visited[i] = 1;
                    parent[i] = v;
                }
            }
        }
        
        if (v != 1)
            find_way = -1;
        else
        {
            int curr_max_flow = G[parent[1]][1];
            int t = 1;
            while (t != 0)
            {
                int u = parent[t];
                curr_max_flow = min(curr_max_flow, G[u][t] - F[u][t]);
                t = u;
            }
            
            t = 1;
            while (t != 0)
            {
                int u = parent[t];
                F[u][t] += curr_max_flow;
                F[t][u] -= curr_max_flow;
                t = u;
            }
            max_flow += curr_max_flow;
        }
    }
    return max_flow;
}

int main()
{
    freopen("test8.in", "r", stdin);
    int n;
    cin >> n;
    vector<vector<int> > G (n, vector<int> (n));
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> G[i][j];
    int max_flow = Ford_Fulkerson(G, n);
    cout << max_flow << endl;
    return 0;
}