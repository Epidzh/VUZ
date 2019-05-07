#ifndef graph_a_h
#define graph_a_h

#include <stdio.h>
#include <vector>

struct node {
    int num, weight;
    
    node(int v, int w) {
        num = v;
        weight = w;
    }
};

struct edge {
    int start, end, weight;
    edge(int s, int e, int w) {
        start = s;
        end = e;
        weight = w;
    }
};

void dfs(std::vector<std::vector<int> > &, std::vector<bool> &, int);
void bfs(std::vector<std::vector<int> > &, std::vector<bool> &, int);
std::vector<int> dijkstra(std::vector<std::vector<node> > &, int);
std::vector<edge> kruskal(std::vector<edge> &, int);
std::vector<int> prim(std::vector<std::vector<int> > &, int);

#endif
