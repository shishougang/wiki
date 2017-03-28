#include <iostream>
#include <limits>
using namespace std;

#define INT_SIZE 32

struct TrieNode {
  int value;
  TrieNode *arr[2];
};

TrieNode *NewNode() {
  TrieNode *temp = new TrieNode;
  temp->value = 0;
  temp->arr[0] = temp->arr[1] = NULL;
  return temp;
}

void Insert(TrieNode *root, int pre_xor) {
  TrieNode *temp = root;
  for (int i = INT_SIZE - 1; i >= 0; --i) {
    bool val = pre_xor & (1 << i);
    if (temp->arr[val] == NULL) {
      temp->arr[val] = NewNode();
    }
    temp = temp->arr[val];
  }
  temp->value = pre_xor;
}

int Query(TrieNode *root, int pre_xor) {
  TrieNode *temp = root;
  for (int i = INT_SIZE - 1; i >= 0; --i) {
    bool val = pre_xor & (1 << i);
    // first look for a prefix that has opposite bit
    if (temp->arr[1-val] != NULL) {
      temp = temp->arr[1-val];
    } else if (temp->arr[val] != NULL) {
      temp = temp->arr[val];
    }
  }
  return pre_xor ^ (temp->value);
}

int MaxSubarrayXOR(int *arr, int n) {
  TrieNode *root = NewNode();
  Insert(root, 0);
  int result = numeric_limits<int>::min(), pre_xor = 0;
  for (int i = 0; i < n; ++i) {
    pre_xor = pre_xor ^ arr[i];
    Insert(root, pre_xor);
    result = max(result, Query(root, pre_xor));
  }
  return result;
}

int main() {
  int arr[] = {8, 1, 2, 12};
  int n = sizeof(arr)/sizeof(arr[0]);
  cout << "Max subarray XOR is " << MaxSubarrayXOR(arr, n) << endl;
  return 0;
}
