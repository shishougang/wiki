#include <iostream>
#include <list>

using namespace std;

class Graph {
 private:
  int v;
  list<int> *adj;
 public:
  Graph(int v);
  void AddEdge(int v, int w);
  /* print BFS from a given source s */
  void BFS(int s);
};

Graph::Graph(int v) {
  this->v = v;
  adj = new list<int>[v];
}

void Graph::AddEdge(int v, int w) {
  adj[v].push_back(w);
}

void Graph::BFS(int s) {
  bool *visited = new bool[v];
  for (int i = 0; i < v; ++i) {
    visited[i] = false;
  }
  list<int> queue;
  visited[s] = true;
  queue.push_back(s);

  list<int>::iterator it;
  int node;
  while (!queue.empty()) {
    node = queue.front();
    cout << node << " ";
    queue.pop_front();

    for (it = adj[node].begin(); it != adj[node].end(); ++it) {
      if (!visited[*it]) {
        visited[*it] = true;
        queue.push_back(*it);
      }
    }
  }
  cout << endl;
  delete[] visited;
}

int main() {
  Graph g(4);
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);
  g.AddEdge(2, 3);
  g.AddEdge(3, 3);
 
  cout << "Following is Breadth First Traversal "
       << "(starting from vertex 2) \n";
  g.BFS(2);
 
  return 0;
}
