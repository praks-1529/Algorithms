#include <stdio.h>
#include <queue>
using namespace std;

#define MAXN 100

bool path_exists(int a[MAXN][MAXN], int N, int parent[], int s, int t) {
  int visited[MAXN];
  for(int i=0; i<N; i++) {
    visited[i] = 0;
    parent[i] =  -1;
  }
  queue<int> q;
  q.push(s);
  visited[s] = true;
  while(!q.empty()) {
    int x = q.front();
    q.pop();  
    for(int i=0; i<N; i++) {
      if(a[x][i] >0 && !visited[i]) {
        q.push(i);
        visited[i] = true;
        parent[i] = x;
      }
    }
  }
  return visited[t];
}

int ford_fulkerson(int a[MAXN][MAXN], int N, int s, int t) {
  int res[MAXN][MAXN];
  int max_flow = 0;
  int parent[MAXN];
  while(path_exists(a, N, parent, s, t)) {
    int min_flow = 1000;
    for(int i=t; i!=s; ) {
      int v = i;
      int u = parent[v];
      i = u;
      if(a[u][v] < min_flow) {
        min_flow = a[u][v];
      }
    }

    for(int i=t; i!=s; ) {
      int v = i;
      int u = parent[v];
      res[u][v] += min_flow;
      a[u][v] -= min_flow;
      i = u;
    }

    max_flow += min_flow;
  }
  return max_flow;
}

int main() {
  freopen("in.txt", "r", stdin);
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
  printf("Max flow:%d\n", ford_fulkerson(a, N, x, y)); 
}

