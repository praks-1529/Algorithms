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
int 
knapSack(int W, vector<int> &v, vector<int> &w, int n) {
  if(W==0 || n==0) return 0;
  if(W < w[n]) {
    return knapSack(W, v, w, n-1);
  } else {
   // return max((v[n] + knapSack(W-w[n], v, w, n-1)), knapSack(W, v, w, n-1));
    // Note ini case duplicates are allowed then below stmt
    return max((v[n] + knapSack(W-w[n], v, w, n)), knapSack(W, v, w, n-1));
  }
}

int knapSackDP(int W, vector<int> &v, vector<int> &wt, int N) {
  N++; // Here N indicates number of items
  int K[N+1][W+1];
  memset(K, 0, sizeof(int)*N+1*W+1);
  for(int n=0; n<=N; n++) {
    for(int w = 0; w<=W; w++) {
      if(n==0 || w==0) K[n][w] = 0; //No items or wieight = 0 => vallue = 0
      else if(wt[n] <= W) {
        K[n][w] = max(K[n-1][w], v[n] + K[n-1][w-wt[n]]);
      } else {
        K[n][w] = K[n-1][w];
      }
    }
  }
  return K[N][W];
}

int main() {
  freopen("knapsack_01.txt", "r", stdin);
  TEST {
    int N; si(N);
    vector<int> v;
    vector<int> w;
    v.pb(0);
    w.pb(0);
    int N_ = N;
    while(N_--) {
      int x;si(x);
      v.pb(x);
    }
    N_ = N;
    while(N_--) {
      int x;si(x);
      w.pb(x);
    }
    int W; si(W);
    cout << knapSack(W, v, w, N) << endl;
//    cout << knapSackDP(W, v, w, N) << endl;
  }
}

