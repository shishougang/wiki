#include <iostream>
#include <vector>
#include <list>
#include <limits>

using namespace std;

struct Edge {
  int v;
  int flow;
  int c;
};

class Graph {
 public:
  Graph(int V);
  void AddEdge(int u, int v, int c);
  bool BFS(int s, int t);
  int SendFlow(int u, int flow, int t, int *start);
  int DinicMaxFlow(int s, int t);
 private:
  int V;
  int *level;
  vector<Edge> *adj;
};

Graph::Graph(int V) {
  adj = new vector<Edge>[V];
  this->V = V;
  level = new int[V];
}

void Graph::AddEdge(int u, int v, int c) {
  // Forward edge : 0 flow and c capacity
  Edge a{v, 0, c};
  // Back edge : 0 flow and 0 capacity
  Edge b{u, 0, 0};
  adj[u].push_back(a);
  adj[v].push_back(b);
}

bool Graph::BFS(int s, int t) {
  for (int i = 0; i < V; ++i) {
    level[i] = -1;
  }
  level[s] = 0;
  list<int> q;
  q.push_back(s);
  vector<Edge>::iterator it;
  while (!q.empty()) {
    int u = q.front();
    q.pop_front();
    for (it = adj[u].begin(); it != adj[u].end(); ++it) {
      Edge &e = *it;
      if (level[e.v] < 0 && e.flow < e.c) {
        level[e.v] = level[u] + 1;
        q.push_back(e.v);
      }
    }
  }
  // IF we can not reach to the sink we
  // return false else true
  return level[t] < 0 ? false : true;
}

// A DFS based function to send flow after BFS has
// figured out that there is a possible flow and
// constructed levels. This function called multiple
// times for a single call of BFS.
// flow: Current flow send by parent function call
// start[]: To keep track of next edge to be explored.
//           start[i] stores  count of edges explored
//           from i.
//  u: Current vertex
//  t: Sink
int Graph::SendFlow(int u, int flow, int t, int *start) {
  if (u == t) {
    return flow;
  }
  for (; start[u] < adj[u].size(); start[u]++) {
    Edge &e = adj[u][start[u]];
    if (level[e.v] == level[u]+1 && e.flow < e.c) {
      int curr_flow = min(flow, e.c - e.flow);
      int temp_flow = SendFlow(e.v, curr_flow, t, start);
      if (temp_flow > 0) {
        // add flow  to current edge
        e.flow += temp_flow;
        return temp_flow;
      }
    }
  }
  return 0;
}

int Graph::DinicMaxFlow(int s, int t) {
  if (s == t) {
    return -1;
  }
  int total = 0;
  while (BFS(s , t) == true) {
    int *start = new int[V+1];
    while (int flow = SendFlow(s, numeric_limits<int>::max(), t, start)) {
      total += flow;
    }
  }
  return total;
}

int main() {
  Graph g(6);
  g.AddEdge(0, 1, 16 );
  g.AddEdge(0, 2, 13 );
  g.AddEdge(1, 2, 10 );
  g.AddEdge(1, 3, 12 );
  g.AddEdge(2, 1, 4 );
  g.AddEdge(2, 4, 14);
  g.AddEdge(3, 2, 9 );
  g.AddEdge(3, 5, 20 );
  g.AddEdge(4, 3, 7 );
  g.AddEdge(4, 5, 4);
  cout << "Maximum flow " << g.DinicMaxFlow(0, 5) << endl;
  return 0;
}
