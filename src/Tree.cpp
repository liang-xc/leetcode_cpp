#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) 
    : val(x), left(left), right(right) {}
};

//144. Binary Tree Preorder Traversal
//preorder: mid -> left -> right
//recursive version
#define RECURSIVE 0
#if RECURSIVE
void _preorder(TreeNode* curr, std::vector<int>& vec) {
  if (curr == nullptr) return;
  vec.push_back(curr->val);
  _preorder(curr->left, vec);
  _preorder(curr->right, vec);
}

std::vector<int> preorderTraversal(TreeNode* root) {
  std::vector<int> result;
  _preorder(root, result);
  return result;
}
#endif
//iterative version
#if not RECURSIVE
std::vector<int> preorderTraversal(TreeNode* root) {
  std::stack<TreeNode*> stk;
  std::vector<int> result;
  if (root == nullptr) return result;
  stk.push(root);
  while(!stk.empty()) {
    TreeNode* node = stk.top();
    stk.pop();
    result.push_back(node->val);
    if(node->right) stk.push(node->right);
    if(node->left) stk.push(node->left);
  }
  return result;
}
#endif

//145. Binary Tree Postorder Traversal
//postorder: left -> right -> mid
//recursive version
#if RECURSIVE
void _postorder(TreeNode* curr, std::vector<int>& vec) {
  if(curr == nullptr) return;
  _postorder(curr->left, vec);
  _postorder(curr->right, vec);
  vec.push_back(curr->val);
}

std::vector<int> postorderTraversal(TreeNode* root) {
  std::vector<int> result;
  _postorder(root, result);
  return result;
}
#endif
//iterative version
#if not RECURSIVE
std::vector<int> postorderTraversal(TreeNode* root) {
  // do mid -> right -> left, then reverse
  std::vector<int> result;
  std::stack<TreeNode*> stk;
  if(root == nullptr) return result;
  stk.push(root);
  while(!stk.empty()) {
    TreeNode* node = stk.top();
    stk.pop();
    result.push_back(node->val);
    if(node->left) stk.push(node->left);
    if(node->right) stk.push(node->right);
  }
  std::reverse(result.begin(), result.end());
  return result;
}
#endif

//94. Binary Tree Inorder Traversal
//inorder: left -> mid -> right
//recursive version
#if RECURSIVE
void _inorder(TreeNode* curr, std::vector<int> vec) {
  if(curr == nullptr) return;
  vec.pushback(curr->val);
  _inorder(curr->left);
  _inorder(curr->right);
}

std::vector<int> inorderTraversal(TreeNode* root) {
  std::vector<int> result;
  _inorder(root, result);
  return result;
}
#endif
//iterative version
#if not RECURSIVE
std::vector<int> inorderTraversal(TreeNode* root) {
  std::vector<int> result;
  std::stack<TreeNode*> stk;
  TreeNode* curr = root;
  while (curr != nullptr || !stk.empty()) {
    if (curr != nullptr) {
      stk.push(curr);
      curr = curr->left;
    } else {
      curr = stk.top();
      stk.pop();
      result.push_back(curr->val);
      curr = curr->right;
    }
  }
  return result;
}
#endif

//102. Binary Tree Level Order Traversal
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
  std::vector<std::vector<int>> result;
  std::queue<TreeNode*> q;
  if (root != nullptr) q.push(root);

  while (!q.empty()) {
    int n = q.size();
    std::vector<int> curr;
    for (int i = 0; i < n; ++i) {
      TreeNode* p = q.front();
      q.pop();
      if (p != nullptr) {
        curr.push_back(p->val);
        q.push(p->left);
        q.push(p->right);
      }
    }

    if (!curr.empty()) {
      result.push_back(curr);
    }
  }
  return result;
}

//226. Invert Binary Tree
TreeNode* invertTree(TreeNode* root) {
  if (root == nullptr) return root;
  std::swap(root->left, root->right);
  invertTree(root->left);
  invertTree(root->right);
  return root;
}

//101. Symmetric Tree
#if RECURSIVE
bool compare(TreeNode* left, TreeNode* right) {
  if (left == nullptr && right != nullptr) return false;
  else if (left != nullptr && right == nullptr) return false;
  else if (left == nullptr && right == nullptr) return true;
  else if (left->val != right->val) return false;
  else return compare(left->left, right->right) && compare(left->right, right->left);
}
bool isSymmetric(TreeNode* root) {
  if (root == nullptr) return true;
  return compare(root->left, root->right);
}
#endif
#if not RECURSIVE
bool isSymmetric(TreeNode* root) {
  if (root == nullptr) return true;
  std::queue<TreeNode*> q;
  q.push(root->left);
  q.push(root->right);

  while(!q.empty()) {
    TreeNode* l = q.front();
    q.pop();
    TreeNode* r = q.front();
    q.pop();
    if (l == nullptr && r == nullptr) {
      continue;
    } else if (l == nullptr || r == nullptr || l->val != r->val) {
      return false;
    } else {
      q.push(l->left);
      q.push(r->right);
      q.push(l->right);
      q.push(r->left);
    }
  }
  return true;
}
#endif

//100. Same Tree
bool isSameTree(TreeNode* p, TreeNode* q) {
  std::queue<TreeNode*> que;
  que.push(p);
  que.push(q);
  while (!que.empty()) {
    TreeNode* l = que.front();
    que.pop();
    TreeNode* r = que.front();
    que.pop();
    if (l == nullptr && r == nullptr) continue;
    else if (l == nullptr || r == nullptr || l->val != r->val) return false;
    else {
      que.push(l->left);
      que.push(r->left);
      que.push(l->right);
      que.push(r->right);
    }
  }
  return true;
}

//104. Maximum Depth of Binary Tree
int maxDepth(TreeNode* root) {
  if (root == nullptr) return 0;
  return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

//111. Minimum Depth of Binary Tree
int minDepth(TreeNode* root) {
  if (root == nullptr) return 0;
  if (root->left == nullptr && root->right != nullptr) return 1 + minDepth(root->right);
  if (root->left != nullptr && root->right == nullptr) return 1 + minDepth(root->left);
  else return 1 + std::min(minDepth(root->left), minDepth(root->right));
}

//222. Count Complete Tree Nodes
int countNodes(TreeNode* root) {
  if (root == nullptr) return 0;
  return 1 + countNodes(root->left) + countNodes(root->right);
}

//110. Balanced Binary Tree
int getHeight(TreeNode* node) {
  // a comparasion between heights -> postorder traversal
  if (node == nullptr) return 0;
  int lHeight = getHeight(node->left);
  int rHeight = getHeight(node->right);
  if (lHeight == -1 || rHeight == -1) return -1;
  return abs(lHeight - rHeight) > 1 ? -1 : 1 + std::max(lHeight, rHeight);
}

bool isBalanced(TreeNode* root) {
  return getHeight(root) != -1;
}

//TODO
//257. Binary Tree Paths
void recordTraversal(TreeNode* curr, std::string path, std::vector<std::string>& path_vec) {
  path += std::to_string(curr->val);
  if (curr->left == nullptr && curr->right == nullptr) {
    path_vec.push_back(path);
    return;
  } else if (curr->left != nullptr) {
    path += "->";
    recordTraversal(curr->left, path, path_vec);
  } else if (curr->right != nullptr) {
    path += "->";
    recordTraversal(curr->right, path, path_vec);
  }
}

std::vector<std::string> binaryTreePaths(TreeNode* root) {
  std::vector<std::string> result;
  std::string path;
  if (root == nullptr) return result;
  recordTraversal(root, path, result);
  return result;
}
