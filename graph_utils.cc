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

// Checks if the graph is connected from given source node. 
// Does a DFS from "s"
// WORKS : DAG/Non DAG
bool allNodesReachable(int w[][MAX_LEN], int N, int s, bool visited[]) {
  stack<int> stk;
  memset(visited, false, sizeof(bool)*N);
  visited[s] = true;
  stk.push(s);
  while(!stk.empty()) {
    int k = stk.top();
    stk.pop();
    for(int j=0; j<N ; j++) {
      if(w[k][j] && !visited[j]) {
        visited[j] = true;
        stk.push(j);
      }
    }
  }
  for(int i=0; i<N; i++) {
    if(!visited[i]) return false;
  }
  return true;
}

// Do DFS and constructs a tree from the graph from adjacency matrix
// NOTE: Call hasCycles() and then only call this function
// WORKS : DAG/Non DAG
node* constructTree(int a[][MAX_LEN], int N, int source=0) {
  stack<int> stk;
  node* tree[MAX_LEN];
  memset(tree, 0, sizeof(node*)*MAX_LEN);
  tree[source] = new node(source);
  stk.push(source); 
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
 
bool hasCycleUtil(int a[][MAX_LEN], int N, 
                  int s, bool visited[], bool recStack[]) {
  visited[s] = true;
  recStack[s] = true;
  for(int j=0; j<N; j++) {
    if(a[s][j] == 0 || s == j) continue;
    if(visited[j] && recStack[j]) return true; //cycle detected because node "j" is already in the stack
    if(hasCycleUtil(a, N, j, visited, recStack)) return true;
  }
  recStack[s] = false;
  return false;
}


// If graph has any cycles. Used for uni-directional graphs only
// For bidirectional it always returns true;
// WORKS : DAG
bool hasCycle(int a[][MAX_LEN], int N) {
  bool visited[MAX_LEN];
  memset(visited, false, sizeof(bool)*MAX_LEN);
  bool recStack[MAX_LEN];
  for(int i=0; i<N; i++) {
    memset(recStack, false, sizeof(bool)*MAX_LEN);
    if(!visited[i]) {
       if(hasCycleUtil(a, N, i, visited, recStack)) return true;
    }
  }
  return false;
}

// graph has eucledian cycle if all vertices have even degree
// WORKS : Non-DAG
bool hasEucledianCycle(int a[][MAX_LEN], int N) {
  for(int i=0; i<N; i++) {
    int degree = 0;
    for(int j=0; j<N; j++) {
      if(i != j && a[i][j]) {
        degree++;
      }
    }
    if(degree%2 == 1) return false;
  }
  return true;
}

// graph has eucledian path
// 0 or 2 vertices have odd degreee. Rest all of them have even degree
// NOTE: Applicable only for undirected graph
// WORKS : Non-DAG
bool hasEucledianPath(int a[][MAX_LEN], int N) {
  int g_odd = 0;
  for(int i=0; i<N; i++) {
    int degree = 0;
    for(int j=0; j<N; j++) {
      if(i != j && a[i][j]) {
        degree++;
      }
    }
    if(degree%2 == 1) {
      g_odd++;
    }
  }
  if(g_odd == 0 || g_odd == 2) {
    return true;
  } else {
    return false;
  }
}

// print eucledian path
void printEucledianPath(int a[][MAX_LEN], int N) {
}

// This node order in the stack gives the Topological sort order also in a DAG                 
void DFSUtil(int a[][MAX_LEN], int N, int u, bool visited[], stack<int> &stk) {
  visited[u] = true;
  for(int v=0; v<N; v++) {
    if(!visited[v] && u != v && a[u][v]) {
      DFSUtil(a, N, v, visited, stk); 
     // stk.push(v);
    }
  }
  stk.push(u);
}

// There exists a path from any vertex to any other vertex
// NOTE: For bi-directional graph it is easy, Just do a DFS
// and all nodes are reachable then it is strongle connected componenet. 
// But for unidirectional componennt below are the ways
// 1. Use floyd warshalls and find all-pair shortest path - O(V^3)
// 2. Use DFS from all the V nodes and check if every other node is reachable - O(v*(V+E))
// 3. Use SCC algorithm - O(V+E). This one is implemented
// WORKS : DAG . For Non-DAG a simple DFS will do, because isConnected() == isStronglyConnected()
bool isStronglyConnected(int a[][MAX_LEN], int N) {

  //DFS first round. Also the topo sort
  bool visited[MAX_LEN];
  stack<int> stk;
  memset(visited, false, sizeof(bool)*MAX_LEN);
  for(int i=0; i<N; i++) {
    if(!visited[i]) {
      DFSUtil(a, N, i, visited, stk); 
      stk.push(i);
    }
  }

  // Now get the transpose of the matrix;
  int Xa[MAX_LEN][MAX_LEN];
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      if(a[i][j]) {
        Xa[j][i] = a[i][j];
      }
    }
  }
  int tot_forests=0;
  stack<int> forest;
  memset(visited, false, sizeof(bool)*MAX_LEN);
  //Now do the DFS of tanspose matrix
  while(!stk.empty()) {
    int k = stk.top();
    stk.pop();
    if(!visited[k]) {
      DFSUtil(Xa, N, k, visited, forest); 
      forest.push(k);
      tot_forests++;
      printf("Forest #%d:\n", tot_forests);
      while(!forest.empty()) {
        printf("%d ", forest.top());
        forest.pop();
      }
      printf("\n");
    }
  }
  return (tot_forests==1 ? true : false);
}

