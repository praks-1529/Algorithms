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
      for(int j=0; j<M; j++) {
        if(a[i][j]) {
          printf("%d  %d  %d", i, j, a[i][j]);
          printf("\n");
        }
      }
    }
  }
}

bool BFSUtil(int a[][MAX_LEN], int N, int s, int t, vector<int> &parent) {
  // Create a visited array and mark all vertices as not visited
  bool visited[MAX_LEN];
  memset(visited, 0, sizeof(visited));
  // Create a queue, enqueue source vertex and mark source vertex
  // as visited
  queue <int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;
  // Standard BFS Loop
  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    for (int v=0; v<N; v++)
    {
      if (visited[v]==false && a[u][v] > 0)
      {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }
  // If we reached sink in BFS starting from source, then return
  // true, else false
  return (visited[t] == true);
}

void print_1d_matrix(vector<int> &a, int N) {
  for(int i=0; i<N; i++)
    printf("  %d", a[i]);
  printf("\n");
}

// Checks if the graph is connected from given source node. 
// Does a DFS from "s"
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

bool augument_path_exisis(int a[][MAX_LEN], int N, int s, int t, vector<int> &path) {
  path.clear();
  vector<int> parent(N);
  if(BFSUtil(a, N, s, t, parent)) {
    for(int i=t; i > 0; ) {
      path.insert(path.begin(), i);
      i = parent[i];
    }
    return true;
  } else {
    return false;
  }
}

int max_flow(int W[][MAX_LEN], int N, int s, int t, int max_flow[][MAX_LEN]) {
  int a[MAX_LEN][MAX_LEN];
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      a[i][j] = W[i][j];
    }
  }
  vector<int> path;
  int maxflow=0;
  while(augument_path_exisis(a, N, s, t, path)) {
    int min = INF;
    for(int i=1; i<path.size(); i++) {
      if(a[path[i-1]][path[i]] < min)  {
        min = a[path[i-1]][path[i]];
      }
    }
    for(int i=1; i<path.size(); i++) {
      a[path[i-1]][path[i]] -= min;
      max_flow[path[i-1]][path[i]] += min;
    }
    maxflow += min;
#if 0
    printf("Cost : %d\n", min);
    print_1d_matrix(path, N);
    printf("Residual matrix \n");
    print_2d_matrix(a, N, N);
    printf("Max flow matrix \n");
    print_2d_matrix(max_flow, N, N);
#endif
  }
  int print_min_cut=0;
  if(print_min_cut) {
    bool visited[MAX_LEN];
    memset(visited, false, sizeof(visited));
    allNodesReachable(a, N, s, visited);
    printf("Min cut is:\n");
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        if(visited[i] && visited[j]) continue;
        if(!visited[i] && !visited[j]) continue;
        if(W[i][j]) {
          printf("%d %d\n", i, j);
        }
      }
    }
  }
  return maxflow;
}

int maximum_bipartite(int W[][MAX_LEN], int N) {
  int a[MAX_LEN][MAX_LEN];  //NOTE: MAX_LEN must be >= N+2
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      if(W[i][j]) {
        a[i+1][j+1] = W[i][j];
        a[0][i+1] = a[j+1][N+1] = 1;
      }
    }
  }
  int maxflow[MAX_LEN][MAX_LEN];
  return max_flow(a, N+2, 0, N+1, maxflow);
}

int main() {
#ifndef MBP
  freopen("graph_maxflow.txt", "r", stdin);
#else
  freopen("graph_bipartite.txt", "r", stdin);
#endif

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
    int maxflow[MAX_LEN][MAX_LEN];

#ifndef MBP
    cout << "Max flow:" <<  max_flow(a, N, 0, N-1, maxflow) << endl; 
#else
    cout << "Maximum bipartite:" << maximum_bipartite(a, N); 
#endif

  }
}
