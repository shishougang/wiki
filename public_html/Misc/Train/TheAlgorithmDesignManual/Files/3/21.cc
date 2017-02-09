
struct Node {
  int value;
  Node *left;
  Node *right;
};

bool CompareBinaryTree(Node *head_m, Node *head_n) {
  if (head_m == NULL && head_n == NULL) {
    return true;
  }
  if (head_m == NULL || head_n == NULL) {
    return false;
  }
  return (head_m->value == head_n->value) &&
      CompareBinaryTree(head_m->left, head_n->left) &&
      CompareBinaryTree(head_m->right, head_n->right);
}
  