// WORKS : DAG . For Non-DAG a simple DFS will do
bool getSCC(int a[][MAX_LEN], int N, vector< vector<int>* > &forests) {

  //DFS first round
  bool visited[MAX_LEN];
  stack<int> stk;
  memset(visited, false, sizeof(bool)*MAX_LEN);
  for(int i=0; i<N; i++) {
    if(!visited[i]) {
      DFSUtil(a, N, i, visited, stk); 
      stk.push(i);
    }
  }

  // Now get the transpose of the matrix;
  int Xa[MAX_LEN][MAX_LEN];
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      if(a[i][j]) {
        Xa[j][i] = a[i][j];
      }
    }
  }
  int tot_forests=0;
  stack<int> forest;
  memset(visited, false, sizeof(bool)*MAX_LEN);
  //Now do the DFS of tanspose matrix
  while(!stk.empty()) {
    int k = stk.top();
    stk.pop();
    if(!visited[k]) {
      DFSUtil(Xa, N, k, visited, forest); 
      forest.push(k);
      forests.pb(new vector<int>);
      while(!forest.empty()) {
        forests[tot_forests]->pb(forest.top());
        forest.pop();
      }
      tot_forests++;
    }
  }
  return (tot_forests==1 ? true : false);

}

void APUtil(int a[][MAX_LEN], int N, int u, int visited[], int disc[], int low[], int parent[], bool isAP[]) {
  static int disc_time = 0;
  disc[u] = ++disc_time;
  low[u] = disc[u];
  visited[u] =true;
  int children=0;
  for(int v=0; v<N; v++) {
    if(a[u][v] && !visited[v]) {
      children++;
      parent[v] = u;
      APUtil(a, N, v, visited, disc, low, parent, isAP);
      low[u] = min(low[u], low[v]);
      if(parent[u] == -1 && children > 1) {
        // Root node and has more than 2 childrens
        isAP[u] = true;
      } else if(parent[u] != -1 && children > 0) { //Leaf node can never be AP's hence children > 0
        // Non leaf-root node and has atleast one node "k" in a sbtree rooted at v
        // such that the disc[k] >= disc[u]. If we delete this node then therre will be no other way 
        // to reach node "k"
        if(low[v] > disc[u]) {
          isAP[u] = true;
        }
      }
    } else if(u!=v && a[u][v]) {
      low[u] = min(low[u], disc[v]);
    }
  }
}


