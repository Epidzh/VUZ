#include <iostream>
#include <vector>
#include "graph-a.h"

using namespace std;

int main()
{
    int n = 6;
    vector<vector<int> > Graph(n);
    Graph[1].push_back(2);
    Graph[1].push_back(3);
    Graph[1].push_back(4);
    
    Graph[2].push_back(1);
    Graph[2].push_back(3);
    
    Graph[3].push_back(1);
    Graph[3].push_back(2);
    Graph[3].push_back(5);
    
    Graph[4].push_back(1);
    
    Graph[5].push_back(3);
    
    
    vector<bool> visited(n, false);
    for (int i = 1; i < n; i++)
        if (visited[i] == false)
            dfs(Graph, visited, i);
    
    visited.assign(n, false);
    for (int i = 1; i < n; i++)
        if (visited[i] == false)
            bfs(Graph, visited, i);
    
    vector<int> dist;
    vector<vector<node> > Graph2(n);
    Graph2[1].push_back(node(2, 3));
    Graph2[1].push_back(node(3, 5));
    Graph2[1].push_back(node(4, 42));
    
    Graph2[2].push_back(node(1, 3));
    Graph2[2].push_back(node(3, 1));
    
    Graph2[3].push_back(node(1, 5));
    Graph2[3].push_back(node(2, 1));
    Graph2[3].push_back(node(5, 10));
    
    Graph2[4].push_back(node(1, 42));
    
    Graph2[5].push_back(node(3, 10));
    dist = dijkstra(Graph2, 1);
//    for (int i = 1; i < dist.size(); i++)
//        cout << dist[i] << " ";
    
    vector<edge> Graph3;
    Graph3.push_back(edge(1, 2, 3));
    Graph3.push_back(edge(1, 3, 5));
    Graph3.push_back(edge(1, 4, 42));
    Graph3.push_back(edge(2, 3, 1));
    Graph3.push_back(edge(5, 3, 10));

    vector<edge> tree = kruskal(Graph3, n);
    for (int i = 0; i < tree.size(); i++)
        cout << tree[i].start << " " << tree[i].end << " " << tree[i].weight << endl;

    int INF = 1000000; // ПРИМ - не дописан
    vector<vector<int> > Graph4(n, vector<int> (n, INF));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < Graph2[i].size(); j++)
                Graph4[i][Graph2[i][j].num] = Graph2[i][j].weight;
    
    tree = prim(Graph4, n, INF);
    for (int i = 0; i < tree.size(); i++)
        cout << tree[i].start << " " << tree[i].end << " " << tree[i].weight << endl;
    return 0;
}
