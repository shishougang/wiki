#include <iostream>

using namespace std;

struct Node {
  int key, height;
  struct Node *left, *right;
  int size;
};

int Height(struct Node *node) {
  if (node == NULL) {
    return 0;
  }
  return node->height;
}

int Size(struct Node *node) {
  if (node == NULL) {
    return 0;
  }
  return node->size;
}

struct Node* NewNode(int key) {
  struct Node* node = new Node;
  node-> key = key;
  node->left = node->right = NULL;
  node->height = node->size = 1;
  return node;
}

int GetBalance(struct Node *node) {
  if (node == NULL) {
    return 0;
  }
  return Height(node->left) - Height(node->right);
}

struct Node* RightRotate(struct Node *y) {
  struct Node *x = y->left;
  struct Node *t = x->right;
  x->right = y;
  y->left = t;
  y->height = max(Height(y->left), Height(y->right)) + 1;
  x->height = max(Height(x->left), Height(x->right)) + 1;

  y->size = Size(y->left) + Size(y->right) + 1;
  x->size = Size(x->left) + Size(x->right) + 1;
  return x;
}

struct Node* LeftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *t = y->left;
  y->left = x;
  x->right = t;
  x->height = max(Height(x->left), Height(x->right)) + 1;
  y->height = max(Height(y->left), Height(y->right)) + 1;

  x->size = Size(x->left) + Size(x->right) + 1;
  y->size = Size(y->left) + Size(y->right) + 1;
  return y;
}

struct Node* Insert(struct Node *node, int key, int *result) {
  if (node == NULL) {
    return NewNode(key);
  }
  if (key < node->key) {
    node->left = Insert(node->left, key, result);
    *result = *result + Size(node->right) + 1;
  } else {
    node->right = Insert(node->right, key, result);
  }
  node->height = max(Height(node->left), Height(node->right)) + 1;
  node->size = Size(node->left) + Size(node->right) + 1;
  int balance = GetBalance(node);
  // Left Left case
  if (balance > 1 && key < node->left->key) {
    return RightRotate(node);
  }
  // Right Right Case
  if (balance < -1 && key > node->right->key) {
    return LeftRotate(node);
  }
  // Left Right Case
  if (balance > 1 && key > node->left->key) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }
  // Right Left Case
  if (balance < -1 && key < node->right->key) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

int GetInvCount(int *arr, int n) {
  struct Node *root = NULL;
  int result = 0;
  for (int i = 0; i < n; ++i) {
    root = Insert(root, arr[i], &result);
  }
  return result;
}

int main() {
  int arr[] = {8, 4, 2, 1};
  int n = sizeof(arr)/sizeof(int);
  cout << "Number of inversions count are : "
       << GetInvCount(arr,n);
  return 0;
}
