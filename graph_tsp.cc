/* ############################################################################
 * START OF HEADER 
 * ############################################################################
 */
#include<cstdio>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cmath>
#include<cassert>
#include<ctime>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include<list>
#include<set>
#include<map>
using namespace std;
 
#define LL long long
#define LD long double

#define sc(x)  scanf("%c",&x) //char
#define si(x)  scanf("%d",&x) //int
#define sf(x)  scanf("%f",&x) //float
#define sl(x)  scanf("%I64d",&x) //int64_
#define sd(x)  scanf("%lf",&x) //double
#define sld(x) scanf("%Lf",&x) //long double
#define slld(x) scanf("%lld",&x) //long long int
#define ss(x)  scanf("%s",x) // string

#define pc(x)  printf("%c",x)
#define pi(x)  printf("%d ",x)
#define pf(x)  printf("%f ",x)
#define pl(x)  printf("%I64d ",x)
#define pd(x)  printf("%lf ",x)
#define pld(x) printf("%Lf ",x)
#define plldn(x) printf("%lldn", x);
#define ps(x) printf("%s", x);

#define pin(x)  printf("%d\n",x)
#define pln(x)  printf("%I64d\n",x)
#define pfn(x)  printf("%f\n",x)
#define pdn(x)  printf("%lf\n",x)
#define pldn(x) printf("%Lf\n",x)
#define plld(x) printf("%lld\n", x);
#define psn(x)  printf("%s\n",x)

#define pn() printf("\n")
#define _p() printf(" ")

#define MODVAL 1000000007

#define FORab(i,a,b) for(int i=a;i<=b;i++)
#define REVab(i,a,b) for(int i=a;i>=b;i--)
#define FORn(i,n) for(i=0;i<n;i++)
#define REVn(i,n) for(int i=n;i>=0;i--)
#define FORSTL(it, a) for(it=a.begin(); it!=a.end(); it++)
#define REVSTL(it, a) for(it=a.end(); it!=a.begin(); it--)

#define MEMS(a,v) memset(a, 0 ,v)
#define MAX(x,y) (x)>(y)?(x):(y)
#define MIN(x,y) (x)<(y)?(x):(y)
#define pb push_back
#define pob pop_back
#define b() begin()
#define e() end()
#define s() size()
#define cl() clear()
#define fi first
#define se second
#define INF (1000000000)
#define SZ 100000
#define MOD (1<<30)

#define VS vector<string>
#define VI vector<int>
#define VF vector<float>
#define VD vector<double>
#define MII map<int,int>
#define MIS map<int, string>
#define MSI map<string, int> 
#define MSS map<string, string>

#define VSI vector<string>::iterator
#define VII vector<int>:iterator
#define VFI vector<float>::iterator
#define VDI vector<double>::iterator
#define MIII map<int,int>::iterator
#define MISI map<int, string>::iterator
#define MSII map<string, int>::iterator 
#define MSSI map<string, string>::n
#define print_array(x,n) for(int i=0; i<n; i++) { cout << x[i] << endl; }
#define TEST int T;scanf("%d",&T);while(T--)
#define CASES int N;scanf("%d",&N);while(N--)

/* ############################################################################
 * END OF HEADER 
 * ############################################################################
*/

/* GREEDY GRAPH COLORING */
#define MAX_LEN 100

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

node* constructTree(int a[][MAX_LEN], int N) {
  stack<int> stk;
  node* tree[MAX_LEN];
  memset(tree, 0, sizeof(node*)*MAX_LEN);
  tree[0] = new node(0);
  stk.push(0); 
  while(!stk.empty()) {
    int k = stk.top();
    stk.pop();
    for(int j=0; j<N ; j++) {
      if(a[k][j] && !tree[j]) {
        tree[j] = new node(j);
        tree[k]->add_child(tree[j]);
        stk.push(j);
      }
    }
  }
  for(int i=0; i<N; i++) {
    if(!tree[i]) return NULL;
  }
  return tree[0];
}

void bellman(int w[][MAX_LEN], int N, int D[]) {
  for(int i=0; i<N; i++) D[i] = INF;
  D[0] = 0;
  for(int n=0; n<N-1; n++) {
    for(int i=0; i<N; i++) {
      for(int j = 0; j<N; j++) {
        if(w[i][j] && (D[i] + w[i][j]) < D[j]) {
          D[j] = D[i] + w[i][j];
        }
      }
    }
  }
}

void kruskals_MST(int w[][MAX_LEN], int MST[][MAX_LEN], int N) {
  memset(MST, 0, sizeof(int)*MAX_LEN*MAX_LEN);
  vector<edge> alledges;
  for(int i=0; i<N; i++) {
    for(int j = i+1; j<N; j++) {
      if(w[i][j]) {
        alledges.pb(edge(i, j, w[i][j]));
      }
    }
  }
  sort(alledges.begin(), alledges.end());
  bool flags[MAX_LEN];
  memset(flags, false, sizeof(bool)*MAX_LEN);
  for(int i=0; i<alledges.size(); i++) {
    edge &e = alledges[i];
    if(!(flags[e.u_] && flags[e.v_])) {
      MST[e.u_][e.v_] = MST[e.v_][e.u_] = 1;
      flags[e.u_] = flags[e.v_] = 1;
    } 
  }
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
    // Form a MST and print the preorder traversal of 
    // MST
    print_2d_matrix(a, N, N);
    kruskals_MST(a, N);
    print_2d_matrix(MST, N, N);
    if(isConnected(MST, N) && !hasCycles(MST, N)) {
      node* mst_tree = constructTree(MST, N);
      printf("\n");
      print_preorder(mst_tree);
    }
  }
}
