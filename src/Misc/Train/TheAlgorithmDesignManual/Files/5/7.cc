
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

const int kMax = 256;
int map_index[kMax];

void MapToIndex(int inorder[], int n) {
  for (int i = 0; i < n; ++i) {
    map_index[inorder[i]] = i;
  }
}

Node *BuildInorderPreorder(in in[], in pre[], int n, int offset) {
  if (n == 0) {
    return NULL:
  }
  int root_val = pre[0];
  int i = map_index[root_val] - offset;
  Node *root = new Node(root_val);
  root->left = BuildInorderPreorder(in, pre+1, i, offset);
  root->right = BuildInorderPreorder(in+i+1, pre+i+1, offset+i+1);
  return root;
}
