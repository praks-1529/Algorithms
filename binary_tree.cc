#include<iostream>
#include <assert.h>
#include <queue>
#include <stack>
using namespace std;

class node {
  public:
    node(int data) : data_(data), left_(NULL), right_(NULL) { }
    node *left_;
    node* right_;
    int data_;
};

class BinaryTree {
  public:
    node *root_;
    void insert_node(int data, int parent, int left) {
      if(root_ == NULL) {
        root_ = new node(data);
        return;
      } else {
        node *x = find_node(root_, parent);
        if(x == NULL) {
          cout << "ERROR: Cannot find node " << parent <<  endl;
          return;
        }
        if(left) {
          assert(x->left_ == NULL);
          x->left_ = new node(data);
        } else {
          assert(x->right_ == NULL);
          x->right_ = new node(data);
        }
      }
    }

    node* find_node(node *x, int key) {
      if(x == NULL) return NULL;
      if(x->data_ == key) {
        return x;
      } else {
        node *left  = find_node(x->left_, key);
        if(left) return left;
        node *right = find_node(x->right_, key);
        if(right) return right;
        return NULL;
      }
    }

    void inOrderLow(node *x) {
      if(x == NULL) return;
      inOrderLow(x->left_);
      cout << x->data_ << endl;
      inOrderLow(x->right_);
    }

    void inOrder() {
      inOrderLow(root_);
    }

    void LevelOrder() {
      queue<node*> node_queue;
      queue<int> level_queue;
      node_queue.push(root_);
      level_queue.push(0);      
      while(!node_queue.empty()) {
        node *x = node_queue.front();
        int level = level_queue.front();
        node_queue.pop();
        level_queue.pop();
        cout << x->data_ << endl;
        if(x->left_) {
          node_queue.push(x->left_);
          level_queue.push(level+1);
        }
        if(x->right_) {
          node_queue.push(x->right_);
          level_queue.push(level+1);
        }
      }
    }

    void RightNode(int key) {
      queue<node*> node_queue;
      queue<int> level_queue;
      node_queue.push(root_);
      level_queue.push(0);      
      node *final_node = NULL;
      while(!node_queue.empty()) {
        node *x = node_queue.front();
        int level = level_queue.front();
        node_queue.pop();
        level_queue.pop();
        if(x->data_ == key) {
          int next_level = level_queue.front();
          if(next_level == level) {
            final_node = node_queue.front();
          } else {
            break;
          }
        } else {
          if(x->left_) {
            node_queue.push(x->left_);
            level_queue.push(level+1);
          }
          if(x->right_) {
            node_queue.push(x->right_);
            level_queue.push(level+1);
          }
        }
      }
      if(final_node) {
        cout << "Right node of " << key << " is " << final_node->data_ << endl;
      } else {
        cout << "Right node not found" << endl;
      }
    }
    
    node* DeepestNodeLow(node *x, int cur_level, int &deep_level) {
      node *left, *right;
      int left_l, right_l;
      left_l = right_l = cur_level;
      left = right = NULL;
      if(x->left_) {
        left = DeepestNodeLow(x->left_, cur_level+1, left_l);
      }
      if(x->right_) {
        right = DeepestNodeLow(x->right_, cur_level+1, right_l);
      }
      if(!left && !right) {
        deep_level = cur_level;
        return x;
      }
      bool isLeftMore = (left_l > right_l) ? true: false;
      if(isLeftMore) {
        deep_level = left_l;
        return left;
      } else {
        deep_level = right_l;
        return right;
      }
    }

    void DeepestNode() {
      int level;
      node *x = DeepestNodeLow(root_, 1, level);
      if(x) {
        cout << "Deepest node is " << x->data_ << " at level " << level << endl;
      } 
    }

    void printAllRootLeafPathLow(node *x, stack<node*> &stk) {
      if(!x->left_ && !x->right_) {
        stack<node*> tmp = stk;
        tmp.push(x);
        while(!tmp.empty()) {
          node *y = tmp.top();
          cout << y->data_ << " " ;
          tmp.pop();
        }
        cout << endl;
        return;
      } else {
        stk.push(x);
        if(x->left_) {
          printAllRootLeafPathLow(x->left_, stk);
        }
        if(x->right_) {
          printAllRootLeafPathLow(x->right_, stk);
        }
        stk.pop();
      }
    }
    void printAllRootLeafPath() {
      stack<node*> stk;
      printAllRootLeafPathLow(root_, stk); 
    }
    void printLeftView() {
      queue<node*> node_queue;
      queue<int> level_queue;
      node_queue.push(root_);
      level_queue.push(1);
      int prev_l = -1;
      while(!node_queue.empty()) {
        node *x = node_queue.front();
        int cur_l = level_queue.front();
        node_queue.pop();
        level_queue.pop();
        if(cur_l != prev_l) {
          cout << x->data_ << " ";
          prev_l = cur_l;
        }
        if(x->left_) {
          node_queue.push(x->left_);
          level_queue.push(cur_l+1);
        }
        if(x->right_) {
          node_queue.push(x->right_);
          level_queue.push(cur_l+1);
        }
      }
      cout << endl;
    }

