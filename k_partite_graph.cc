#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;
#define MODVAL 1000000007

typedef unsigned long long ull;
ull mulmod(ull a,ull b,ull c=MODVAL){
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
ull modulo(ull a, ull b, ull c=MODVAL){
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

ull
num_of_spanning_k_partite(ull n, int p, vector<int> &ki) {
  if(p==1) {
    return 0;
  }
  assert(p >= 2);
  ull base = modulo(n, p-2); 
  for(int i=0; i<ki.size(); i++) {
    base = (base * modulo((n-ki[i]), ki[i] - 1))%MODVAL;
  }
  return base;
}

int main() {
  ull n, k;
  cin >> n >> k;
  int p = n;  // total number of sets 
  vector<int> ki(p, k); // Size of each sets
  if(n == 1 && k==1) {
    cout << 1 << endl;
  } else {
    cout << num_of_spanning_k_partite((n*k), p, ki) << endl;
  }
}
