#include <iostream>
#include <list>

using namespace std;

class Graph {
 private:
  int v;
  list<int> *adj;

  void DFSHelper(int s, bool *visited);
 public:
  Graph(int v);
  void AddEdge(int v, int w);
  /* print DFS from a given source s */
  void DFS(int s);
};

Graph::Graph(int v) {
  this->v = v;
  adj = new list<int>[v];
}

void Graph::AddEdge(int v, int w) {
  adj[v].push_back(w);
}

void Graph::DFSHelper(int s, bool *visited) {
  visited[s] = true;
  cout << s << " ";
  list<int>::iterator it;
  for (it = adj[s].begin(); it != adj[s].end(); ++it) {
    if (!visited[*it]) {
      DFSHelper(*it, visited);
    }
  }
}

void Graph::DFS(int s) {
  bool *visited = new bool[v];
  for (int i = 0; i < v; ++i) {
    visited[i] = false;
  }
  DFSHelper(s, visited);
}

int main() {
  Graph g(4);
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);
  g.AddEdge(2, 3);
  g.AddEdge(3, 3);
  cout << "Following is Depth First Traversal (starting from vertex 2) \n";
  g.DFS(2);
  cout << endl;
  return 0;
}
