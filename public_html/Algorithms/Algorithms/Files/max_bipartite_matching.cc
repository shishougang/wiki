#include <cstring>
#include <iostream>

using namespace std;

#define M 6
#define N 6

// A DFS based recursive function that returns true if a
// matching for vertex u is possible
bool Bpm(bool bp_graph[M][N], int u, bool *seen, int *match_r) {
  for (int v = 0; v < N; ++v) {
    if (bp_graph[u][v] && !seen[v]) {
      seen[v] = true;
      // If job 'v' is not assigned to an applicant OR
      // previously assigned applicant for job v (which is matchR[v]) 
      // has an alternate job available.
      if (match_r[v] < 0 || Bpm(bp_graph, match_r[v], seen, match_r)) {
          match_r[v] = u;
          return true;
      }
    }
  }
  return false;
}

int MaxBPM(bool bp_graph[M][N]) {
  // An array to keep track of the applicants assigned to jobs.
  int match_r[N];
  memset(match_r, -1, sizeof(match_r));
  int result = 0;
  for (int u = 0; u < M; ++u) {
    bool seen[N];
    memset(seen, 0, sizeof(seen));
    if (Bpm(bp_graph, u, seen, match_r)) {
      ++result;
    }
  }
  return result;
}

int main() {
  bool bp_graph[M][N] = {{0, 1, 1, 0, 0, 0},
                        {1, 0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 1}};
 
  cout << "Maximum maching is "
       << MaxBPM(bp_graph) << endl;
  return 0;
}
