#include <iostream>  // NOLINT
using std::cout;
using std::endl;

struct Node {
  int value;
  struct Node *next;
  Node(int in_value, struct Node* in_next) : value(in_value), next(in_next) {
  }
};

void ReverseLinkedList(Node **head) {
  if (!head || *head == NULL) {
    return;
  }
  Node *prev, *p, *next;
  prev = *head;
  p = prev->next;
  prev->next = NULL;
  while (p != NULL) {
    next = p->next;
    p->next = prev;
    prev = p;
    p = next;
  }
  *head = prev;
}

void PrintLinkedList(const Node *head) {
  const Node *p = head;
  while (p != NULL) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;
}

int main(int argc, char *argv[])
{
  int i;
  const int kMaxN = 10;
  Node *head;
  head = new Node(0, NULL);
  Node *p, *q;
  p = head;
  for (i = 1; i < kMaxN; ++i) {
    q = new Node(i, NULL);
    p->next = q;
    p = q;
  }
  PrintLinkedList(head);
  ReverseLinkedList(&head);
  PrintLinkedList(head);
  return 0;
}
