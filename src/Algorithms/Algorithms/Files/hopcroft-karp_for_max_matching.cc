#include <climits>
#include <iostream>
#include <list>
#include <queue>
using namespace std;

#define NIL 0
#define INF INT_MAX

class BipGraph {
 public:
  BipGraph(int m, int n);
  void AddEdge(int u, int v);
  // Returns true if there is an augmenting path
  bool Bfs();
  // Adds augmenting path if there is one beginning with u
  bool Dfs(int u);
  // Returns size of maximum matcing
  int HopcroftKarp();
 private:
  // m and n are number of vertices on left
  // and right sides of Bipartite Graph
  int m, n;
  list<int> *adj;
  int *pair_u, *pair_v, *dist;
};

BipGraph::BipGraph(int m, int n) {
  this->m = m;
  this->n = n;
  adj = new list<int>[m+1];
}

void  BipGraph::AddEdge(int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

int BipGraph::HopcroftKarp() {
  pair_u = new int[m+1];
  pair_v = new int[n+1];
  // dist[u] stores distance of left side vertices
  // dist[u] is one more than dist[u'] if u is next
  // to u'in augmenting path
  dist = new int[m+1];
  for (int u = 0; u <= m; ++u) {
    pair_u[u] = NIL;
  }
  for (int v = 0; v <= n; ++v) {
    pair_v[v] = NIL;
  }
  int result = 0;
  // Keep updating the result while there is an
  // augmenting path.
  while (Bfs()) {
    // Find a free vertex
    for (int u = 1; u <= m; ++u) {
      // If current vertex is free and there is
      // an augmenting path from current vertex
      if (pair_u[u] == NIL && Dfs(u)) {
        ++result;
      }
    }
  }
  return result;
}

bool BipGraph::Bfs() {
  queue<int> que;
  for (int u = 1; u <= m; ++u) {
    if (pair_u[u] == NIL) {
      // If this is a free vertex, add it to queue
      dist[u] = 0;
      que.push(u);
    } else {
      // Else set distance as infinite so that this vertex
      // is considered next time
      dist[u] = INF;
    }
  }
  dist[NIL] = INF;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    if (dist[u] < dist[NIL]) {
      // If this node is not NIL and can provide a shorter path to NIL
      list<int>::iterator it;
      for (it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = *it;
        if (dist[pair_v[v]] == INF) {
          dist[pair_v[v]] = dist[u] + 1;
          que.push(pair_v[v]);
        }
      }
    }
  }
  return (dist[NIL] != INF);
}

bool BipGraph::Dfs(int u) {
  if (u != NIL) {
    list<int>::iterator it;
    for (it = adj[u].begin(); it != adj[u].end(); ++it) {
      int v = *it;
      if (dist[pair_v[v]] == dist[u] + 1) {
        if (Dfs(pair_v[v]) == true) {
          pair_v[v] = u;
          pair_u[u] = v;
          return true;
        }
      }
    }
    // If there is no augmenting path beginning with u.
    dist[u] = INF;
    return false;
  }
  return true;
}

int main() {
  BipGraph g(4, 4);
  g.AddEdge(1, 2);
  g.AddEdge(1, 3);
  g.AddEdge(2, 1);
  g.AddEdge(3, 2);
  g.AddEdge(4, 2);
  g.AddEdge(4, 4);
  cout << "Size of maximum matching is " << g.HopcroftKarp();
  return 0;
}
