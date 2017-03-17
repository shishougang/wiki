#include <iostream>
#include <limits>

using namespace std;

struct Node {
  int data;
  struct Node* left, *right;
};

struct Node* NewNode(int data) {
  struct Node* new_node = new Node;
  new_node->data = data;
  new_node->left = new_node->right = NULL;
  return new_node;
}

int FindMaxHelper(struct Node* root, int *res) {
  if (root == NULL) {
    return 0;
  }
  int l = FindMaxHelper(root->left, res);
  int r = FindMaxHelper(root->right, res);
  // This path must include at-most one child of root
  int max_single = max(max(l, r) + root->data, root->data);
  int max_root = max((l + r + root->data), max_single);
  *res = max(*res, max_root);
  return max_single;
}

int FindMaxSum(struct Node* root) {
  int res = numeric_limits<int>::min();
  FindMaxHelper(root, &res);
  return res;
}

int main(void) {
  struct Node *root = NewNode(10);
  root->left        = NewNode(2);
  root->right       = NewNode(10);
  root->left->left  = NewNode(20);
  root->left->right = NewNode(1);
  root->right->right = NewNode(-25);
  root->right->right->left   = NewNode(3);
  root->right->right->right  = NewNode(4);
  cout << "Max path sum is " << FindMaxSum(root) << endl;;
  return 0;
}
