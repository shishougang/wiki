#include <iostream>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

// Max number of states in the matching machine.
const int MAXS = 500;
// Maximum number of characters in input alphabet
const int MAXC = 26;

// Bit i in this mask is one if the word with index i
// appears when the machine enters this state.
int out[MAXS];

// FAILURE FUNCTION
int f[MAXS];

int g[MAXS][MAXC];

void BuildMatchingMachine(const string* arr, int k) {
  memset(out, 0, sizeof(out));
  memset(g, -1, sizeof(g));
  int states = 1;
  for (int i = 0; i < k; ++i) {
    const string &word = arr[i];
    int current_state = 0;
    for (int j = 0; j < word.size(); ++j) {
      int ch = word[j] - 'a';
      if (g[current_state][ch] == -1) {
        g[current_state][ch] = states++;
      }
      current_state = g[current_state][ch];
    }
    out[current_state] |= (1 << i);
  }
  // For all characters which don't have an edge from
  // root (or state 0) in Trie, add a goto edge to state
  // 0 itself
  for (int ch = 0; ch < MAXC; ++ch) {
    if (g[0][ch] == -1) {
      g[0][ch] = 0;
    }
  }
  memset(f, -1, sizeof(f));
  queue<int> q;
  for (int ch = 0; ch < MAXC; ++ch) {
    // All nodes of depth 1 have failure function value
    // as 0. For example, in above diagram we move to 0
    // from states 1 and 3.
    if (g[0][ch] != 0) {
      f[g[0][ch]] = 0;
      q.push(g[0][ch]);
    }
  }
  while (q.size()) {
    int state = q.front();
    q.pop();
    // For the removed state, find failure function for
    // all those characters for which goto function is
    // not defined.
    for (int ch = 0; ch <= MAXC; ++ch) {
      // If goto function is defined for character 'ch'
      // and 'state'
      if (g[state][ch] != -1) {
        int failure = f[state];
        // Find the deepest node abeled by proper
        // suffix of string from root to current state.
        while (g[failure][ch] == -1) {
          failure = f[failure];
        }
        failure = g[failure][ch];
        f[g[state][ch]] = failure;
        out[g[state][ch]] |= out[failure];
        q.push(g[state][ch]);
      }
    }
  }
}


int FindNextState(int current_state, char next) {
  int answer = current_state;
  int ch = next - 'a';
  while (g[answer][ch] == -1) {
    answer = f[answer];
  }
  return g[answer][ch];
}

void SearchWords(const string& text, const string* arr, int k) {
    BuildMatchingMachine(arr, k);
    int current_state = 0;
    for (int i = 0; i < text.size(); ++i) {
      current_state = FindNextState(current_state, text[i]);
      if (out[current_state] == 0) {
        continue;
      }
      for (int j = 0; j < k; ++j) {
        if (out[current_state] & (1 << j)) {
          cout << "Word " << arr[j] << " appears from "
               << i - arr[j].size() + 1 << " to " << i << endl;
        }
      }
    }
}

int main() {
  string arr[] = {"he", "she", "hers", "his"};
  string text = "ahishers";
  int k = sizeof(arr)/sizeof(arr[0]);
  SearchWords(text, arr, k);
  return 0;
}
