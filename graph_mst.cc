
#define MAX_LEN 100

void print_2d_matrix(int a[MAX_LEN][MAX_LEN], int N, int M) {
  int type = 1;
  if(type == 0) {
    for(int i=0; i<N; i++) {
      for(int j=0; j<M; j++) {
        printf("  %d", a[i][j]);
      }
      printf("\n");
    }
  } else {
    for(int i=0; i<N; i++) {
      for(int j=i; j<M; j++) {
        if(a[i][j]) {
          printf("%d  %d  %d", i, j, a[i][j]);
          printf("\n");
        }
      }
    }
  }
}

void print_1d_matrix(int a[], int N) {
  for(int i=0; i<N; i++)
    printf("  %d", a[i]);
  printf("\n");
}

class node {
  public :
    node(int data) {
      data_ = data; 
    }
    void add_child(node * child) {
      child_.pb(child);
    }
    int data_;
    vector<node*> child_;
};

class edge {
public:
  edge(int u, int v, int data) {
    u_          = u;
    v_          = v;
    data_       = data; 
  }
  bool operator<(const edge &rhs) const {
    return data_ < rhs.data_;
  }
  int u_;
  int v_;
  int data_;
};

void print_preorder(node *n) {
  printf("%d ", n->data_);
  if(n->child_.size() == 0) return;
  for(int i=0; i<n->child_.size(); i++) {
    print_preorder(n->child_[i]);
  }
}

void kruskals_MST(int w[][MAX_LEN], int N) {
  vector<edge> alledges;
  for(int i=0; i<N; i++) {
    // NOTE: Considering only upper diagonal elements for bi-directional edges
    for(int j = i+1; j<N; j++) {
      if(w[i][j]) {
        alledges.pb(edge(i, j, w[i][j]));
      }
    }
  }
  int MST[MAX_LEN][MAX_LEN];
  // sort based on the edge weight
  sort(alledges.begin(), alledges.end());
  // Now start the core algo
  bool flags[MAX_LEN];
  memset(flags, false, sizeof(bool)*MAX_LEN);
  for(int i=0; i<alledges.size(); i++) {
    edge &e = alledges[i];
    if(!(flags[e.u_] && flags[e.v_])) {
      MST[e.u_][e.v_] = MST[e.v_][e.u_] = 1;
      flags[e.u_] = flags[e.v_] = 1;
    } 
  }
  print_2d_matrix(MST, N, N);
  node* mst_tree= DFSUtil(MST, N);
  printf("\n");
  print_preorder(mst_tree);
}

int main() {
  freopen("tsp.txt", "r", stdin);
  TEST {
    int a[MAX_LEN][MAX_LEN];
#ifdef TYPE1
    int N;
    si(N);
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        scanf("%d", &a[i][j]);
      }
    }
#else
    int N;
    si(N);
    int E;
    si(E);
    int E_ = E;
    while(E_--) {
      int x, y, w;
      si(x); si(y); si(w);
      a[x][y] = a[y][x] = w;
    }
#endif
    print_2d_matrix(a, N, N);
    int D[MAX_LEN];
    bellman(a, N, D);
    printf("\n");
    print_1d_matrix(D, N);
    printf("\n");
    kruskals_MST(a, N);
  }
}
