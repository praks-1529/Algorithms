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
#define MAX_LEN 9

bool isRowSafe(int a[][MAX_LEN], int v, int r, int c) {
  for(int i=0; i<9; i++) {
    if(a[r][i] == v) {
      return false;
    }
  }
  return true;
}

bool isColSafe(int a[][MAX_LEN], int v, int r, int c) {
  for(int i=0; i<9; i++) {
    if(a[i][c] == v) {
      return false;
    }
  }
  return true;
}

bool isBlockSafe(int a[][MAX_LEN], int v, int r, int c) {
  int sr = (r/3)*3;
  int sc = (c/3)*3;
  for(int i=sr; i<sr+3; i++) {
    for(int j=sc; j<sc+3; j++) {
      if(a[i][j] == v) {
        return false;
      }
    }
  }
  return true;
}

bool isSafe(int a[][MAX_LEN], int v, int r, int c) {
  if(!isRowSafe(a, v, r, c)) {
    return false;
  } 
  if(!isColSafe(a, v, r, c)) {
    return false;
  }
  if(!isBlockSafe(a, v, r, c)) {
    return false;
  }
  return true;
}

bool findNextEmptyPos(int a[][MAX_LEN], int &r, int &c) {
  for(int i=0; i<9; i++) {
    for(int j=0; j<9; j++) {
      if(a[i][j] == 0) {
        r = i; c = j;
        return true;
      }
    }
  }
  return false;
}

bool solveSudoku(int a[][MAX_LEN]) 
{
  int r, c;
  if(!findNextEmptyPos(a, r, c)) {
    return true;
  }
  for(int i=1; i<=9; i++) {
    if(isSafe(a, i, r, c)) {
      a[r][c] = i;
      if(solveSudoku(a)) {
        return true;
      }
      a[r][c] = 0; //backtrack
    }
  }
  return false;
}

void print_2d_matrix(int a[MAX_LEN][MAX_LEN], int N, int M) {
  int type = 0;
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

int main() {
  freopen("sudoku.txt", "r", stdin);
  TEST {
    int a[MAX_LEN][MAX_LEN];
    int N; si(N);
    for(int i=0; i <N; i++) {
      for(int j=0; j<N; j++) {
        int x; si(x);
        a[i][j] = x;
      }
    }
    if(solveSudoku(a)) {
      printf("TRUE\n");
      print_2d_matrix(a, N, N);
    }
  }
}
