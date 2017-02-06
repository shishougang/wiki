#include <iostream>
#include <list>

using namespace std;

#define NIL -1

class Graph {
 public:
  Graph(int V);
  virtual ~Graph();
  void AddEdge(int v, int w);
  void AP();
 private:
  int V;
  list<int> *adj;
  void APUtil(int u, bool *visited, int *disc, int *low,
              int *parent, bool *ap);
};

Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
}

Graph::~Graph() {
  delete[] adj;
}

void Graph::AddEdge(int v, int w) {
  adj[v].push_back(w);
  adj[w].push_back(v);  // Note: the graph is undirected
}

void Graph::AP() {
  bool *visited = new bool[V];
  int *disc = new int[V];
  int *low = new int[V];
  int *parent = new int[V];
  bool *ap = new bool[V];

  for (int i = 0; i < V; ++i) {
    parent[i] = NIL;
    visited[i] = false;
    ap[i] = false;
  }
  for (int i = 0; i < V; ++i) {
    if (visited[i] == false) {
      APUtil(i, visited, disc, low, parent, ap);
    }
  }

  for (int i = 0; i < V; ++i) {
    if (ap[i] == true) {
      cout << i << " ";
    }
  }
  delete[] visited;
  delete[] disc;
  delete[] low;
  delete[] parent;
  delete[] ap;
}

void Graph::APUtil(int u, bool *visited, int *disc, int *low,
              int *parent, bool *ap) {
  static int time = 0;
  int children = 0;
  visited[u] = true;
  disc[u] = low[u] = ++time;
  list<int>::iterator it;
  for (it = adj[u].begin(); it != adj[u].end(); ++it) {
    int v = *it;
    if (visited[v] == false) {
      children++;
      parent[v] = u;
      APUtil(v, visited, disc, low, parent, ap);
      low[u] = min(low[u], low[v]);
      // case 1
      if (parent[u] == NIL && children > 1) {
        ap[u] = true;
      }
      // case 2
      if (parent[u] != NIL && low[v] >= disc[u]) {
        ap[u] = true;
      }
    } else {
      if (v != parent[u]) {
        low[u] = min(low[u], disc[v]);
      }
    }
  }
}

int main() {
  // Create graphs given in above diagrams
  cout << "\nArticulation points in first graph \n";
  Graph g1(5);
  g1.AddEdge(1, 0);
  g1.AddEdge(0, 2);
  g1.AddEdge(2, 1);
  g1.AddEdge(0, 3);
  g1.AddEdge(3, 4);
  g1.AP();
 
  cout << "\nArticulation points in second graph \n";
  Graph g2(4);
  g2.AddEdge(0, 1);
  g2.AddEdge(1, 2);
  g2.AddEdge(2, 3);
  g2.AP();
 
  cout << "\nArticulation points in third graph \n";
  Graph g3(7);
  g3.AddEdge(0, 1);
  g3.AddEdge(1, 2);
  g3.AddEdge(2, 0);
  g3.AddEdge(1, 3);
  g3.AddEdge(1, 4);
  g3.AddEdge(1, 6);
  g3.AddEdge(3, 5);
  g3.AddEdge(4, 5);
  g3.AP();
 
  return 0;
}
