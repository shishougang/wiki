#include <cstdio>
#include <cstdlib>
#include <cstring>

struct Edge {
  int src;
  int dest;
  int weight;
};

struct Graph {
  int V;
  int E;
  struct Edge *edge;
};

struct Graph* CreateGraph(int V, int E) {
  struct Graph *graph = new Graph;
  graph->V = V;
  graph->E = E;
  graph->edge = new Edge[E];
  return graph;
}

// A structure to represent a subset for union-find
struct subset {
  int parent;
  int rank;
};

int Find(struct subset *subsets, int i) {
  // find root and make root as parent of i (path compression)
  if (subsets[i].parent != i) {
    subsets[i].parent = Find(subsets, subsets[i].parent);
  }
  return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset *subsets, int x, int y) {
  int xroot = Find(subsets, x);
  int yroot = Find(subsets, y);

  if (subsets[xroot].rank < subsets[yroot].rank) {
    subsets[xroot].parent = yroot;
  } else if (subsets[xroot].rank > subsets[yroot].rank) {
    subsets[yroot].parent = xroot;
  } else {
    // If ranks are same, then make one as root and increment
    // its rank by one
    subsets[yroot].parent = xroot;
    subsets[xroot].rank++;
  }
}

int EdgeComp(const void *a, const void *b) {
  struct Edge *e1 = (struct Edge*) a;
  struct Edge *e2 = (struct Edge*) b;
  return e1->weight > e2->weight;
}

void KruskalMST(struct Graph *graph) {
  qsort(graph->edge, graph->E, sizeof(graph->edge[0]), EdgeComp);
  struct subset *subsets = new subset[graph->V];

  for (int v = 0; v < graph->V; ++v) {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }
  int e = 0;
  int i = 0;
  struct Edge result[graph->V];
  while (e < graph->V - 1) {
    struct Edge next_edge = graph->edge[i++];
    int x = Find(subsets, next_edge.src);
    int y = Find(subsets, next_edge.dest);
    if (x != y) {
      result[e++] = next_edge;
      Union(subsets, x, y);
    }
    // else discard the next_edge
  }
  printf("Following are the edges in the constructed MST\n");
  for (i = 0; i < e; ++i) {
    printf("%d -- %d == %d\n", result[i].src, result[i].dest,
           result[i].weight);
  }
  delete[] subsets;
}

int main()
{
  /* Let us create following weighted graph
         10
     0--------1
     |  \     |
     6|   5\   |15
     |      \ |
     2--------3
         4       */
  int V = 4;  // Number of vertices in graph
  int E = 5;  // Number of edges in graph
  struct Graph* graph = CreateGraph(V, E);
  // add edge 0-1
  graph->edge[0].src = 0;
  graph->edge[0].dest = 1;
  graph->edge[0].weight = 10;
 
  // add edge 0-2
  graph->edge[1].src = 0;
  graph->edge[1].dest = 2;
  graph->edge[1].weight = 6;
 
  // add edge 0-3
  graph->edge[2].src = 0;
  graph->edge[2].dest = 3;
  graph->edge[2].weight = 5;
 
  // add edge 1-3
  graph->edge[3].src = 1;
  graph->edge[3].dest = 3;
  graph->edge[3].weight = 15;
 
  // add edge 2-3
  graph->edge[4].src = 2;
  graph->edge[4].dest = 3;
  graph->edge[4].weight = 4;
 
  KruskalMST(graph);
  delete[] graph->edge;
  delete graph;
  return 0;
}
