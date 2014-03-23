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

class node {
  public:
    node(char c) : c_(c) { 
      for(int i=0; i<26; i++) {
        childs_[i] = NULL;
      }
    }
    int count_;
    node* childs_[26];
  private:
    char c_;
};

class Trie {
  public:
    Trie(void) {
      root_ = new node('-');
    }
    void AddWord(std::string &word) {
      int index;
      char c;
      node *nd = root_;;
      for(int i=0; i<word.size(); i++) {
        c       = word[i];
        index   = c - 'a';
        if(!(nd->childs_[index])) {
          nd->childs_[index] = new node(c);
        }
        nd = nd->childs_[index];
      }
      nd->count_++;
    }
    int FindWord(std::string word) {
      int index;
      char c;
      node *nd = root_;;
      for(int i=0; i<word.size(); i++) {
        c       = word[i];
        index   = c - 'a';
        if(!(nd->childs_[index])) {
          return false;
          nd->childs_[index] = new node(c);
        }
        nd = nd->childs_[index];
      }
      return nd->count_;
    }
  private:
    node* root_;
};

Trie* construct_tree(vector<string> &ip) {
  Trie* t = new Trie();
  for(int i=0 ; i<ip.size(); i++) {
    t->AddWord(ip[i]);
  }
  return t;
}

int main() {
  freopen("trie.txt", "r", stdin);
  TEST {
    int N; si(N);
    int N_ = N;
    std::vector<std::string> ip;
    while(N_--) {
       std::string x;
       cin >> x;
       ip.pb(x);
    }
    Trie *tree = construct_tree(ip);
    cout << tree->FindWord(std::string("sa")) << endl;
  }
}
