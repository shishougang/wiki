#include <iostream>  // NOLINT
using std::cout;
using std::endl;

struct Node {
  int value;
  Node *next;
};

Node* FindMidNode(Node *head) {
  Node *p, *q;
  p = head;
  q = head;
  i = 0;
  while (p != NULL) {
    i++;
    p = p->next;
    if (i == 2) {
      q = q->next;
      i = 0;
    }
  }
  return q;
}
