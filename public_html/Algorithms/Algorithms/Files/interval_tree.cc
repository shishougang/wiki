#include <iostream>

using namespace std;

struct Interval {
  int low, high;
};

struct Node {
  Interval *i;
  int max;
  Node *left, *right;
};

Node* NewNode(const Interval& i) {
  Node *temp = new Node;
  temp->i = new Interval(i);
  temp->max = i.high;
  temp->left = temp->right = NULL;
  return temp;
}

Node* Insert(Node *root, const Interval &i) {
  if (root == NULL) {
    return NewNode(i);
  }
  int l = root->i->low;
  if (i.low < l) {
    root->left = Insert(root->left, i);
  } else {
    root->right = Insert(root->right, i);
  }
  if (root->max < i.high) {
    root->max = i.high;
  }
  return root;
}

bool Overlap(const Interval &i1, const Interval &i2) {
  if (i2.low >= i1.low && i2.low <= i1.high) {
    return true;
  } else if (i2.high >= i1.low && i2.high <= i1.high) {
    return true;
  }
  return false;
}

Interval* OverlapSearch(const Node *root, const Interval &i) {
  if (root == NULL) {
    return NULL;
  }
  if (Overlap(*(root->i), i)) {
    return root->i;
  }
  if (root->left != NULL && root->left->max >= i.low) {
    return OverlapSearch(root->left, i);
  }
  return OverlapSearch(root->right, i);
}

  
int main() {
  Interval ints[] = {{15, 20}, {10, 30}, {17, 19},
                     {5, 20}, {12, 15}, {30, 40}};
  int n = sizeof(ints)/sizeof(ints[0]);
  Node *root = NULL;
  for (int i = 0; i < n; i++) {
    root = Insert(root, ints[i]);
  }
  Interval x = {6, 7};
  cout << "Searching for interval [" << x.low << "," << x.high << "]";
  Interval *res = OverlapSearch(root, x);
  if (res == NULL) {
    cout << "\nNo Overlapping Interval";
  } else {
    cout << "\nOverlaps with [" << res->low << ", " << res->high << "]";
  }
  return 0;
}
