#include <iostream>  // NOLINT
using std::cout;
using std::endl;

struct Node {
  int val;
  struct Node* left;
  struct Node* right;
  Node(int val_in) {
    val = val_in;
    left = NULL;
    right = NULL;
  }
};

bool FindIthElementCore(struct Node *root, int ith, int *index, int *value) {
  if (root == NULL) {
    return false;
  }
  if (FindIthElementCore(root->left, ith, index, value)) {
    return true;
  }
  cout << ith << ": " << *index << ": " << root->val << endl;
  if (ith == *index) {
    *value = root->val;
    return true;
  }
  (*index)++;
  if (FindIthElementCore(root->right, ith, index, value)) {
    return true;
  } else {
    return false;
  }
}

bool FindIthElement(struct Node *root, int ith, int *value) {
  int start = 0;
  return FindIthElementCore(root, ith, &start, value);
}

int main(int argc, char *argv[]) {
  struct Node *root, *p;
  root = new Node(2);
  root->left = new Node(1);
  root->right = new Node(3);
  int res;
  if (FindIthElement(root, 2, &res)) {
    cout << res << endl;
  }
  return 0;
}
