#include <cstring>
#include <iostream>
#include <queue>
#include <limits>
using namespace std;

#define V 6

/* Returns true if there is a path from source 's' to sink 'd' in
  residual graph. Also fills parent[] to store the path */
bool Bfs(int res_graph[V][V], int s, int d, int *parent) {
  bool visited[V];
  memset(visited, 0, sizeof(visited));
  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v = 0; v < V; ++v) {
      if (visited[v] == false && res_graph[u][v] > 0) {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }
  return (visited[d] == true);
}

void Dfs(int res_graph[V][V], int s, bool *visited) {
  visited[s] = true;
  for (int i = 0; i < V; ++i) {
    if (res_graph[s][i] && !visited[i]) {
      Dfs(res_graph, i, visited);
    }
  }
}
        
void MinCut(int graph[V][V], int s, int d) {
  int u, v;
  int res_graph[V][V];
  for (u = 0; u < V; ++u) {
    for (v = 0; v < V; ++v) {
      res_graph[u][v] = graph[u][v];
    }
  }
  int parent[V];
  while (Bfs(res_graph, s, d, parent)) {
    int path_flow = numeric_limits<int>::max();
    for (v = d; v != s; v = parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, res_graph[u][v]);
    }
    for (v = d; v != s; v = parent[v]) {
      u = parent[v];
      res_graph[u][v] -= path_flow;
      res_graph[v][u] += path_flow;
    }
  }
  bool visited[V];
  memset(visited, false, sizeof(visited));
  Dfs(res_graph, s, visited);
  for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
      if (visited[i] && !visited[j] && graph[i][j]) {
        cout << i << " - " << j << endl;
      }
    }
  }
}

int main() {
  int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                      {0, 0, 10, 12, 0, 0},
                      {0, 4, 0, 0, 14, 0},
                      {0, 0, 9, 0, 0, 20},
                      {0, 0, 0, 7, 0, 4},
                      {0, 0, 0, 0, 0, 0}
  };
  MinCut(graph, 0, 5);
  return 0;
}
