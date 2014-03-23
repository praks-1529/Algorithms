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
typedef unsigned long long ull;
bool brute_method (ull n, int iterations)
{
   if (n<=1) return false;
   if (n==2) return true;
   if (n%2==0) return false;
   ull m = (ull)sqrt((long double)n);
   for (ull i=3; i<=m; i+=2)
      if (n%i==0)
         return false;
   return true;
}

/* this function calculates (a*b)%c taking into account that a*b in case of 10^18 might overflow */
ull mulmod(ull a,ull b,ull c){
  ull x = 0, y=a%c;
  while(b > 0){
    if(b%2 == 1){
      x = (x+y)%c;
    }
    y = (y*2)%c;
    b /= 2;
  }
  return x%c;
}

/* This function calculates (a^b)%c */
ull modulo(ull a, ull b, ull c){
  ull x=1,y=a; 
  while(b > 0){
    if(b%2 == 1){
      x = mulmod(x, y, c);
    }
    y = mulmod(y, y, c); // squaring the base
    b /= 2;
  }
  return x%c;
}

/* Fermat's test for checking primality, the more iterations the more is accuracy */
bool Fermat(ull p,int iterations){
  if(p == 1){ // 1 isn't prime
    return false;
  }
  for(int i=0;i<iterations;i++){
    // choose a random integer between 1 and p-1 ( inclusive )
    ull a = rand()%(p-1)+1; 
    // modulo is the function we developed above for modular exponentiation.
    if(modulo(a,p-1,p) != 1){ 
      return false; /* p is definitely composite */
    }
  }
  return true; /* p is probably prime */
}

/* Miller-Rabin primality test, iteration signifies the accuracy of the test */
bool Miller(long long p,int iteration){
    if(p<2){
        return false;
    }
    if(p!=2 && p%2==0){
        return false;
    }
    long long s=p-1;
    while(s%2==0){
        s/=2;
    }
    for(int i=0;i<iteration;i++){
        long long a=rand()%(p-1)+1,temp=s;
        long long mod=modulo(a,temp,p);
        while(temp!=p-1 && mod!=1 && mod!=p-1){
            mod=mulmod(mod,mod,p);
            temp *= 2;
        }
        if(mod!=p-1 && temp%2==0){
            return false;
        }
    }
    return true;
}

//calculates Jacobian(a/n) n>0 and n is odd
int calculateJacobian(long long a,long long n){
    if(!a) return 0; // (0/n) = 0
    int ans=1;
    long long temp;
    if(a<0){
        a=-a;    // (a/n) = (-a/n)*(-1/n)
        if(n%4==3) ans=-ans; // (-1/n) = -1 if n = 3 ( mod 4 ) 
    }
    if(a==1) return ans; // (1/n) = 1
    while(a){
        if(a<0){
            a=-a;    // (a/n) = (-a/n)*(-1/n)
            if(n%4==3) ans=-ans;    // (-1/n) = -1 if n = 3 ( mod 4 )
        }
        while(a%2==0){
            a=a/2;    // Property (iii)
            if(n%8==3||n%8==5) ans=-ans;    
        }
        swap(a,n);    // Property (iv)
        if(a%4==3 && n%4==3) ans=-ans; // Property (iv)
        a=a%n; // because (a/p) = (a%p / p ) and a%pi = (a%n)%pi if n % pi = 0
        if(a>n/2) a=a-n; 
    }
    if(n==1) return ans;
    return 0; 
}

/* Iterations determine the accuracy of the test */
bool Solovoy(long long p,int iteration){
    if(p<2) return false;
    if(p!=2 && p%2==0) return false;
    for(int i=0;i<iteration;i++){
        long long a=rand()%(p-1)+1;
        long long jacobian=(p+calculateJacobian(a,p))%p;
        long long mod=modulo(a,(p-1)/2,p);
        if(!jacobian || mod!=jacobian){ 
            return false;
        }
    }
    return true;
}

enum test_type {
  brute=0,
  fermat,
  miller,
  solovoy
};

bool
is_prime(ull n, int iterations, test_type type) {
  if(type == brute) {
    return brute_method(n, iterations);
  } else if(type == fermat) {
    return Fermat(n, iterations);
  } else if(type == miller) {
    return Solovoy(n, iterations);
  } else if(type == solovoy) {
    return Miller(n, iterations);
  }
}

#define ITERATIONS 12

int main() {
  TEST {
    ull N;
    cin >> N;
    bool found = false;
    ull mult = N/6;
    test_type type = miller;
    if(N%6 != 0) {
      for(ull i=N; i>(mult*6) && !found; i--) {
        if(is_prime(i, ITERATIONS, type)) {
          cout << i << endl;
          found = true;
        }
      }
    }
    for(ull i=mult; (i>=1 && !found) ; i--) {
      if(((i*6+1) <=N) && is_prime(i*6+1, ITERATIONS, type)) {
        cout << (i*6+1) << endl;
        break;
      }
      if(is_prime((i*6-1), ITERATIONS, type)) {
        cout << (i*6-1) << endl;
        break;
      }
    }
  }
}
