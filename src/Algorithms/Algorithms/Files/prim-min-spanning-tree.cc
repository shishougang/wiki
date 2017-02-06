#include <cstdio>
#include <climits>

#define V 5

int MinKey(int *key, bool *mst_set) {
  int min = INT_MAX;
  int min_index;
  for (int v = 0; v < V; ++v) {
    if (mst_set[v] == false && key[v] < min) {
      min = key[v];
      min_index = v;
    }
  }
  return min_index;
}

int PrintMST(int *parent, int graph[V][V]) {
  printf("Edge   Weight\n");
  for (int i = 1; i < V; i++) {
    printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
  }
}

void PrimMST(int graph[V][V]) {
  int key[V];
  bool mst_set[V];
  for (int i = 0; i < V; ++i) {
    key[i] = INT_MAX;
    mst_set[i] = false;
  }
  int parent[V];
  key[0] = 0;
  parent[0] = -1;
  for (int count = 0; count < V - 1; ++count) {
    int min_v = MinKey(key, mst_set);
    mst_set[min_v] = true;
    for (int v = 0; v < V; ++v) {
      // graph[min_v][v] is non zero only for adjacent vertices of min_v
      // mstSet[v] is false for vertices not yet included in MST
      // Update the key only if graph[min_v][v] is smaller than key[v]
      if (graph[min_v][v] && mst_set[v] == false &&
          graph[min_v][v] < key[v]) {
        parent[v] = min_v;
        key[v] = graph[min_v][v];
      }
    }
  }
  PrintMST(parent, graph);
}

int main() {
   /* Let us create the following graph
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
  int graph[V][V] = {{0, 2, 0, 6, 0},
                     {2, 0, 3, 8, 5},
                     {0, 3, 0, 0, 7},
                     {6, 8, 0, 0, 9},
                     {0, 5, 7, 9, 0},
  };
  PrimMST(graph);
  
  return 0;
}

