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
#define MSSI map<string, string>::iterator
#define print_array(x,n) for(int i=0; i<n; i++) { cout << x[i] << endl; }
#define TEST int T;scanf("%d",&T);while(T--)
#define CASES int N;scanf("%d",&N);while(N--)

/* ############################################################################
 * END OF HEADER 
 * ############################################################################
*/
#define MAX_LEN 100

bool isSafe(int a[][MAX_LEN], int N, int u, int colr, int colors[]) {
  for(int i=0; i<N; i++) {
    if(a[u][i] && colors[i] == colr) {
      return false;
    }
  }
  return true;
}

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

int main() {
  freopen("graph_mcolor.txt", "r", stdin);
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
      si(x); si(y);
      a[x][y] = a[y][x] = 1;
    }
#endif
    int M; si(M);
    int colors[MAX_LEN];
    memset(colors, 0, sizeof(colors));
    if(mcolor_graph_possible(a, N, 0, M, colors)) {
      printf("Possible\n");
      for(int i=0; i<N; i++) {
        printf("%d ", colors[i]);
      }
    } else {
      printf("Not-Possible\n");
    } 
  }
}

