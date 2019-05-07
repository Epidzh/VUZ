#include "graph-a.h"
#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>

void dfs(std::vector<std::vector<int> > &Graph, std::vector<bool> &visited, int i) {
    visited[i] = true;
    for (int j = 0; j < Graph[i].size(); j++) {
        if (visited[Graph[i][j]] == false) {
            dfs(Graph, visited, Graph[i][j]);
        }
    }
    std::cout << i << " "; // topologic?
}

void bfs(std::vector<std::vector<int> > &Graph, std::vector<bool> &visited, int i) {
    std::queue<int> q;
    q.push(i);
    visited[i] = true;
    while (!q.empty()) {
        int v = q.front();
        std::cout << v << " ";
        q.pop();
        for (int j = 0; j < Graph[v].size(); j++) {
            if (visited[Graph[v][j]] == false) {
                visited[Graph[v][j]] = true;
                q.push(Graph[v][j]);
            }
        }
    }
}

std::vector<int> dijkstra(std::vector<std::vector<node> > &Graph, int start) {
    const int INF = INT_MAX;
    std::vector<int> dist(Graph.size(), INF);
    dist[start] = 0;
    std::vector<bool> visited(Graph.size(), false);
    for (int i = 0; i < Graph.size(); i++) {
        int v = INF;
        for (int j = 1; j < Graph.size(); j++)
            if ((visited[j] == false) && (v == INF || dist[j] < dist[v]))
                v = j;
        if (v == INF)
            break;
        
        for (int j = 0; j < Graph[v].size(); j++) {
            int t = Graph[v][j].num;
            dist[t] = fmin(dist[t], dist[v] + Graph[v][j].weight);
        }
        visited[v] = true;
    }
    return dist;
}

bool comp(edge edge1, edge edge2) {
    return edge1.weight < edge2.weight;
}

std::vector<edge> kruskal(std::vector<edge> &Graph, int n) {
    std::vector<edge> ans;
    sort(Graph.begin(), Graph.end(), comp);
    std::vector<int> tree(n);
    for (int i = 0; i < n; i++)
        tree[i] = i;
    for (int i = 0; i < Graph.size(); i++) {
        int a = Graph[i].start;
        int b = Graph[i].end;
        if (tree[a] != tree[b]) {
            int old_id = tree[a],  new_id = tree[b];
            for (int j = 0; j < n; ++j)
                if (tree[j] == old_id)
                    tree[j] = new_id;
            ans.push_back(Graph[i]);
        }
    }
    return ans;
}
