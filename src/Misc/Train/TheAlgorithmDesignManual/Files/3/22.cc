#include <iostream>  // NOLINT
using std::cout;
using std::endl;

struct Node {
  int value;
  Node *next;
};

struct TNode {
  int value;
  TNode *left;
  TNode *right;
  TNode(int value_in) {
    value = value_in;
    left = NULL;
    right = NULL;
  }
};

void InsertToList(Node **head, int value) {
  Node *new_node = new Node;
  new_node->value = value;
  new_node->next = *head;
  *head = new_node;
}

void ConvertTreeToList(const TNode *root, Node **head) {
  if (root == NULL) {
    return;
  }
  ConvertTreeToList(root->right, head);
  InsertToList(head, root->value);
  ConvertTreeToList(root->left, head);
}

void PrintList(const Node *head) {
  const Node *p = head;
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;
}

int main(int argc, char *argv[])
{
  Node *head = NULL;
  TNode *left = new TNode(1);
  TNode *right = new TNode(3);
  TNode *root = new TNode(2);
  root->left = left;
  root->right = right;
  ConvertTreeToList(root, &head);
  PrintList(head);
  return 0;
}

