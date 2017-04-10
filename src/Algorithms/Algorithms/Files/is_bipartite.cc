#include <iostream>
#include <queue>
using namespace std;

#define V 4

bool IsBipartiteUtil(int G[][V], int src, int *color_arr) {
  color_arr[src] = 1;
  queue<int> q;
  q.push(src);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v = 0; v < V; ++v) {
      if (G[u][v] && color_arr[v] == -1) {
        color_arr[v] = 1 - color_arr[u];
        q.push(v);
      } else if (G[u][v] && color_arr[v] == color_arr[u]) {
        return false;
      }
    }
  }
  return true;
}

bool IsBipartite(int G[][V]) {
  // Create a color array to store colors assigned to all veritces.
  int color_arr[V];
  for (int i = 0; i < V; ++i) {
    color_arr[i] = -1;
  }
  // This code is to handle disconnected graoh
  for (int i = 0; i < V; ++i) {
    if (color_arr[i] == -1) {
      if (IsBipartiteUtil(G, i, color_arr) == false) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int G[][V] = {{0, 1, 0, 1},
                {1, 0, 1, 0},
                {0, 1, 0, 1},
                {1, 0, 1, 0}};
  IsBipartite(G) ? cout << "Yes" : cout << "No";
  return 0;
}