    int depth_;
    bool checkSameLeavesLevelLow(node *x, int level) {
      if(x == NULL) return true;
      if(!x->left_ && !x->right_) {
        if(depth_ == -1) {
          depth_ = level+1;
          return true;
        } else {
          if(depth_ != (level+1)) {
            return false;
          }
          return true;
        }
      }
      return (checkSameLeavesLevelLow(x->left_, level+1) & checkSameLeavesLevelLow(x->right_, level+1));
    }
    void checkSameLeavesLevel(void) {
      depth_ = -1;
      if(checkSameLeavesLevelLow(root_, 1)) {
        cout << "All leaves are at same level" << endl;
      } else {
        cout << "All leaves are not at same level" << endl;
      }
    }
    int getAncestorRec(node *x, int d1, int d2) {
      if(x->data_ > d1 && x->data_ < d2) {
        return x->data_;
      } else {
        if(x->data_ < d1) {
          if(x->left_) {
            return getAncestorRec(x->left_, d1, d2);
          } else {
            return -1;
          }
        } else {
          if(x->right_) {
            return getAncestorRec(x->left_, d1, d2);
          } else {
            return -1;
          }
        }
      }
    }
    void getAncestor(int d1, int d2) {
      int x = getAncestorRec(root_, d1, d2);
      if(x == -1) {
        cout << "Ancestor not found" << endl;
      } else {
        cout << "Ancestor " << x << endl;
      }
    }

    node* extractInRangeLow(node* x, int min, int max) {
      if(x == NULL) return NULL;
      x->left_ = extractInRangeLow(x->left_, min, max);
      x->right_ = extractInRangeLow(x->right_, min, max);
      if(x->data_ < min) {
        node* replace = x->right_;
        x->right_ = NULL;
        delete x;
        return replace; // NOTE: The entire left subtree is also deleted since it is guranteed to be less tham min
      }
      if(x->data_ > max) {
        node* replace = x->left_;
        x->left_ = NULL;
        delete x;
        return replace; // NOTE: The entire left subtree is also deleted since it is guranteed to be less tham min
      }
      return x;
    }
    void extractInRange(int min, int max) {
       root_ = extractInRangeLow(root_, min, max);
    }

    node* splitThresholdLow(node *x, int l) {
      if(x == NULL) return NULL;
      x->left_ = splitThresholdLow(x->left_, l);
      x->right_ = splitThresholdLow(x->right_, l);
      if(x->data_ < l) {
        node* replace = x->right_;
        x->right_ = NULL;
        delete x;
        return replace;
      }
      return x;
    }
    void splitThreshold(int l) {
      root_ = splitThresholdLow(root_, l);
    }

};

int main() {
  BinaryTree *bt = new BinaryTree();
  bt->insert_node(2, 0, false);
  bt->insert_node(5, 2, true);
  bt->insert_node(6, 2, false);
  bt->insert_node(7, 5, true);
  bt->insert_node(8, 5, false);
  bt->insert_node(9, 6, true);
  bt->insert_node(10, 6, false);
  bt->insert_node(11, 7, true);
  bt->insert_node(12, 9, false);
  cout << "Inoder" << endl;
  bt->inOrder();
  cout << "Level oder" << endl;
  bt->LevelOrder();
  /* Right node */
  bt->RightNode(11);
  /* Deepest node */
  bt->DeepestNode();
  /* Print all the paths */
  cout << "Printing all the paths" << endl;
  bt->printAllRootLeafPath();
  cout << "Printing left view" << endl;
  bt->printLeftView();
  cout << "Check if all leaves are at same level" << endl;
  bt->checkSameLeavesLevel();
  bt->getAncestor(7, 8);
  /* Extract tree in the range [min, max] */
  bt->extractInRange(6, 10);
  bt->splitThreshold(7);
  bt->inOrder();
}
