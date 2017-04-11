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

struct Subset {
  int parent;
  int rank;
};

struct Graph* CreateGraph(int V, int E) {
  struct Graph* graph = new Graph;
  graph->V = V;
  graph->E = E;
  graph->edge = new Edge[E];
  return graph;
}

int Find(Subset *subsets, int i) {
  // find root and make root as parent of i (path compression)
  if (subsets[i].parent != i) {
    subsets[i].parent = Find(subsets, subsets[i].parent);
  }
  return subsets[i].parent;
}

void Union(Subset *subsets, int x, int y) {
  int xroot = Find(subsets, x);
  int yroot = Find(subsets, y);
  if (subsets[xroot].rank < subsets[yroot].rank) {
    subsets[xroot].parent = yroot;
  } else if (subsets[xroot].rank > subsets[yroot].rank) {
    subsets[yroot].parent = xroot;
  } else {
    subsets[yroot].parent = xroot;
    ++subsets[xroot].rank;
  }
}

int IsCycle(struct Graph* graph) {
  Subset *subsets = new Subset[graph->V];
  for (int v = 0; v < graph->V; ++v) {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }
  for (int i = 0; i < graph->E; ++i) {
    int x = Find(subsets, graph->edge[i].src);
    int y = Find(subsets, graph->edge[i].dest);
    if (x == y) {
      return 1;
    }
    Union(subsets, x, y);
  }
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
  
    
