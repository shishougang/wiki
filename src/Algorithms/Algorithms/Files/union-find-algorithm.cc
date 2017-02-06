#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NO_PARENT -1

struct Edge {
  int src;
  int dest;
};

struct Graph {
  // V-> Number of vertices
  int V;
  // E-> Number of edges
  int E;
  struct Edge* edge;
};

struct Graph* CreateGraph(int V, int E) {
  struct Graph* graph = new Graph;
  graph->V = V;
  graph->E = E;
  graph->edge = new Edge[E];
  return graph;
}

int Find(int *parent, int i) {
  if (parent[i] == NO_PARENT) {
    return i;
  }
  return Find(parent, parent[i]);
}

void Union(int *parent, int x, int y) {
  int xset = Find(parent, x);
  int yset = Find(parent, y);
  parent[xset] = yset;
}

int IsCycle(struct Graph* graph) {
  int *parent = new int[graph->V];
  memset(parent, NO_PARENT, sizeof(int) * graph->V);
  for (int i = 0; i < graph->E; ++i) {
    int x = Find(parent, graph->edge[i].src);
    int y = Find(parent, graph->edge[i].dest);
    if (x == y) {
      return 1;
    }
    Union(parent, x, y);
  }
  delete[] parent;
  return 0;
}

int main() {
    /* Let us create following graph
         0
        |  \
        |    \
        1-----2 */    
  int V = 3, E = 3;
  struct Graph* graph = CreateGraph(V, E);
  
  // add edge 0-1
  graph->edge[0].src = 0;
  graph->edge[0].dest = 1;
  
  // add edge 1-2
  graph->edge[1].src = 1;
  graph->edge[1].dest = 2;
  
  // add edge 0-2
  graph->edge[2].src = 0;
  graph->edge[2].dest = 2;
 
  if (IsCycle(graph))
    printf( "graph contains cycle\n" );
  else
    printf( "graph doesn't contain cycle\n" );
  delete graph;
  return 0;
}
  
    
