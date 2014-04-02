#include <stdio.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#define MAXN 100

void dfs_util(int a[MAXN][MAXN], int N, stack<int> &st, int visited[], int s) {
   visited[s] = true;
   for(int i=0; i<N; i++) {
     if(a[s][i] > 0 && !visited[i]) {
       dfs_util(a, N, st, visited, i);
       st.push(i);
     }
   }
}

vector< stack<int> >  find_SCC(int a[MAXN][MAXN], int N) {
   int visited[MAXN];
   for(int i=0; i<N; i++) {
     visited[i] = 0;
   }

   stack<int> st;
   for(int i=0; i<N; i++) {
     if(!visited[i]) {
        dfs_util(a, N, st, visited, i);
        st.push(i);
     }
   }

   // Now reverse the links and 
   int rev[MAXN][MAXN];
   for(int i=0; i<N; i++) {
     for(int j=0; j<N; j++) {
       if(a[i][j]) {
         rev[j][i] = a[i][j];
       }
     }
   }

   vector<stack<int> > SCC;
   for(int i=0; i<N; i++) {
     visited[i] = 0;
   }
   while(!st.empty()) {
     int x = st.top();
     st.pop();
     if(!visited[x]) {
       stack<int> st2;
       dfs_util(rev, N, st2, visited, x);
       st2.push(x);
       SCC.push_back(st2);
     }
   }

   // Print all forests in topo sort
   for(int i=0; i<SCC.size(); i++) {
     stack<int> cur = SCC[i];
     while(!cur.empty()) {
       int x = cur.top();
       cur.pop();
       printf("%d ", x);
     }
     printf("\n");
   }
   return SCC;
}

int main() {
  int N, M;
  int a[MAXN][MAXN];
  scanf("%d", &N);
  scanf("%d", &M);
  while(M--) {
    int x, y, w;
    scanf("%d %d %d", &x, &y, &w);
    a[x][y] = w;
  }
  int x, y;
  scanf("%d %d", &x, &y);
  (void)find_SCC(a, N);
}

