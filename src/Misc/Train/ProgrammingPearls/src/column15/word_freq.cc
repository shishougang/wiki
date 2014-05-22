#include <iostream>  // NOLINT
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;

typedef struct Node* Nodeptr;
struct Node {
  Node(string inword, int incount, Nodeptr innext) {
    word = inword;
    count = incount;
    next = innext;
  }
  string word;
  int count;
  Nodeptr next;
};

#define NHASH 29989
#define MULT 31
Nodeptr bin[NHASH];

unsigned int Hash(const string &str) {
  unsigned int h = 0;
  for (string::const_iterator it = str.begin(); it != str.end(); ++it) {
    h = MULT * h + *it;
  }
  return h % NHASH;
}

void InWord(const string &str) {
  Nodeptr p;
  int h;
  h = Hash(str);
  for (p = bin[h]; p != NULL; p = p->next) {
    if (str.compare(p->word) == 0) {
      (p->count)++;
      return;
    }
  }
  p = new Node(str, 1, bin[h]);
  bin[h] = p;
}

int main(int argc, char *argv[]) {
  string str;
  int i;
  for (i = 0; i < NHASH; ++i) {
    bin[i] = NULL;
  }
  while (cin >> str) {
    InWord(str);
  }
  for (i = 0; i < NHASH; ++i) {
    for (Nodeptr p = bin[i]; p != NULL; p = p->next) {
      cout << p->word << " " << p->count << endl;
    }
  }
  return 0;
}
