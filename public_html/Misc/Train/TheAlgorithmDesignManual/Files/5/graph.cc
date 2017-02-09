#include <cstdio>

#define MAXV 1000  // maximum number of vertices

typedef struct {
  int y;  // adjacency info
  int weight;  // edge weight, if any
  struct edgenode *next;  // next edge in list
} edgenode;

typedef struct {
  edgenode *edges[MAXV + 1];   // adjacency info
  int degree[MAXV + 1];  // outdegree of each vertex
  int nvertices;  // number of vertices in graph
  int nedges;  // number of edges in graph
  bool directed;  // is the graph directed
} graph;

void initialize_graph(graph *g, bool directed) {
  int i;
  g->nvertices = 0;
  g->nedges = 0;
  g->directed = directed;
  for (i = 1; i <= NMAX; ++i) {
    g->degree[i] = 0;
    g->edges[i] = NULL;
  }
}

void insert_edge(graph *g, int x, int y, bool directed) {
  edgenode *p;
  p = new edgenode;
  p-> weight = 0;
  p->y = y;
  p->next = g->edges[x];
  g->edges[x] = p;
  g->degree[x]++;
  if (directed == false) {
    insert_edge(g, y, x, true);
  } else {
    g->nedges++;
  }
}

void read_graph(graph *g, bool directed) {
  int i;
  int m;
  int x, y;
  initialize_graph(g, directed);
  scanf("%d %d", &(g->nvertices), &m);
  for (i = 1; i <= m; ++i) {
    scanf("$d %d", &x, &y);
    insert_edge(g, x, y, directed);
  }
}

print_graph(graph *g) {
  int i;
  edgenode *p;
  for (i = 1; i <= g->nvertices; ++i) {
    printf("%d: ", i);
    p = g->edges[i];
    while (p != NULL) {
      printf("%d ", p->y);
      p = p->next;
    }
    printf("\n");
  }
}
