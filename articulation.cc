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

#define MEM(a,v) memset(a,v,sizeof(a))
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
#define MSSI map<string, string>::iterator
#define print_array(x,n) { for(int i=0; i<n; i++) { cout << x[i] << " " ; } cout << endl; }
#define TEST int T;scanf("%d",&T);while(T--)
#define CASES int N;scanf("%d",&N);while(N--)

/* ############################################################################
 * END OF HEADER 
 * ############################################################################
*/

#define MXN 3001

bool arr[MXN][MXN];
bool artic_point[MXN];
int depth[MXN];
int low_point[MXN];
int time_stamp=0;

void
dfs_visit2(int previous_node, int parent_id, int N) {
  int child = 0;
  depth[parent_id]     = ++time_stamp;
  low_point[parent_id] = depth[parent_id];
  for(int child_id=0; child_id<N; child_id++) {
    if(arr[parent_id][child_id]) {
      if(depth[child_id]==-1) {
        child++;
        dfs_visit2(parent_id, child_id, N);
        low_point[parent_id] = MIN(low_point[parent_id], low_point[child_id]);
        /* This one is the low point of tree rooted at the child */
        if((low_point[child_id] >= depth[parent_id]) && (parent_id != previous_node)) {
          /* Not a root node and has a child forest at "child_id", for which low_point[child_id] <= depth[parent_id] */
          artic_point[parent_id]=true;
        }
      } else if(child_id != parent_id) {
        /* Back edge and not a tree edge */
        low_point[parent_id] = MIN(low_point[parent_id], depth[child_id]);
      }
    }
  }
  if(previous_node == parent_id && child>1) {
    /* Only true for root node */
    artic_point[parent_id]=true;
  }
}

void
init() {
  /* Reset */
  memset(arr, 0, MXN*MXN*sizeof(bool));
  memset(artic_point, 0, MXN*sizeof(bool));
  memset(depth, 0, MXN*sizeof(int));
  memset(low_point, 0, MXN*sizeof(int));
  for(int i=0; i<MXN; i++)
  {
    low_point[i]=-1;
    depth[i]=-1;
  }
}

int 
find_articulation_points(int N) {
  /* Do a DFS and get the tree */
  for(int i=0; i<N; i++) {
    if(depth[i] == -1) {
      dfs_visit2(i,i, N);
    }
  }
  /* Do a post order and populate low_point[] */
  int ret=0;
  for(int i=0; i<N; i++) {
    if(artic_point[i]) ret++;
  }
  return ret;
}

int main() {
#if DEBUG
  //freopen("in.txt", "r", stdin);
#endif
  TEST {
    init();
    int N, M;
    cin >> N >> M;
    while(M--) {
      int i, j;
      si(i); si(j);
      arr[i][j] = arr[j][i] = true;
    }
    cout << find_articulation_points(N) << endl; 
  }
}

