#include <cstdio>
#include <climits>

#define V 4
#define INF 9999

void PrintSolution(int dist[][V]) {
  printf ("Following matrix shows the shortest distances"
          " between every pair of vertices \n");
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      if (dist[i][j] == INF)
        printf("%7s", "INF");
      else
        printf ("%7d", dist[i][j]);
    }
    printf("\n");
  }
}
 
void FloydWarshall(int graph[][V]) {
  int dist[V][V], i, j , k;
  for (i = 0; i < V; ++i) {
    for (j = 0; j < V; ++j) {
      dist[i][j] = graph[i][j];
    }
  }
  for (k = 0; k < V; ++k) {
    for (i = 0; i < V; ++i) {
      for (j = 0; j < V; ++j) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
  PrintSolution(dist);
}

int main() {
  /* Let us create the following weighted graph
            10
       (0)------->(3)
        |         /|\
      5 |          |
        |          | 1
       \|/         |
       (1)------->(2)
            3           */
  int graph[V][V] = { {0,   5,  INF, 10},
                      {INF, 0,   3, INF},
                      {INF, INF, 0,   1},
                      {INF, INF, INF, 0} };
 
  FloydWarshall(graph);
  return 0;
}
