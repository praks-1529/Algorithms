#include <vector>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

typedef int ull;

void
bit_update(ull index, ull x, vector<ull> &tree) {
  while(index <= tree.size()) {
    tree[index] += x;
    index += (index & -index);
  }
}

ull
bit_query(ull index, vector<ull> &tree) {
  ull ret = 0;
  while(index > 0) {
    ret += tree[index];
    index -= (index & -index);
  }
  return ret;
}

void bin_index_tree() {
  int N, M;
  scanf("%d", &N);
  scanf("%d", &M);
  vector<ull> arr(N+1,0);
  vector<ull> aux(N+1,0);
  char type[2];
  while(M--) {
    scanf("%s", type);
    if(type[0] == 'Q') {
      int x, y;
      scanf("%d%d", &x, &y);
      cout << (bit_query(x+1, aux) - bit_query(y+1, aux)) << endl;
    } else {
      /* O(lgn) algorithm */
      int i;
      scanf("%d", &i);
      bit_update(i+1, 1, aux);
    }
  }
}

int brute_force() {
  int N, M;
  scanf("%d", &N);
  scanf("%d", &M);
  vector<ull> arr(N,0);
  vector<ull> aux(N,0);
  char type[2];
  while(M--) {
    scanf("%s", type);
    if(type[0] == 'Q') {
      int x, y;
      scanf("%d%d", &x, &y);
      cout << (aux[x] - aux[y]) << endl;
    } else {
      /* O(n) algorithm */
      int i;
      scanf("%d", &i);
      arr[i]++;
      for(int j=i ; j < aux.size(); j++) {
        aux[j] = aux[j-1] + arr[j];
      }
    }
  }
}

int main() {
#if TXT_IP
  freopen("small.txt","r",stdin);
#endif
  if(0) {
    brute_force();
  } else {
    bin_index_tree();
  }
}
