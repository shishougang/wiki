#include <iostream>  // NOLINT
using std::cout;
using std::endl;
#include <queue>
using std::priority_queue;
#include <utility>
using std::make_pair;
using std::pair;
#include <vector>
using std::vector;
#include <algorithm>
using std::max;
using std::min;
#include <limits>
using std::numeric_limits;


int FindSmallestSnippet(vector<vector<int> > &index_positions) {
  // max-priority, select smallest position, use -index_positions[i][j], (i,j)
  priority_queue<pair<int, pair<int ,int> > > queue;
  int max_pos = 0; // the max pos of  the snippet
  int i;
  for (i = 0; i < index_positions.size(); ++i) {
    int pos = index_positions[i][0];
    max_pos = max(max_pos, pos);
    queue.push(make_pair(-pos, make_pair(i, 0)));
  }
  int smallest_len = numeric_limits<int>::max();
  while (queue.size() == index_positions.size()) {
    int min_pos = -queue.top().first;
    smallest_len = min(smallest_len, max_pos - min_pos + 1);
    int word_pos = queue.top().second.first;
    int index = queue.top().second.second;
    queue.pop();
    ++index;
    if (index < index_positions[word_pos].size()) {
      int next_pos = index_positions[word_pos][index];
      max_pos = max(max_pos, next_pos);
      queue.push(make_pair(-next_pos, make_pair(word_pos, index)));
    }
  }
  return smallest_len;
}
  
int main(int argc, char *argv[]) {
  int data[][3] = {{1, 4, 5}, {4, 9, 10}, {5, 6, 15}};
  vector<vector<int> > index_positions;
  for (int i = 0; i < 3; i++) {
    index_positions.push_back(vector<int>(data[i], data[i] + 3));
  }
  cout << FindSmallestSnippet(index_positions) << endl;
  return 0;
}
