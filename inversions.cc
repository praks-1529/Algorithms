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
#define read1dArray(a, N)  { \
  int i = 0; \
  while(N--) { \
    si(a[i++]); \
  } \
} 

/* ############################################################################
 * END OF HEADER 
 * ############################################################################
*/
#define MAX_LEN 100

int mergesort(int a[], int low, int high) {
  if(low >= high) {
    return 0;
  } else {
    if(high-low == 1) {
      if(a[low] > a[high]) {
        int temp = a[low];
        a[low] = a[high];
        a[high] = temp;
        return 1;
      } else {
        return 0;
      }
    } else {
      int mid = (high - low)/2;
      int inv = mergesort(a, low, mid);
      inv += mergesort(a, mid+1, high);
      int l1, l2;
      int s[MAX_LEN];
      int k=0;
      for(l1 = low, l2 = mid+1; (l1 <= mid && l2 <= high); ) {
        if(a[l1] > a[l2]) {
          inv += (mid-l1+1);
          s[k++] = a[l2++];
        } else {
          s[k++] = a[l1++];
        }
      }
      while(l1<=mid) {
        s[k++] = a[l1++];
      }
      while(l2 <=high) {
        s[k++] = a[l2++];
      }
      int i = low;
      for(k=0; k<(high-low+1); ) {
        a[i++] = s[k++];
      }
      return inv;
    }
  }
}


int main() {
  freopen("inversions.txt", "r", stdin);
  TEST {
    int N; si(N);
    int a[MAX_LEN];
    int N_ = N;
    read1dArray(a, N_);
    cout << mergesort(a, 0, N-1) <<  endl; 
  }
}