// Articulation or cut vertice is a vetrtex which if we remove from the 
// graph, will no longer be connected. NOTE: Applicable for undirectional graph 
// IMPORTANCE: Find critical nodes
// WORKS : FOr Non-DAG. AP's and Bridges are for NON-DAG
bool findArticulationPoint(int a [][MAX_LEN], int N, bool isAP[]) {
  memset(isAP, false, sizeof(isAP));
  int low[MAX_LEN];     // Lowest discovery time reachable from node
  int disc[MAX_LEN];    // discovery time of the node
  int parent[MAX_LEN];  // parent of the node
  int visited[MAX_LEN];
  memset(low, 0, sizeof(low));
  memset(disc, 0, sizeof(disc));
  memset(parent, -1, sizeof(parent));
  memset(visited, 0, sizeof(visited));
  APUtil(a, N, 0, visited, disc, low, parent, isAP);
}

void BridgeUtil(int a[][MAX_LEN], int N, int u, int visited[], int disc[], int low[], int parent[], bool isBridge[][MAX_LEN]) {
  static int disc_time = 0;
  disc[u] = ++disc_time;
  low[u] = disc[u];
  visited[u] =true;
  int children=0;
  for(int v=0; v<N; v++) {
    if(a[u][v] && !visited[v]) {
      children++;
      parent[v] = u;
      BridgeUtil(a, N, v, visited, disc, low, parent, isBridge);
      low[u] = min(low[u], low[v]);
      // The edge(u,v) connect atleast one node "k" in a subtree rooted at v, such that 
      // disc[k] >= disc[u]. If se delete this edge then there is no other way to reach the node "k"
      if(low[v] >= disc[u]) {
        isBridge[u][v] = true;
      }
    } else if(u!=v && a[u][v]) {
      low[u] = min(low[u], disc[v]);
    }
  }
}

// Bridges are the edges which if we remove the graph will no longer be connected
// NOTE: Applicable for undirected graph
// IMPORTANCE : Find critical edges. 
// WORKS : FOr Non-DAG. AP's and Bridges are for NON-DAG
bool findBridges(int a[][MAX_LEN], int N, bool isBridge[][MAX_LEN]) {
  memset(isBridge, false, sizeof(isBridge));
  int low[MAX_LEN];     // Lowest discovery time reachable from node
  int disc[MAX_LEN];    // discovery time of the node
  int parent[MAX_LEN];  // parent of the node
  int visited[MAX_LEN];
  memset(low, 0, sizeof(low));
  memset(disc, 0, sizeof(disc));
  memset(parent, -1, sizeof(parent));
  memset(visited, 0, sizeof(visited));
  BridgeUtil(a, N, 0, visited, disc, low, parent, isBridge);
}

// Graph is BiCOnnected if there exisists two vertext disjoint paths between 
// any to vertices of the graph
bool isBiConnected(int a[][MAX_LEN], int N) {
  bool isCutVertice[MAX_LEN];
  if(!isStronglyConnected(a, N)) return false;
  if(!findArticulationPoint(a, N, isCutVertice)) return false;
  return true;
}

void ToplogicalSortUtil(int a[][MAX_LEN], int N, int u, bool visited[], stack<int> &stk) {
  visited[u] = true;
  for(int v=0; v<N; v++) {
    if(!visited[v] && u != v && a[u][v]) {
      ToplogicalSortUtil(a, N, v, visited, stk); 
    }
  }
  stk.push(u);
}

// Givan a DAG find the shortest path from a "s" to "t"
// Why not Bellman or Djikstras ?
// Bellman = O(VE)
// Djikstras = O(E + VlogV)
//
// => This method is O(V+E)
// 1. Do toplogical sort
// 2. Travers the topo graph and keep rlaxing the edges 
int shortest_path_DAG(int a[][MAX_LEN], int N, int s, int t) {
  bool visited[MAX_LEN];
  memset(visited, false, sizeof(visited));
  stack<int> stk;
  for(int i=0; i<N ; i++) {
    if(!visited[i]) {
      ToplogicalSortUtil(a, N, i, visited, stk); 
    }
  } 
  int min_dist[MAX_LEN];
  for(int i=0; i<N; i++) {
    min_dist[i] = INF;
  }
  min_dist[s] = 0;
  bool start_track;
  while(!stk.empty()) {
    int u = stk.top();
    stk.pop();
    if(u == s) start_track = true;
    if(start_track) {
      for(int v=0; v<N; v++) {
        if(a[u][v]) {
          if(min_dist[v] > min_dist[u] + a[u][v]) {
            min_dist[v] =  min_dist[u] + a[u][v];
          }
        }
      }
    }
  }
  return min_dist[t];
}

