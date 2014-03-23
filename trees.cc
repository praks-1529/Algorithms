#include<iostream>
using namespace std;


template <class T>
class node {
  private:
    node<T>* left_;
    node<T>* right_;
    T data_;
  public:
    node() : left_(NULL), right_(NULL) { } ;
    node(T data) : left_(NULL), right_(NULL) { data_ = data; }
    ~node();
    void set_left(node<T>* left) { this->left_ = left; }
    void set_right(node<T>* right) { this->right_ = right; }
    void set_data(T data) { this->data_ = data; }
    node<T>* get_left(void) { return(this->left_) ; }
    node<T>* get_right(void) { return(this->right_) ; }
    T& get_data(void) { return(this->data_); }
};

template <typename T>
class less_s {
  public:
    bool operator () (T &left_data, T &right_data) 
           { 
              if(left_data < right_data) {
                return(true);
              } else {
                return(false);
              }
           }
};

template<class T>
static void inorder_traversal_core(T node_) {
  if(node_ != NULL) {
    inorder_traversal_core(node_->get_left());
    cout << node_->get_data() << " " ;
    inorder_traversal_core(node_->get_right());
  }
}

template<class T>
static void preorder_traversal_core(T node_) {
  if(node_ != NULL) {
    cout << node_->get_data() << " " ;
    inorder_traversal_core(node_->get_left());
    inorder_traversal_core(node_->get_right());
  }
}

template<class T>
static void postorder_traversal_core(T node_) {
  if(node_ != NULL) {
    inorder_traversal_core(node_->get_left());
    inorder_traversal_core(node_->get_right());
    cout << node_->get_data() << " " ;
  }
}

template <class T, class Compare = less_s<T> >
class bst {
  private:
    node<T>* root_node_;
  public:
    bst() { root_node_ = NULL ; }
    ~bst();
    void insert_node(T data);
    void inorder_traversal(void);
    void preorder_traversal(void);
    void postorder_traversal(void);
};


template <class T, class Compare>
bst<T, Compare>::~bst() {
}

template <class T, class Compare>
void bst<T, Compare>::insert_node(T data) {
  Compare comp;
  if(root_node_ == NULL) {
    root_node_ = new node<T>;
    root_node_->set_data(data);
    return;
  } else {
    node<T> *cur_node = root_node_;
    node<T> *prev_node;
    while(cur_node != NULL) {
      if(comp(data, cur_node->get_data())) {
        prev_node = cur_node;
        cur_node = cur_node->get_left();
      } else {
        prev_node = cur_node;
        cur_node = cur_node->get_right();
      }
    } 
    node<T> *new_node = new node<T>(data);
    if(comp(data, prev_node->get_data())) {
      prev_node->set_left(new_node);
    } else {
      prev_node->set_right(new_node);
    }
  }
  return;
}

template <class T, class Compare>
void bst<T, Compare>::inorder_traversal() {
  inorder_traversal_core(root_node_);
}

template <class T, class Compare>
void bst<T, Compare>::preorder_traversal() {
  preorder_traversal_core(root_node_);
}

template <class T, class Compare>
void bst<T, Compare>::postorder_traversal() {
  postorder_traversal_core(root_node_);
}

int main() {
  bst<int> my_bst;
  my_bst.insert_node(6);
  my_bst.insert_node(8);
  my_bst.insert_node(1);
  my_bst.inorder_traversal();
}
