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

#define read1dArray(a, N)  { \
  int i = 0; \
  while(N--) { \
    si(a[i++]); \
  } \
} 

#define read2dArray(a, N, M)  { \
  int i = 0; \
  int j = 0; \
  for(int i=0; i<N; i++) { \
    for(int j=0; j<M; j++) { \
      si(a[i][j]); \
    } \
  } \
} 

#define VSI vector<string>::iterator
#define VII vector<int>:iterator
#define VFI vector<float>::iterator
#define VDI vector<double>::iterator
#define MIII map<int,int>::iterator
#define MISI map<int, string>::iterator
#define MSII map<string, int>::iterator 
#define MSSI map<string, string>::iterator
#define print_array(x,n) for(int i=0; i<n; i++) { cout << x[i] << endl; }
#define TEST int T;scanf("%d",&T);while(T--)
#define CASES int N;scanf("%d",&N);while(N--)

/* ############################################################################
 * END OF HEADER 
 * ############################################################################
*/
/******************************************************************
 *  SOME UTUILITY FUNCTIONS
 *  **************************************************************/

#define MAXN 1000000009
int power(int a, int b)
{
  if(b==0)
    return 1;
  else if(b==1)
    return a;
  else if(b%2==0)
    return power((a*a),b/2);
  else
    return (power((a*a),b/2)*a);
}

int logbase2(int N) {
  int x = (int)(log(N)/log(2));
  return x;
}

int powerint(int A, int B) {
  int x= (int)pow(A, B);
  return x;
}


class Graph {
  public:
    Graph(int N) {
      E_.resize(N);
      for(int i=0; i<N; i++) {
        E_[i].resize(N, 0);
      }
    }
    void addEdge(int u, int v) {
      (E_[u])[v] = 1;
      (E_[v])[u] = 1;
    }
    void removeEdge(int u, int v) {
      (E_[u])[v] = 0;
      (E_[v])[u] = 0;
    }
    const vector<int>& operator[](const int i) const {
      return E_[i];
    }
    vector< vector<int> > E_;
};

#define MAXNUM 10000000

// Indexed from 1 to N. Aim of below segment tree is to 
// return the miniumum element 
class segment_tree {
  public:
    segment_tree(int size) {
      tree_size_ = 2*(powerint(2, (logbase2(size)+1)));
      tree_.resize(tree_size_, MAXNUM);
    }
    // To update index "5" with a value of "78" in a tree with nodes 1-N, use
    // update(5, 78, 1, 1, N);
    void update(int index, int value, int root_index, int low, int high) {
      if(low == high && low == index) {
        tree_[low] = value;
      } else {
        int middle = (low+high)/2; 
        if(index >= low && index <= middle) {
          update(index, value, root_index*2, low, middle);
        } else {
          update(index, value, root_index*2+1, low, middle);
        }
        tree_[root_index] = MIN(tree_[root_index*2], tree_[root_index*2+1]);
      } 
    } 
    
    // To get the minimum element between 3 and 5 in a tree of size 1-N
    // query(1, 3, 5, 1, N)
    int query(int root_index, int x, int y, int low, int high) {
      if(x > high || y < low) { 
        return MAXN;
      }
      if(x <= low && high <= y) {
        return tree_[root_index];
      }
      int l1, l2;
      int mid = (low+high)>>2;
      l1 = query(root_index*2, x, y, low, mid);
      l2 = query(root_index*2+1, x, y, mid+1, high);
      return l1<l2 ? l1 : l2;
    }
  private:
    int tree_size_;
    vector<int> tree_;
};

class hld {
  public:
    // Constructor
    hld(int size) {
      node_rank_.resize(size, -1);
      node_chain_.resize(size, -1);
      chain_leader_.resize(size, -1);
      parent_.resize(size, -1);
      tot_chains_ = 0;
      g_pos_ = 0;
    }

    // Populate the parent and subtree size
    void dfs(Graph &E, int cur_node, int cur_parent) {
      parent_[cur_node]         = cur_parent;
      subtree_size_[cur_node]   = 1;
      for(int i=0; i!=E[cur_node].size(); i++) {
        int j = E[cur_node][i];
        if(parent_[j] != -1) {
          dfs(E, j, cur_node);
          subtree_size_[cur_node] += subtree_size_[j];
        }
      }
    }

    // heavy-light decomposition
    void heavy_light_decompose(Graph &E, int cur_node, int cur_parent, int cur_chain, int cur_pos) {
      if(cur_chain == -1) {
        cur_chain = tot_chains_++;
        cur_pos = 0;
        chain_leader_[cur_chain] = cur_node;
      }
      node_rank_[cur_node]      = g_pos_++;
      node_chain_[cur_node]     = cur_chain;
      // Find the adjacent vertice with heaviest subtree size
      int mx = -1;
      for(int i=0; i!=E[cur_node].size(); i++) {
        int j = E[cur_node][i];
        if( parent_[j] != -1 && ( mx == -1 || subtree_size_[j] > subtree_size_[mx] ) ) {
          mx = j;
        }
      }
      // Now traverse the adjacent vertices
      for(int i=0; i!=E[cur_node].size(); i++) {
        int j = E[cur_node][i];
        if(parent_[j] != -1) {
          if(j == mx) {
            // Continue with the same link
            heavy_light_decompose(E, j, cur_node, cur_chain, cur_pos+1);
          } else {
            // Start a new link 
            heavy_light_decompose(E, j, cur_node, -1, 0);
          }
        }
      }
    }

  private:
    vector<int> chain_leader_;
    vector<int> node_rank_;
    vector<int> node_chain_;
    vector<int> parent_;
    vector<int> subtree_size_;
    int tot_chains_;
    int g_pos_;
};

int main() {
}
