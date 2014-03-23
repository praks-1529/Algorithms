#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#define MAX_V 10000007
using namespace std;
typedef int ull;

/******************************************************************
 *  SOME UTUILITY FUNCTIONS
 *  **************************************************************/
ull
power(ull a, ull b)
{
  if(b==0)
    return 1;
  else if(b==1)
    return a;
  else if(b%2==0)
    return power((a*a),b/2);
  else
    return (power((a*a),b/2)*a);
}

ull logbase2(ull N) {
  ull x = (ull)(log(N)/log(2));
  return x;
}

ull powerint(ull A, ull B) {
  ull x= (ull)pow(A, B);
  return x;
}

/*****************************************************************
 * BASED ON SQUARE ROOT <O(n), O(sq(n)) >
 * NOTE: vector<ull> ip starts from index 0 to N-1
 * **************************************************************/
void
sqrt_process(vector<ull> &ip, vector<ull> &pre_process) {
  ull N = ip.size();
  ull sq_N = (ull)sqrt(N);
  if(sq_N * sq_N == N) {
    pre_process.resize(sq_N);
  } else {
    pre_process.resize(sq_N+1);
  }
  ull k=0;
  ull min = MAX_V;
  ull min_index = -1;
  ull i;
  for(i=0; i<ip.size(); i++) {
    if(ip[i] < min) {
      min = ip[i];
      min_index = i;
    }
    if(sq_N-1 == (i%sq_N)) {
      pre_process[k++] = min_index;
      min = MAX_V;
      min_index = -1;
    }
  }
  if(((i-1)%sq_N) < sq_N-1) {
    pre_process[k++] = min_index;
  }
}

ull
sqrt_query(vector<ull> &ip, vector<ull> &pre_process, ull i, ull j) {
  ull N = ip.size();
  ull sq_N = (ull)sqrt(N);
  ull min = MAX_V;
  for(ull k=i; k<=j ;k++) {
    if(k%sq_N) {
      if(ip[k] < min) {
        min = ip[k];
      }
    } else {
      if(j >= (k + sq_N-1) ) {
        if(ip[pre_process[(k/sq_N)]] < min) {
          min = ip[pre_process[(k/sq_N)]];
          k += sq_N-1;
        }
      } else { 
        if(ip[k] < min) {
          min = ip[k];
        }
      }
    }
  }
  return min;
}

/*****************************************************************
 * BASED ON SEGMENT TREE <O(n), O(log(n)) >
 * NOTE: vector<ull> ip starts from index 0 to N-1
 * **************************************************************
                                         (0-9)
                                       /       \
                                  (0-4)          (5-9)
                                 /     \        /     \
                              (0-2)   (3-4)   (5-7)   (8-9)
                             /     \  /   \   /   \   /    \
                           (0,1)  (2)(3)  (4)(5)  (7)(8)   (9)
                          /     \
                         (0)    (1)
*/
/* Calculate the index of the minimum value between ip[low] - ip[high] and store it in seg_tree[root_index] */

void
segment_tree_init_low(ull root_index, 
                      ull low, ull high, 
                      vector<ull> &ip, 
                      vector<ull> &seg_tree, 
                      bool min_tree) {
  if(seg_tree.size() == 0) {
    ull tree_size = 2*(powerint(2, (logbase2(ip.size())+1)));
    seg_tree.resize(tree_size+1);
  }
  if(low == high) {
    seg_tree[root_index] = low;
  } else {
    segment_tree_init_low(root_index*2,   
                          low, (low+high)/2, 
                          ip, 
                          seg_tree, 
                          min_tree);
    segment_tree_init_low(root_index*2+1, 
                          ((low+high)/2)+1, high,
                          ip, 
                          seg_tree, 
                          min_tree);
    if(min_tree) {
      if(ip[seg_tree[root_index*2]] < ip[seg_tree[root_index*2 + 1]]) {
        seg_tree[root_index] = seg_tree[root_index*2];
      } else {
        seg_tree[root_index] = seg_tree[root_index*2+1];
      }
    } else {
      if(ip[seg_tree[root_index*2]] > ip[seg_tree[root_index*2 + 1]]) {
        seg_tree[root_index] = seg_tree[root_index*2];
      } else {
        seg_tree[root_index] = seg_tree[root_index*2+1];
      }
    }
  }
}

void
segment_tree_init(vector<ull> &ip, vector<ull> &seg_tree, bool min_tree) {
  segment_tree_init_low(1, 0, ip.size()-1, ip, seg_tree, min_tree);
}

/* Above example. (b, e) = (0, 9)  and (i, j) = (5, 7) */
ull
segment_tree_query_low(ull root, 
                       ull b, ull e, 
                       vector<ull> &seg_tree, 
                       vector<ull> &ip, 
                       ull i, ull j,
                       bool min_tree) {
  ull p1, p2;
  //if the current interval doesn't intersect 
  //the query interval return -1
  // Example : (0, 2) does not intersect with (3, 7)
  if (i > e || j < b)
    return -1;

  //if the current segment tree intererval is included in 
  //the query interval return M[node]. i.e (i <= b <= e <= j)
  //Above example : 3 <= 3<= 4<= 7
  if (b >= i && e <= j)
    return seg_tree[root];

  //compute the minimum position in the 
  //left and right part of the interval
  p1 = segment_tree_query_low(2 * root,
                              b, (b + e) / 2, 
                              seg_tree, 
                              ip, 
                              i, j, 
                              min_tree);
  p2 = segment_tree_query_low(2 * root + 1, 
                              (b + e) / 2 + 1, e,
                              seg_tree, 
                              ip, 
                              i, j,
                              min_tree);
  //return the position where the overall 
  //minimum is
  if (p1 == -1)
    return p2;
  if (p2 == -1)
    return p1;
  if(min_tree) {
    if (ip[p1] <= ip[p2])
      return p1;
    else 
      return p2;
  } else {
    if (ip[p1] >= ip[p2])
      return p1;
    else 
      return p2;
  }
}

ull 
segment_tree_query(ull i, ull j, vector<ull> &seg_tree, vector<ull> &ip, bool min_tree) {
  int k = segment_tree_query_low(1, 0, ip.size()-1, seg_tree, ip, i, j, min_tree);
  if(k >= 0) {
    return ip[k];
  } else {
    return k;
  }
}

int main() {
  //freopen("in.txt", "r", stdin);
  int N, K;
  cin >> N >> K;
  vector<ull> ip(N);
  int i = 0;
  while(N--) {
    cin >> ip[i++];
  }
  if(0) {
    vector<ull> pre_process;
    sqrt_process(ip, pre_process);
    while(K--) {
      int i, j;
      cin >> i >> j;
      cout << sqrt_query(ip, pre_process, i, j) << endl; 
    }
  } else {
    vector<ull> min_seg_tree;
    vector<ull> max_seg_tree;
    segment_tree_init(ip, min_seg_tree, true);
    segment_tree_init(ip, max_seg_tree, false);
    while(K--) {
      int i, j;
      cin >> i >> j;
      cout << "Min : " << segment_tree_query(x, y, min_seg_tree, ip, true) << endl;
      cout << "Max : " << segment_tree_query(x, y, max_seg_tree, ip, false) << endl;
    }
  }
}