bool isSafe(int a[][MAX_LEN], int N, int u, int colr, int colors[]) {
  for(int i=0; i<N; i++) {
    if(a[u][i] && colors[i] == colr) {
      return false;
    }
  }
  return true;
}

// Is it possible to color a non-DG graph using at max M colors ? WHen M=2
// we can use this function to determine if the a graph is bipartite graph or 
// K-partite graph
bool mcolor_graph_possible(int a[][MAX_LEN], int N, int u, int M, int colors[]) {
  if(u==N) {
    return true;
  } else {
    for(int i=1; i <= M; i++) {
      if(isSafe(a, N, u, i, colors)) {
        colors[u] = i;
        if(mcolor_graph_possible(a, N, u+1, M, colors)) {
          return true;
        } 
        colors[u] = 0; // backtrack
      }
    }
  }
  return false;
}

bool hasUnvisitedNode(int visited[], int N, bool path) {
  for(int i=0; i<N; i++) {
    if(visited[i] == 0) {
      return true;
    }
  }
  if(path) {
    return false;
  } else {
    if(visited[0] == 2) {
      return false;
    } else {
      return true;
    }
  }
}

// Graph has hamiltonian cycle
// Visit all the vertices in the graph exactly once
// TSP = minimum weight Hamilton cycle
bool hasHamiltonCycle(int a[][MAX_LEN], int N, int u, int visited[]) {
  if(!hasUnvisitedNode(visited, N, false)) {
    return true;
  } else {
    for(int i=0; i<N ; i++) {
      if(a[u][i] && (!visited[i] || i==0)) {
        visited[i] += 1;
        if(hasHamiltonCycle(a, N, i, visited)) {
          return true;
        }
        visited[i] -= 1; //back trace
      }
    }
    return false;
  }
}

// Graph has hamiltonian path
bool hasHamiltonPath(int a[][MAX_LEN], int N, int u, int visited[]) {
  if(!hasUnvisitedNode(visited, N, true)) {
    return true;
  } else {
    for(int i=0; i<N ; i++) {
      if(a[u][i] && !visited[i]) {
        visited[i] = true;
        if(!hasUnvisitedNode(visited, N, true) || hasHamiltonPath(a, N, i, visited)) {
          return true;
        }
        visited[i] = false; //back trace
      }
    }
    return false;
  }
}

int main() {
  freopen("graph_utils.txt", "r", stdin);
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
      a[x][y] = w;
    }
#endif
    bool visited[MAX_LEN];
    bool isBridge[MAX_LEN][MAX_LEN];
    cout << "All nodes reachable:" << allNodesReachable(a, N, 1, visited) << endl;
    cout << "Has cycles:" << hasCycle(a, N) << endl;
    cout << "Has Eucledian path:" << hasEucledianPath(a, N) << endl;
    cout << "Has Eucledian cycle:" << hasEucledianCycle(a, N) << endl;
    cout << "is strongly connected:" << isStronglyConnected(a, N) << endl;
    cout << "Articulaion Point:" << findArticulationPoint(a, N, visited) << endl;
    for(int i=0; i<N; i++) {
      if(visited[i]) printf("%d ", i);
    }
    cout << "Bridges:" << findBridges(a, N, isBridge) << endl;
    printf("\n");
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        if(isBridge[i][j]) printf("%d %d\n", i, j);
      }
    }
    cout << "Min distance in DAG in O(V+E)" << shortest_path_DAG(a, N, 2, 3) << endl;
    int visitedi[MAX_LEN];
    memset(visitedi, 0, sizeof(visitedi));
    visitedi[0]=1;
    cout << "Has hamilton cycle:" << hasHamiltonPath(a, N, 0, visitedi) << endl;
  }
}
